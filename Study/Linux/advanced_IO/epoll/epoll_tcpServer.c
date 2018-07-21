/*================================================================

# File Name: epoll_tcpServer.c
# Author: rjm
# mail: rjm96@foxmail.com
# Created Time: 2018年06月06日 星期三 15时01分14秒

================================================================*/


// epoll 的 LT 和 ET 模式

#include <stdio.h>
#include <stdlib.h>
#include <sys/epoll.h>
#include <fcntl.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <string.h>
#include <unistd.h>
#include <assert.h>
#include <errno.h>

#define MAX_EVENT_SIZE 1024
#define BUF_SIZE 10

// 将文件描述符设置为非阻塞的
void setnonblocking(int fd)
{
    int old_option = fcntl(fd, F_GETFL);
    int new_option = old_option | O_NONBLOCK;
    if(fcntl(fd, F_SETFL, new_option) == -1)
    {
        exit(-1);
        perror("fcntl");
    }
}

// 注册文件描述符和事件 
void _epoll_add(int epoll_fd, int fd, int mode_flag) // mode_flag 表示是否对 fd 启用 ET 模式
{
    struct epoll_event event;
    event.data.fd = fd;
    event.events = EPOLLIN;
    if(mode_flag == 1)
    {
        event.events |= EPOLLET;
    }
    setnonblocking(fd);
    epoll_ctl(epoll_fd, EPOLL_CTL_ADD, fd, &event);
}

// 获取监听套接字的接口
int _startUp(int port)
{
    if(port < 1024)
    {
        printf("Usage: ./server [port > 1024]\n");
        return 2;
    }
    struct sockaddr_in addr;
    bzero((void*)&addr, sizeof(addr));
    addr.sin_family = AF_INET;
    addr.sin_port = htons( port );
    addr.sin_addr.s_addr = INADDR_ANY;

    int listen_fd = socket(AF_INET, SOCK_STREAM, 0);
    if(listen_fd < 0)
    {
        perror("socket");
        return 3;
    }

    // 解决因为 timeout 引起的 bind 失败问题
    int opt = 1;
    setsockopt(listen_fd, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt));

    if(bind(listen_fd, (struct sockaddr*)&addr, sizeof(addr)) < 0)
    {
        perror("bind");
        return 4;
    }

    if(listen(listen_fd, 5) < 0)
    {
        perror("listen");
        return 5;
    }

    return listen_fd;
}

// LT 模式的工作流程
void lt(struct epoll_event* evs, int size, int epfd, int listen_fd)
{
    assert(evs != NULL);
    char buf[MAX_EVENT_SIZE];
    for(int i = 0; i < size; i++)
    {
        int sock_fd = evs[i].data.fd;
        if(sock_fd == listen_fd)
        {
            struct sockaddr_in client_addr;
            socklen_t client_addr_len = sizeof(client_addr);
            int connect_fd = accept(listen_fd, (struct sockaddr*)&client_addr, &client_addr_len);
            if(connect_fd < 0)
            {
                perror("accept");
                continue;
            }
            _epoll_add(epfd, connect_fd, 0); // 此时对 connect_fd 不使用 ET 模式
        }
        else if(evs[i].events & EPOLLIN)
        {
            printf("read event trigger ! \n");
            memset(buf, 0, BUF_SIZE);
            // int recv( _In_ SOCKET s, _Out_ char *buf, _In_ int len, _In_ int flags );
            int recv_ret = recv(sock_fd, buf, BUF_SIZE-1, 0);
            if(recv_ret <= 0)
            {
                close(sock_fd);
                continue;
            }
            printf("get %d bytes of content : %s\n", recv_ret, buf);
        }
        else
        {
            printf("other thing happend ... \n");
        }
    }
}

// ET 模式的工作流程
void et(struct epoll_event* evs, int size, int epfd, int listen_fd)
{
    assert(evs != NULL);
    char buf[MAX_EVENT_SIZE];
    for(int i = 0; i < size; i++)
    {
        int sock_fd = evs[i].data.fd;
        if(sock_fd == listen_fd)
        {
            struct sockaddr_in client_addr;
            socklen_t client_addr_len = sizeof(client_addr);
            int connect_fd = accept(listen_fd, (struct sockaddr*)&client_addr, &client_addr_len);
            if(connect_fd < 0)
            {
                perror("accept");
                continue;
            }
            _epoll_add(epfd, connect_fd, 1); // 此时对 connect_fd 使用 ET 模式
        }
        else if(evs[i].events & EPOLLIN)
        {
            printf("read event trigger ! \n");
            // int recv( _In_ SOCKET s, _Out_ char *buf, _In_ int len, _In_ int flags );
            while(1)
            {
                // 非阻塞地读
                memset(buf, 0, BUF_SIZE);
                int recv_ret = recv(sock_fd, buf, BUF_SIZE-1, 0);
                if(recv_ret < 0)
                {
                    if(errno == EAGAIN || errno == EWOULDBLOCK)
                    {
                        printf("read at last !\n");
                        break;
                    }
                    close(sock_fd);
                    break;
                }
                else if(recv_ret == 0)
                {
                    close(sock_fd);
                }
                else
                {
                    printf("get %d bytes of content : %s\n", recv_ret, buf);
                }
            }
        }
        else
        {
            printf("other thing happend ... \n");
        }
    }
}


int main(int argc, char* argv[])
{
    if(argc != 2)
    {
        printf("Usage: ./server [port > 1024]\n");
        return 1;
    }

    // 1, 获取监听套接字
    int listen_sock = _startUp(atoi(argv[1]));

    // 2, 设置 event 数组, 创建epoll模型, 注册监听套接字
    // setEventArr_SignInListen()
    struct epoll_event evs[MAX_EVENT_SIZE];
    int epoll_fd = epoll_create(5);
    if(epoll_fd == -1)
    {
        perror("epoll_create");
        return 6;
    }
    // 注册监听套接字
    _epoll_add(epoll_fd, listen_sock, 1);

    // 3, 开始循环等待, 连接, 服务
    while(1)
    {
        int epoll_wait_ret = epoll_wait(epoll_fd, evs, MAX_EVENT_SIZE, -1);
        if(epoll_wait_ret == -1)
        {
            perror("epoll_wait_ret");
            return 7;
        }

        // 4, 使用 LT 或 ET 模式
        //lt(evs, epoll_wait_ret, epoll_fd, listen_sock);
        et(evs, epoll_wait_ret, epoll_fd, listen_sock);
    }
    close(listen_sock);
    close(epoll_fd);
    return 0;
}
