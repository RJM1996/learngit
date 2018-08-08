
#include <stdio.h>
#include <poll.h>
#include <stdlib.h>
#include <string.h>
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
    addr.sin_addr.s_addr = INADDR_ANY;

    int listen_fd = socket(AF_INET, SOCK_STREAM, 0);
    if(listen_fd == -1)
    {
        perror("socket");
        return -1;
    }
    if( bind(listen_fd, (struct sockaddr*)&addr, sizeof(addr)) == -1 )
    {
        perror("bind");
        return -1;
    }

    if( listen(listen_fd, 5) == -1 )
    {
        perror("listen");
        return -1;
    }

    struct pollfd fd_list[1024];
    fd_init(fd_list, sizeof(fd_list)/sizeof(struct pollfd));
    fd_add(listen_fd, fd_list, sizeof(fd_list)/sizeof(struct pollfd));

    while(1)
    {
        int poll_ret = poll(fd_list, sizeof(fd_list)/sizeof(struct pollfd), 10000);
        if(poll_ret == -1)
        {
            perror("poll");
            continue;
        }
        if(poll_ret == 0)
        {
            printf("poll timeout !\n");
            continue;
        }
        for(size_t i = 0; i<sizeof(fd_list)/sizeof(struct pollfd); i++)
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
                write(fd_list[i].fd, buf, strlen(buf));
            }
        } // 第二重循环
    } // 第一重循环
    return 0;
}
