
#include "epoll_http.h"

int main(int argc, char* argv[])
{
    if(argc != 2)
    {
        printf("Usage : %s [port > 1024]\n", argv[0]);
        return 1; // 用法错误
    }

    // 1. 获取监听套接字
    // int socket(int domain, int type, int protocol);
    int listen_socket = StartUp(atoi(argv[1])); // 传入端口号

    // 2. 循环获取新连接
    while(1)
    {
        struct sockaddr_in client;
        socklen_t client_len = sizeof(client);
        int connected_socket = accept(listen_socket, (struct sockaddr*)&client, &client_len);
        if(connected_socket < 0)
        {
            perror("accept");
            continue;
        }
        // 到这里说明已经获得一个新的连接了
        char buf_ip[1024];
        buf_ip[0] = '\0'; // 清空缓冲区
        // const char *inet_ntop(int af, 
        // const void *src, char *dst, socklen_t size);
        if(inet_ntop(AF_INET, &client.sin_addr, buf_ip, sizeof(buf_ip)) == NULL)
        {
            printf("IP 转换失败\n");
            perror("inet_ntop");
            return 4;
        }
        // 到这里已经获得客户端的 ip 地址和端口号了
        printf("get a new client : [%s | %d]\n", buf_ip, ntohs(client.sin_port));

        // 接下来就该处理客户端的请求了, 这里采用 IO 多路转接的 epoll ET 模式
        


        
    }
}
