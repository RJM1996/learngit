/*================================================================

# File Name: poll_tcpServer.c
# Author: rjm
# mail: rjm96@foxmail.com
# Created Time: 2018年05月31日 星期四 20时57分39秒

================================================================*/



#include <stdio.h>
#include <poll.h>
#include <stdlib.h>
#include <sys/select.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <assert.h>

#define DEFAULT_FD_SIZE 1024
 
// 使用 poll 监控标准输入

//int main(int argc, char* argv[])
//{
//    struct pollfd poll_fd;
//    poll_fd.fd = 0; //标准输入 0
//    poll_fd.events = POLLIN; //读事件
//    while(1)
//    {
//        int ret = poll(&poll_fd, 1, 10000);
//        if(ret < 0)
//        {
//            perror("poll");
//            continue;
//        }
//        if(ret == 0)
//        {
//            printf("poll timeout !\n");
//            continue;
//        }
//        if(poll_fd.revents == POLLIN)
//        {
//            char buf[1024] = {0};
//            read(0, buf, sizeof(buf)-1);
//            printf("\n== %s \n", buf);
//        }
//    }
//
//}


// poll版本的单进程tcp服务器

void fd_init(struct pollfd* fd_list, int size)
{
    assert(fd_list);
    for(int i=0; i<size; i++)
    {
        fd_list[i].fd = -1;
        fd_list[i].events = 0;
        fd_list[i].revents = 0;
    }
}
void fd_add(int fd, struct pollfd* fd_list, int size)
{
    assert(fd_list);
    for(int i = 0; i<size; i++)
    {
        if(fd_list[i].fd == -1)
        {
            fd_list[i].fd = fd;
            fd_list[i].events = POLLIN;
            break;
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
    struct sockaddr_in addr;
    addr.sin_family = AF_INET;
    addr.sin_port = inet_addr(argv[1]);
    addr.sin_addr.s_addr = htons(INADDR_ANY);

    // 获取监听套接字
    int listen_fd = socket(AF_INET, SOCK_STREAM, 0);
    if(listen_fd < 0)
    {
        perror("socket");
        return -1;
    }
    // 绑定
    // int bind(int sockfd, const struct sockaddr *
    //          addr,socklen_t addrlen);
    int bind_ret = bind(listen_fd, 
                (struct sockaddr*)&addr, sizeof(addr));
    if(bind_ret < 0)
    {
        perror("bind");
        return -1;
    }
    // 监听
    // int listen(int sockfd, int backlog);
    int listen_ret = listen(listen_fd, 5);
    if(listen_ret < 0)
    {
        perror("listen");
        return -1;
    }
    // 定义文件描述符数组
    //struct pollfd* fd_list = (struct pollfd*)malloc(sizeof(struct pollfd) * DEFAULT_FD_SIZE);
    struct pollfd fd_list[1024];
    fd_init(fd_list, sizeof(fd_list)/sizeof(struct pollfd));

    // 添加listen_fd到fd_list中
    fd_add(listen_fd, fd_list, sizeof(fd_list)/sizeof(struct pollfd));

    while(1)
    {
        // int poll(struct pollfd *fds, nfds_t nfds, int timeout);
        int poll_ret = poll(fd_list, sizeof(fd_list)/sizeof(struct pollfd), 10000);
        if(poll_ret < 0)
        {
            perror("poll");
            continue;
        }
        if(poll_ret == 0)
        {
            printf("poll timeout !\n");
            continue;
        }
        for(int i = 0; i<sizeof(fd_list)/sizeof(struct pollfd); i++)
        {
            if(fd_list[i].fd == -1)
            {
                continue;
            }
            if((fd_list[i].revents & POLLIN) != 1)
            {
                continue;
            }
            if(fd_list[i].fd == listen_fd)
            {
                // 处理是监听套接字的情况
                struct sockaddr_in client_addr;
                socklen_t len = sizeof(client_addr);
                int connect_fd = accept(listen_fd, (struct sockaddr*)&client_addr, &len);
                if(connect_fd < 0)
                {
                    perror("accept");
                    continue;
                }
                fd_add(connect_fd, fd_list, sizeof(fd_list)/sizeof(struct pollfd));
            }
            else
            {
                // 处理 connect_fd 的情况
                char buf[1024];
                int read_ret = read(fd_list[i].fd, buf, sizeof(buf)-1);
                if(read_ret < 0)
                {
                    perror("read");
                    exit(1);
                }
                if(read_ret == 0)
                {
                    printf("client quit !\n");
                    close(fd_list[i].fd);
                    fd_list[i].fd = -1;
                }
                buf[read_ret] = '\0';
                printf("client say : %s\n", buf);
            }
        } // 第二重循环
    } // 第一重循环
    return 0;
}
