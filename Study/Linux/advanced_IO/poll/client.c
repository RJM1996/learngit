#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>


int main(int argc, char* argv[])
{
    if(argc != 3)
    {
        printf("Usage: ./client [server_ip] [server_port]\n");
        return -1;
    }

    struct sockaddr_in addr;
    addr.sin_family = AF_INET;
    addr.sin_addr.s_addr = inet_addr(argv[1]);
    addr.sin_port = htons(atoi(argv[2]));



    int fd = socket(AF_INET, SOCK_STREAM, 0);
    if(fd == -1)
    {
        perror("socket");
        return -1;
    }
    if(connect(fd, (struct sockaddr*)&addr, sizeof addr) == -1)
    {
        perror("connect");
        return -1;
    }
    while(1)
    {
        printf("请输入> ");
        fflush(stdout);
        char buf[1024] = {0};
        read(0, buf, sizeof(buf)-1);
        if(write(fd, buf, sizeof(buf)-1) == -1)
        {
            perror("write");
            continue;
        }
        ssize_t read_size = read(fd, buf, sizeof(buf)-1);
        if(read_size == -1)
        {
            perror("read");
            continue;
        }
        if(read_size == 0)
        {
            printf("client close");
            break;
        }
        printf("server say: %s\n", buf);
    }
    close(fd);
    return 0;
}
