
#include "epoll_http.h"

// 1. 获取监听套接字
int StartUp(int port)
{
    if(port < 1024)
    {
        printf("port must > 1024 ! \n");
        return 2;
    }

    struct sockaddr_in addr;
    addr.sin_family = AF_INET; // ipv4 协议族
    addr.sin_port = htons(port); // 主机字节序转为网络字节序
    addr.sin_addr.s_addr = INADDR_ANY; // INADDR_ANY 转换过来就是0.0.0.0，泛指本机

    int listen_socket = socket(AF_INET, SOCK_STREAM, 0);
    if(listen_socket < 0)
    {
        printf("创建 socket 失败\n");
        perror("socket");
        return 3;
    }

    // 解决 TIME-WAIT 引起的 bind 失败问题
    int opt = 1;
    setsockopt(listen_socket, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt));

    // 绑定
    if(bind(listen_socket, (struct sockaddr*)&addr, sizeof(addr)) < 0)
    {
        printf("绑定失败\n");
        perror("bind");
        return 4;
    }
    // 监听
    if(listen(listen_socket, 5) < 0)
    {
        printf("监听失败\n");
        perror("listen");
        return 5;
    }
    return listen_socket;
}
