/*================================================================

# File Name: epoll_ET_tcpServer.c
# Author: rjm
# mail: rjm96@foxmail.com
# Created Time: 2018年06月06日 星期三 13时33分46秒

================================================================*/



// ET 模式的epoll
#include <stdio.h>
#include <fcntl.h>
#include <stdlib.h>
#include <sys/epoll.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h> 
#include <arpa/inet.h>
#include <unistd.h>
#include <string.h>
#include <errno.h>
#include <string>
#include <sys/stat.h>
#include <sys/stat.h>
#include <sys/sendfile.h>


#define MAX 10

// setNoBlock
// 将一个文件描述符设置为非阻塞
void setNoBlock(int fd)
{
    int fl = fcntl(fd, F_GETFL);
    if(fl < 0)
    {
        perror("fcntl");
        return ;
    }
    fcntl(fd, F_SETFL, fl | O_NONBLOCK);
}

//////////////////////////////////
// 实现相应接口
//////////////////////////////////

// 1, 获取监听套接字
int startUp(int port)
{
    if(port < 1024)
    {
        printf("Usage: ./server [port > 1024]\n");
        return 2;
    }
    struct sockaddr_in addr;
    addr.sin_family = AF_INET;
    addr.sin_port = htons(port);
    addr.sin_addr.s_addr = INADDR_ANY;
    int listen_fd = socket(AF_INET, SOCK_STREAM, 0); 
    if(listen_fd < 0)
    {
        perror("socket");
        return 3;
    }
    // 绑定
    // int bind(int sockfd, const struct sockaddr *addr,
    //          socklen_t addrlen);
    int bind_ret = bind(listen_fd, (struct sockaddr*)&addr, sizeof(addr));
    if(bind_ret < 0)
    {
        perror("bind");
        return 4;
    }
    // 监听
    int listen_ret = listen(listen_fd, 5);
    if(listen_ret < 0)
    {
        perror("listen");
        return 5;
    }
    return listen_fd;
}

// 2, 监听套接字就绪, 开始获取连接
void getConnect(int listen_fd, int epoll_fd)
{
    struct sockaddr_in client;
    socklen_t len = sizeof(client);
    // 连接
    // int accept(int sockfd, struct sockaddr *addr, socklen_t *addrlen);
    int connect_fd = accept(listen_fd, (struct sockaddr*)&client, &len);
    if(connect_fd < 0)
    {
        perror("accept");
        return ;
    }
    // 到这里连接成功
    printf("get a new client: [%s | %d]\n", inet_ntoa(client.sin_addr), ntohs(client.sin_port));
    // 将其设置为非阻塞
    setNoBlock(connect_fd);
    // 将这个新获取的套接字添加到epoll_fd中
    struct epoll_event ev;
    ev.data.fd = connect_fd;
    ev.events = EPOLLIN | EPOLLET;
    int ret = epoll_ctl(epoll_fd, EPOLL_CTL_ADD, connect_fd, &ev);
    if(ret < 0)
    {
        perror("epoll_ctl");
        return ;
    }
}

// 实现无阻塞地读的接口
ssize_t noBlockRead(int fd, char* buf, int size)
{
    (void) size;
    ssize_t total_size = 0;
    while(1)
    {
        ssize_t cur_size = read(fd, buf + total_size, sizeof(buf)/sizeof(buf[0]));
        total_size += cur_size;
        if(cur_size < (ssize_t)(sizeof(buf)/sizeof(buf[0])) || errno == EAGAIN)
        {
            break;
        }
    }
    buf[total_size] = 0;
    return total_size;
}

// 2, 正常客户端就绪, 开始服务
void service(int client, int epoll_fd)
{
    char buf[1024] = {0};
    int ret = noBlockRead(client, buf, sizeof(buf)-1);
    if(ret < 0)
    {
        perror("read");
        return ;
    }
    if(ret == 0)
    {
        printf("client quit !\n");
        close(client);
        epoll_ctl(epoll_fd, EPOLL_CTL_DEL, client, NULL);
        return ;
    }
    buf[ret] = 0;
    printf("\n=====================================\n");
    printf("client say :\n%s\n", buf);
    printf("\n=====================================\n");

    const std::string home = "./webroot/index.html";
    struct stat st;
    if(stat(home.c_str(), &st) < 0)
    {
        printf("文件不存在\n");
        perror("stst");
        return ;
    }
    int index_fd = open(home.c_str(), O_RDONLY);

    // 定义状态行和空行
    const char* status_line = "HTTP/1.0 200 OK\r\n";                                                                   
    const char* blank_line = "\r\n";
    // 1.发送响应状态行
    send(client, status_line, strlen(status_line), 0);

    // 2.发送Content-Length用于描述HTTP消息实体的传输长度
    char len_buf[256] = {0};
    // content_length = "Content-Length: %u\r\n"
    sprintf(len_buf, "Content-Length: %lu\r\n", st.st_size);
    send(client, len_buf, strlen(len_buf), 0);

    // 3.发送空行
    send(client, blank_line, strlen(blank_line), 0);

    // 4.发送所请求的资源
    // ssize_t sendfile(int out_fd, int in_fd, off_t *offset, size_t count);
    if(sendfile(client, index_fd, NULL, st.st_size) < 0)
    {
        perror("sendfile");
    }
    // 关闭打开的文件
    close(index_fd);
}

int main(int argc, char* argv[])
{
    if(argc != 2)
    {
        printf("Usage : ./server [port > 1024]\n");
        return 1;
    }
    
    // 首先要获取监听套接字
    int listen_sock = startUp(atoi(argv[1]));

    // 创建 epoll 模型
    int epfd = epoll_create(MAX);

    // 将 listen_sock 设置为非阻塞
    setNoBlock(listen_sock);

    // 将监听套接字注册到 epoll 模型中
    struct epoll_event ev;
    ev.events = EPOLLIN | EPOLLET;
    ev.data.fd = listen_sock;
    int epoll_ctl_ret = epoll_ctl(epfd, EPOLL_CTL_ADD, listen_sock, &ev);
    if(epoll_ctl_ret < 0)
    {
        perror("epoll_ctl");
        return 6;
    }

    // 循环等待连接, 提供服务
    while(1)
    {
        struct epoll_event evs[MAX];
        // 获取就绪事件
        int epoll_wait_ret = epoll_wait(epfd, evs, MAX, -1);
        if(epoll_wait_ret < 0)
        {
            perror("epoll_wait");
            continue;
        }
        if(epoll_wait_ret == 0)
        {
            printf("epoll timeout !\n");
            continue;
        }
        // 到这里说明有事件就绪了
        for(int i = 0; i < epoll_wait_ret; i++)
        {
            // 如果不是读事件就绪
            if(!(evs[i].events & EPOLLIN))
            {
                continue;
            }
            // 如果是监听套接字的读事件就绪
            if(evs[i].data.fd == listen_sock)
            {
                // 开始进行连接
                getConnect(listen_sock, epfd);
            }
            else
            {
                // 说明是正常客户端的读事件就绪, 开始服务
                service(evs[i].data.fd, epfd);
            }
        } // loop 1 end
    } // loop 2 end
    return 0;
}
