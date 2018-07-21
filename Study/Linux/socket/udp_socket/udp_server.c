/*================================================================

# File Name: udp_server.c
# Author: rjm
# mail: rjm96@foxmail.com
# Created Time: 2018年05月03日 星期四 08时32分03秒

================================================================*/


#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>  
#include <sys/socket.h>
#include <arpa/inet.h>
#include <string.h>

//socket的参数使用SOCK_DGRAM表示UDP 
//bind之后就可以直接进行通信了
//使用sendto和recvfrom来进行数据读写 

int main(int argc, char* argv[])
{
    if(argc != 2)
    {
        printf("Usage: ./udp_server [port > 1024]\n");
        return -1;
    }
    //1, 创建 socket 文件描述符
    int sockfd = socket(AF_INET,SOCK_DGRAM,0);//AF_INET 表示ipv4协议
    //SOCK_DGRAM 表示支持 udp 连接
    //通常某协议中只有一种特定类型，这样protocol参数设置为0
    if(sockfd < 0)
    {
        perror("socket");
        return 1;
    }

    //初始化 sockaddr_in 结构体
    struct sockaddr_in local;
    local.sin_family = AF_INET; //ipv4协议
    local.sin_port = htons(atoi(argv[1])); 
    local.sin_addr.s_addr = INADDR_ANY; 
    //inet_addr函数功能是将一个点分十进制的ip
    //转换成一个u long型的整数

    //2, 绑定端口号
    if(bind(sockfd, (struct sockaddr*)&local, sizeof(local)) != 0)
    {
        perror("bind");
        return 2;
    }

    //3, 绑定成功就可以直接进行通信了
    char buf[1024] = {0};
    struct sockaddr_in client;
    while(1)
    {
        socklen_t len = sizeof(client);
        //函数原型:ssize_t recvfrom(int sockfd,void *buf,size_t len,unsigned int flags,
        //                          struct sockaddr *from,socket_t *fromlen); 
        //ssize_t 相当于 long int，socket_t 相当于int
        //sockfd：标识一个已连接套接口的描述字。
        //buf：接收数据缓冲区。
        //len：缓冲区长度。
        //flags：调用操作方式。
        ssize_t s = recvfrom(sockfd, buf, sizeof(buf)-1, 0, (struct sockaddr*)&client, &len);
        if(s > 0)
        {
            //成功
            buf[s] = 0; //将第一个设置为0, 以清空缓冲区
            printf("[%s:%d]: %s\n", inet_ntoa(client.sin_addr), \
                        ntohs(client.sin_port), buf);
            //inet_ntoa将一个十进制网络字节序转换为点分十进制IP格式的字符串

            //int sendto ( socket s , const void * msg, int len, unsigned int flags, 
            //             const struct sockaddr * to , int tolen ) ;
            //sendto()用来将数据由指定的socket传给对方主机。
            //参数s为已建好连线的socket
            //如果利用UDP协议则不需经过连线操作
            //参数msg指向欲连线的数据内容
            //参数flags一般设0 
            //参数to用来指定欲传送的网络地址
            //参数tolen为sockaddr的结构长度
            sendto(sockfd, buf, strlen(buf), 0, (struct sockaddr*)&client, sizeof(client));
            //将接收到的数据返回给发送方
        }
    }
}

