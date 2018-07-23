/*================================================================

# File Name: http_server.c
# Author: rjm
# mail: rjm96@foxmail.com
# Created Time: 2018年05月28日 星期一 14时51分08秒

================================================================*/


#include <stdio.h>
#include <sys/socket.h> 
#include <netinet/in.h> 
#include <arpa/inet.h> 
#include <unistd.h> 
#include <string.h> 
#include <stdlib.h>

// 实现一个简单的 http服务器
int main(int argc, char* argv[])
{
    if(argc != 3)
    {
        printf("Usage: ./server [ip] [port]\n");
        return -1;
    }

    //1, 创建套接字
    //int socket(int domain, int type, int protocol);
    //因为http是基于tcp的, 所以用SOCK_STREAM, 可靠的
    int fd = socket(AF_INET, SOCK_STREAM, 0);
    if(fd < 0)
    {
        perror("socket");
        return -1;
    }
    struct sockaddr_in addr;
    addr.sin_family = AF_INET;
    // inet_addr 将一个点分十进制的IP转换成一个长整数型数（u_long类型）等同于inet_addr()。
    addr.sin_addr.s_addr = inet_addr(argv[1]);
    // htons是将整型变量从主机字节顺序转变成网络字节顺序 
    // 就是整数在地址空间存储方式变为高位字节存放在内存的低地址处。
    addr.sin_port = htons(atoi(argv[2]));

    //2, 绑定

    //int bind(int sockfd, const struct sockaddr *addr,
    //         socklen_t addrlen);
    int ret = bind(fd, (struct sockaddr*)&addr, sizeof(addr));
    if(ret < 0)
    {
        perror("bind");
        return -1;
    }

    //3, 监听
    // int listen(int sockfd, int backlog);
    ret = listen(fd, 5);
    if(ret < 0)
    {
        perror("listen");
        return -1;
    }

    //4, 连接
    while(1)
    {
        struct sockaddr_in client_addr;
        socklen_t len;
        //int accept(int sockfd, struct sockaddr *addr, socklen_t *addrlen);
        int client_fd = accept(fd, (struct sockaddr*)&client_addr, &len);
        if(client_fd < 0)
        {
            perror("accept");
            continue; //不断获取连接
        }
        char input_buf[10240] = {0};
        ssize_t read_size = read(client_fd, input_buf, sizeof(input_buf)-1);
        if(read_size < 0)
        {
            perror("read");
            return -1;
        }
        printf("[request] %s\n", input_buf);
        char buf[1024] = {0};
        const char* web_str = "<h1>hello, world</h1>";
        // int sprintf(char *str, const char *format, ...);
        int ret = sprintf(buf, "HTTP/1.0 200 OK\nContent-Length:%lu\n\n%s", strlen(web_str), web_str);
        if(ret < 0)
        {
            perror("sprintf");
            return -1;
        }
        // ssize_t write(int fd, const void *buf, size_t count);
        ssize_t i = write(client_fd, buf, sizeof(buf));
        if(i < 0)
        {
            perror("write");
            return -1;
        }
    }
    return 0;
}
