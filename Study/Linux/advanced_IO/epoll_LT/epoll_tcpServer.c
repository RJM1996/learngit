/*================================================================

# File Name: epoll_tcpServer.c
# Author: rjm
# mail: rjm96@foxmail.com
# Created Time: 2018年06月03日 星期日 14时01分07秒

================================================================*/


// IO 多路转接之 epoll

#include <stdio.h>
#include <stdlib.h>
#include <sys/epoll.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h> 
#include <arpa/inet.h>
#include <unistd.h>
#include <string.h>
#include <fcntl.h>


#define MAX 128
#define HOME_PAGE "webroot/index.html"

// 获取监听套接字
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

    // 避免 timewait 引起的绑定失败问题
    int opt = 1;
    setsockopt(listen_fd, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt));

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

// 监听套接字就绪, 开始连接
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
    // 将这个新获取的套接字添加到epoll_fd中
    struct epoll_event ev;
    ev.data.fd = connect_fd;
    ev.events = EPOLLIN;
    int ret = epoll_ctl(epoll_fd, EPOLL_CTL_ADD, connect_fd, &ev);
    if(ret < 0)
    {
        perror("epoll_ctl");
        return ;
    }
}

// 正常客户端就绪
void service(int client, int epoll_fd)
{
    char buf[1024] = {0};
    int ret = read(client, buf, sizeof(buf)-1);
    if(ret < 0)
    {
        perror("read");
        return ;
    }
    if(ret == 0)
    {
        printf("\nclient quit !\n");
        close(client);
        epoll_ctl(epoll_fd, EPOLL_CTL_DEL, client, NULL);
        return ;
    }
    buf[ret] = 0;
    printf("%s", buf);
    //printf("\n=====================================\n");
    //printf("client say : %s \n", buf);
    //printf("\n=====================================\n");

    char* home = HOME_PAGE;
    int fd = open(home, O_RDONLY);
    if(fd < 0)
    {
        perror("open");
        exit(1);
    }
    // char index[] = "<head><h1>hello, world</h1></head>";
    // ssize_t recv(int sockfd, void *buf, size_t len, int flags);
    char index[4096];
    ssize_t read_ret = read(fd, index, sizeof(index));
    if(read_ret == -1)
    {
        perror("read");
        exit(1);
    }
    char rev[8192];
    sprintf(rev, "HTTP/1.0 200 OK\r\nContent-Length: %u\r\n\r\n%s", sizeof(index), index);
    send(client, rev, sizeof(rev), 0);

    // ssize_t send(int sockfd, const void *buf, size_t len, int flags);

    //sprintf(rev, "HTTP/1.0 200 OK\r\n");
    //send(client, rev, sizeof(rev), 0);

    //sprintf(rev, "Content-Length: %u\r\n", sizeof(index));
    //send(client, rev, sizeof(rev), 0);

    //sprintf(rev, "\r\n");
    //send(client, rev, sizeof(rev), 0);

    //sprintf(rev, "%s", index);

    close(fd);
    printf("%s", rev);
}

int main(int argc, char* argv[])
{
    if(argc != 2)
    {
        printf("Usage: ./server [port > 1024]\n");
        return 1;
    }
    // 获取监听套接字
    int listen_sock = startUp(atoi(argv[1]));

    // 创建 epoll 模型
    int epfd = epoll_create(128);

    // 将监听套接字注册到 epoll 模型中
    // int epoll_ctl(int epfd, int op, int fd, struct epoll_event *event);
    struct epoll_event ev;
    ev.events = EPOLLIN;
    ev.data.fd = listen_sock;
    int epoll_ctl_ret = epoll_ctl(epfd, EPOLL_CTL_ADD, listen_sock, &ev);
    if(epoll_ctl_ret < 0)
    {
        perror("epoll_ctl");
        return 6;
    }

    // 等待连接, 循环服务
    while(1)
    {
        struct epoll_event events[MAX];
        // 等待事件就绪
        // int epoll_wait(int epfd, struct epoll_event *events,
        //                int maxevents, int timeout);
        int epoll_wait_ret = epoll_wait(epfd, events, MAX, -1); // 设为 -1 , 始终阻塞
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
        for(int i = 0; i < epoll_wait_ret; i++)
        {
            // 如果不是读事件就绪
            if(!(events[i].events & EPOLLIN))
            {
                continue;
            }
            // 如果是监听套接字就绪
            if(events[i].data.fd == listen_sock)
            {
                // 开始进行连接
                getConnect(listen_sock, epfd);
            }
            else
            {
                // 说明是正常客户端的读事件就绪, 开始服务
                service(events[i].data.fd, epfd);
            }
        } // 第二重循环结束
    } // 第一重循环结束
    return 0;
}
