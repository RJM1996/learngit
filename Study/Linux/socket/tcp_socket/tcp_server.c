/*================================================================

# File Name: tcp_server.c
# Author: rjm
# mail: rjm96@foxmail.com
# Created Time: 2018年05月06日 星期日 11时24分35秒

================================================================*/


#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <string.h>
#include <pthread.h>

#define ADDR_FAMILY AF_INET

//定义一个结构体保存线程创建所执行函数需要的参数
typedef struct Arg
{
    int sockfd;
    struct sockaddr_in addr;
}Arg;


void* service(void* ptr)
{
    Arg* arg = (Arg*)ptr;

    char buf_ip[1024];
    //清空buf_ip
    buf_ip[0] = 0;
    //inet_ntop转换client_sock的ip
    if(inet_ntop(AF_INET, &arg->addr.sin_addr, buf_ip, sizeof(buf_ip)) == NULL)
    {
        perror("inet_ntop");
        return NULL;
    }

    while(1) 
    {
        //定义buf缓冲区
        char buf[1024];
        //清空
        buf[0] = 0;
        //从client_sock读取数据到buf
        ssize_t read_ret = read(arg->sockfd, buf, sizeof(buf));
        if(read_ret < 0)
        {
            perror("read");
            break;
        }
        if(read_ret == 0)
        {
            printf("[client %s:%d] leave! \n", buf_ip, arg->addr.sin_port);
            break;
        }
        printf("[client %s:%d] say: %s\n", buf_ip, arg->addr.sin_port, buf);

        //将buf中的数据写到client_sock
        //将消息回显给用户
        int write_ret = write(arg->sockfd, buf, sizeof(buf));
        if(write_ret < 0)
        {
            perror("write");
            break;
        }
        buf[strlen(buf)-1] = '\0';
    }
    free(arg);
    arg = NULL;
    return NULL;
}


int main(int argc, char* argv[])
{
    if(argc != 2)
    {
        printf("Usage: ./server [port > 1024]\n");
        return -1;
    }
    //1,打开socket 得到sock
    int sock = socket(AF_INET, SOCK_STREAM, 0);//ipv4, tcp 
    if(sock == -1)
    {
        perror("socket");
        return 1;
    }
    //2,定义两个sockaddr_in结构体的对象
    struct sockaddr_in server_socket;
    struct sockaddr_in client_socket;

    //3,结构体初始化
    server_socket.sin_family = AF_INET;
    server_socket.sin_port = htons(atoi(argv[1]));
    //server_socket.sin_addr.s_addr = inet_addr(argv[1]);
    server_socket.sin_addr.s_addr = INADDR_ANY;

    //4,绑定(sock和server_sock绑定)
    int bind_ret = bind(sock, (struct sockaddr*)&server_socket, sizeof(struct sockaddr_in));
    if(bind_ret == -1)
    {
        perror("bind");
        return 2;
    }

    //5,监听
    int listen_ret = listen(sock, 5);
    if(listen_ret == -1)
    {
        perror("listen");
        return 3;
    }

    //走到这说明绑定和监听成功
    printf("Wecome to Online Chat Server\n");

    //6,循环, 获得client_sock
    while(1)
    {
        socklen_t addrlen = sizeof(struct sockaddr_in);
        //获得client_sock;
        int client_sock = accept(sock, (struct sockaddr*)&client_sock, &addrlen);
        //定义buf_ip缓冲区
        char buf_ip[1024];
        //清空buf_ip
        buf_ip[0] = 0;
        //inet_ntop转换client_sock的ip
        if(inet_ntop(AF_INET, &client_socket.sin_addr, buf_ip, sizeof(buf_ip)) == NULL)
        {
            perror("inet_ntop");
            return 4;
        }
        printf("[client %s:%d] connected\n",
                    buf_ip, client_socket.sin_port);

        //7,循环服务
#if 1
        //====================================多进程版本===========================================

        int pid = fork();
        if(pid == 0)
        {
            int id = fork();
            if(id == 0)
            {
                //孙子进程
                while(1) 
                {
                    //定义buf缓冲区
                    char buf[1024];
                    //清空
                    buf[0] = 0;
                    //从client_sock读取数据到buf
                    ssize_t read_ret = read(client_sock, buf, sizeof(buf));
                    if(read_ret < 0)
                    {
                        perror("read");
                        break;
                    }
                    if(read_ret == 0)
                    {
                        printf("[client %s:%d] leave! \n", buf_ip, client_socket.sin_port);
                        break;
                    }
                    printf("[client %s:%d] say: %s\n", buf_ip, client_socket.sin_port, buf);

                    //将buf中的数据写到client_sock
                    //将消息回显给用户
                    int write_ret = write(client_sock, buf, sizeof(buf));
                    if(write_ret < 0)
                    {
                        perror("write");
                        break;
                    }
                    buf[strlen(buf)-1] = '\0';
                }
            }
        }
#endif

#if 0
        //====================================多线程版本===========================================

        pthread_t tid;
        Arg* arg = (Arg*)malloc(sizeof(Arg)); 
        arg->sockfd = client_sock;
        arg->addr = client_socket;
        int pthread_ret = pthread_create(&tid, NULL, service, (void*)arg);
        if(pthread_ret < 0)
        {
            perror("pthread_create");
            return 5;
        }
        // 线程分离
        pthread_detach(tid);
#endif

    }
    //8,服务完毕 关闭sock
    close(sock);
    return 0;
}
