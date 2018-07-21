/*================================================================

# File Name: udp_client.c
# Author: rjm
# mail: rjm96@foxmail.com
# Created Time: 2018年05月03日 星期四 08时30分52秒

================================================================*/


#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>  
#include <sys/socket.h>
#include <arpa/inet.h>
#include <string.h>
#include <unistd.h>

int main(int argc, char* argv[])
{
    if(argc != 3)
    {
        printf("Usage: ./udp_client [ip] [port]\n");
        return 1;
    }

    //1, 创建 socket 文件描述符
    int sockfd = socket(AF_INET,SOCK_DGRAM,0);//AF_INET 表示ipv4协议
    //SOCK_DGRAM 表示支持 udp 连接
    //通常某协议中只有一种特定类型，这样protocol参数设置为0
    if(sockfd < 0)
    {
        perror("socket");
        return 2;
    }
    //初始化 sockaddr_in 结构体
    struct sockaddr_in server;
    server.sin_family = AF_INET; //ipv4协议
    server.sin_port = htons(atoi(argv[2])); //第三个参数是端口号
    server.sin_addr.s_addr = inet_addr(argv[1]); //第二个参数是ip地址
    //inet_addr函数功能是将一个点分十进制的ip
    //转换成一个u long型的整数

    char buf[1024] = {0};
    struct sockaddr_in peer;
    while(1)
    {
        socklen_t len = sizeof(peer);
        printf("Please Enter: ");
        fflush(stdout);
        ssize_t s = read(0, buf, sizeof(buf)-1);
        if(s > 0)
        {
            //成功
            buf[s-1] = 0; //将第一个设置为0, 以清空缓冲区, -1是因为read会把\n读进来, -1把\n减去
            //int sendto ( socket s , const void * msg, int len, unsigned int flags, 
            //             const struct sockaddr * to , int tolen ) ;
            //sendto()用来将数据由指定的socket传给对方主机。
            //参数s为已建好连线的socket
            //如果利用UDP协议则不需经过连线操作
            //参数msg指向欲连线的数据内容
            //参数flags一般设0 
            //参数to用来指定欲传送的网络地址
            //参数tolen为sockaddr的结构长度
            sendto(sockfd, buf, strlen(buf), 0, (struct sockaddr*)&server, sizeof(server));
            ssize_t size = recvfrom(sockfd, buf, sizeof(buf)-1, 0, (struct sockaddr*)&peer, &len);
            if(size > 0)
            {
                buf[size] = 0;
                printf("server echo: %s\n", buf);
            }
        }
    }
}
