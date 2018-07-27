#include "epoll_http.h"

int main(int argc, char* argv[])
{
    if(argc != 2)
    {
        printf("Usage : ./server [port > 1024]\n");
        return 1;
    }

    // 首先要获取监听套接字
    int listen_sock = StartUp(atoi(argv[1]));

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
