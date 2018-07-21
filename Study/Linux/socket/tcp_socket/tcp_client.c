/*================================================================

# File Name: tcp_client.c
# Author: rjm
# mail: rjm96@foxmail.com
# Created Time: 2018年05月06日 星期日 11时24分19秒

================================================================*/


#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>  
#include <sys/socket.h>
#include <arpa/inet.h>
#include <strings.h>
#include <unistd.h>
#include <string.h>
#include "proto.h"

#define ADDR_FAMILY AF_INET

// 定义两个通信对象
Request request;
Response response;

int main(int argc, char* argv[])
{
    if(argc != 3)
    {
        printf("Usage: ./client [ip] [port > 1024]\n");
        return 1;
    }
    printf("Welcome to Online Chat Client\n");
    //1, 打开socket
    int sock = socket(AF_INET, SOCK_STREAM, 0); //ipv4, tcp
    if(sock < 0)
    {
        perror("socket");
        return 2;
    }
    //2, 定义buf缓冲区 清空
    char buf[1024];
    buf[0] = 0;
    //3, 定义sockaddr_in对象server_sock
    struct sockaddr_in server_sock;
    //3, bzero() server_sock
    bzero(&server_sock, sizeof(struct sockaddr_in));

    //4, 初始化server_sock
    server_sock.sin_family = ADDR_FAMILY;
    server_sock.sin_port = htons(atoi(argv[2]));
    server_sock.sin_addr.s_addr = inet_addr(argv[1]);
    //5, 连接server
    int connect_ret = connect(sock, (struct sockaddr*)&server_sock, sizeof(struct sockaddr_in));
    if(connect_ret < 0)
    {
        perror("connect");
        return 3;
    }
    //6, 循环发送消息
    while(1)
    {
        //scanf("%d,%d\n", &request.a, &request.b);
        printf("Please Enter: ");
        fflush(stdout);
        fgets(buf, sizeof(buf), stdin);
        buf[strlen(buf)-1] = 0;
        //比较quit 退出
        if(strcmp(buf, "quit") == 0)
        {
            printf("bye!\n");
            break;
        }
        // 把buf中的数据写到sock
        int write_ret = write(sock, buf, sizeof(buf));
        if(write_ret < 0)
        {
            perror("write");
            return 4;
        }
        // 把sock中的数据读到buf
        int read_ret = read(sock, buf, sizeof(buf));
        printf("server echo: %s\n", buf);

       // int write_ret = write(sock, request, sizeof(Request));
       // int read_ret = read(sock, response, sizeof(Response));
    }
    //7, 结束关闭sock
    close(sock);

    return 0;
}
