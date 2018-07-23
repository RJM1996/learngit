
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
    int listen_socket = 

}
