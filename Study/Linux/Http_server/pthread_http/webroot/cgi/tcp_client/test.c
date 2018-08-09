#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netinet/in.h>

#define SERVER_IP "192.168.228.134"
#define SERVER_PORT 9999
#define BUF_SIZE 1024


int client()
{
    struct sockaddr_in addr;
    addr.sin_family = AF_INET;
    if(inet_aton(SERVER_IP, &addr.sin_addr) == 0)
    {
        perror("inet_aton");
    }
    addr.sin_port = htons((SERVER_PORT));

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

        const char* buf = "app open 1";
        if(write(fd, buf, strlen(buf))== -1)
        {
            perror("write");
        }

    return 0;
}



int main()
{
    client();
}
