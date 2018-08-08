
// 利用select 实现一个单进程版本的tcp服务器, 可服务多个客户

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/select.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netinet/in.h>

#define MAX_FD_SIZE ( sizeof(fd_set) * 8 )
#define INIT -1

// 初始化文件描述符数组
void arr_init(int* fd_arr, int num)
{
    int i = 0;
    for(; i<num; i++)
    {
        fd_arr[i] = INIT;
    }
}
// 添加套接字
int arr_add(int* fd_arr, int num, int fd_sock)
{
    (void)num;
    size_t i = 0;
    for(; i<MAX_FD_SIZE; i++)
    {
        if(fd_arr[i] == INIT)
        {
            fd_arr[i] = fd_sock;
            return 0;
        }
    }
    return -1;
}
// 删除套接字
void arr_del(int* fd_arr, int num, size_t index)
{
    (void)num;
    if(index < MAX_FD_SIZE && index > 0)
    {
        fd_arr[index] = INIT;
    }
}
// 设置文件描述符集
int set_fds(int* fd_arr, int num, fd_set* fds)
{
    (void)num;
    int max_fd = INIT; 
    printf("select : ");
    size_t i = 0;
    for(; i<MAX_FD_SIZE; i++)
    {
        if(fd_arr[i] > INIT)
        {
            printf("%d ", fd_arr[i]);
            FD_SET(fd_arr[i], fds);
            if(max_fd < fd_arr[i])
            {
                max_fd = fd_arr[i];
            }
        }
    }
    printf("\n");
    return max_fd;
}

// 获取监听套接字
int startUp(int port)
{
    if(port <= 1024)
      return -1;
    // 获取套接字
    int sock = socket(AF_INET, SOCK_STREAM, 0);
    if(sock < 0)
    {
        perror("socket");
        exit(1);
    }
    // 设置 opt
    // int setsockopt(int sockfd, int level, int optname, const void *optval, socklen_t optlen);
    // sockfd：标识一个套接口的描述字。
    // level：选项定义的层次；支持SOL_SOCKET、IPPROTO_TCP、IPPROTO_IP和IPPROTO_IPV6。
    // optname：需设置的选项。
    // optval：指针，指向存放选项待设置的新值的缓冲区。
    // optlen：optval缓冲区长度。
    int opt = 1;
    // SO_REUSEADDR是让端口释放后立即就可以被再次使用。
    //
    // SO_REUSEADDR用于对TCP套接字处于TIME_WAIT状态下的socket，才可以重复绑定使用。
    // server程序总是应该在调用bind()之前设置SO_REUSEADDR套接字选项
    setsockopt(sock, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt));
    // 定义sockaddr_in对象, 并初始化
    struct sockaddr_in local;
    local.sin_family = AF_INET;
    local.sin_port = htons(port);
    local.sin_addr.s_addr = htonl(INADDR_ANY);
    
    // 绑定
    if( bind(sock, (struct sockaddr*)&local, sizeof(local) ) < 0)
    {
        perror("bind");
        exit(2);
    }

    // 监听
    if( listen(sock, 5) < 0 )
    {
        perror("listen");
        exit(3);
    }

    return sock;
}

void service(int* fd_arr, int num, fd_set* fds)
{
    int i = 0;
    for(; i<num; i++)
    {
        if(fd_arr[i] > INIT && FD_ISSET(fd_arr[i], fds))
        {
            int fd = fd_arr[i];
            if(i == 0)
            {
                // 说明这是监听套接字就绪了
                struct sockaddr_in client;
                socklen_t len = sizeof(client);
                // 连接
                // int accept(int sockfd, struct sockaddr *addr, socklen_t *addrlen);
                int new_sock = accept(fd, (struct sockaddr*)&client, &len);
                if(new_sock < 0)
                {
                    perror("accept");
                    continue;
                }
                else
                {
                    printf("get a new client: [%s|%d]\n", inet_ntoa(client.sin_addr), ntohs(client.sin_port));
                }
                int arr_add_ret = arr_add(fd_arr, num, new_sock);
                if(arr_add_ret < 0)
                {
                    printf("server is busy !\n");
                    close(new_sock);
                }
            }
            else
            {
                // 到这里说明有新的文件描述符的读事件就绪了
                char buf[1024];
                ssize_t ret = read(fd, buf, sizeof(buf) - 1);
                if(ret > 0)
                {
                    buf[ret] = 0;
                    printf("\n=============================\n");
                    printf("client : %s\n", buf);
                    printf("\n=============================\n");
                }
                else if(ret == 0)
                {
                    printf("client quit !\n");
                    arr_del(fd_arr, num, i);
                }
                else
                {
                    perror("read");
                    close(fd);
                    arr_del(fd_arr, num, i);
                }
            }
        }
    }
}




int main(int argc, char* argv[])
{
    if(argc != 2)
    {
        printf("Usage: ./server [port > 1024]\n");
        return -1;
    }

    // 设置监听套接字listen_sock
    int listen_sock = startUp(atoi(argv[1]));
    // 定义保存文件描述符的数组
    int fd_arr[MAX_FD_SIZE];
    
    // 初始化文件描述符数组
    arr_init(fd_arr, MAX_FD_SIZE);
    // 添加监听套接字
    arr_add(fd_arr, MAX_FD_SIZE, listen_sock);

    // 设置文件描述符集
    fd_set fds;
    // 最大的文件描述符
    int max_fd = 0;

    while(1)
    {
        // 设置timeout
        struct timeval timeout = {5, 0}; // 第一个成员代表秒, 第二个是微秒, 此处设置 5s
        // 清空文件描述符集
        FD_ZERO(&fds);
        // 获取文件描述符最大值
        max_fd = set_fds(fd_arr, MAX_FD_SIZE, &fds);
        // 调用select等待
        // int select(int nfds, fd_set *readfds, fd_set *writefds,
        //            fd_set *exceptfds, struct timeval *timeout);
        switch(select(max_fd + 1, &fds, NULL, NULL, &timeout))
        {
            // 返回值为 0, 超时
            case 0:
                printf("select timeout !\n");
                break;
            case -1:
                perror("select");
            default:
                // 成功了, 就开始服务
                service(fd_arr, MAX_FD_SIZE, &fds);
        }
    }
}
