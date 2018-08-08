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


int client(char* arg)
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

    while(1)
    {
        (void)arg;
        // 解析 arg 里面的请求数据
        // 然后发给 tcp 服务器 
        // TODO
        char buf[BUF_SIZE] = {0};
        // arg:button=open
        char flag[256];
        int id;
        sscanf(arg, "button=%s&id=%d", flag, &id);
        if(strcmp(flag, "open") == 0)
        {
            switch(id)
            {
            case 1:
                {
                    // 如果是命令是 open 设备id = 1, 就给服务器发送:app open 1
                    const char* open_id01 = "app open 1";
                    if(write(fd, open_id01, sizeof(open_id01)) == -1)
                    {
                        perror("write");
                        return 404;
                    }
                    break;
                }

            case 2:
                {
                    const char* open_id02 = "app open 2";
                    if(write(fd, open_id02, sizeof(open_id02)) == -1)
                    {
                        perror("write");
                        return 404;
                    }
                    break;
                }
            default:
                break;
            }
        } // if open end

        if(strcmp(flag, "close") == 0)
        {
            switch(id)
            {
            case 1:
                {
                    // 如果是命令是 close 设备id = 1, 就给服务器发送:app close 1
                    const char* close_id01 = "app close 1";
                    if(write(fd, close_id01, sizeof(close_id01)) == -1)
                    {
                        perror("write");
                        return 404;
                    }
                    break;
                }

            case 2:
                {
                    const char* close_id02 = "app close 2";
                    if(write(fd, close_id02, sizeof(close_id02)) == -1)
                    {
                        perror("write");
                        return 404;
                    }
                    break;
                }
            default:
                break;
            }
        } // if close end

        // 接收 tcp 服务器的回应
        ssize_t read_size = read(fd, buf, sizeof(buf)-1);
        if(read_size == -1)
        {
            perror("read");
            continue;
        }
        if(read_size == 0)
        {
            printf("server busy");
            break;
        }
        // 收到 tcp服务器的回应, 根据回应判断是否控制成功
        // 再将结果返回给 app 客户端
        
        printf("<html>");
        printf("<meta charset=utf-8>");
        printf("<h2>%s</h2>", buf);
        printf("</html>");
    }

    return 0;
}

int main()
{
    char* method = NULL;
    char* query_string = NULL;
    char* arg = NULL;
    int content_len = -1;
    char buf[BUF_SIZE];
    if(getenv("METHOD") != NULL)
    {
        method = getenv("METHOD");
        if(strcasecmp(method, "GET") == 0)
        {
            if(getenv("QUERY_STRING") != NULL)
            {
                query_string = getenv("QUERY_STRING");
                arg = query_string;
            }
        }
        else
        {
            // post
            if(getenv("CONTENT_LENGTH") != NULL)
            {
                content_len = atoi(getenv("CONTENT_LENGTH"));
                int i = 0;
                for(; i < content_len; i++)
                {
                    read(0, &buf[i], 1);
                }
                buf[i] = '\0';
                arg = buf;
            }
        }
        // 此时 buf 里存的就是 app 发来的请求
        // 然后把 buf 传给 client
        // 由client解析请求数据, 根据app的请求, 再向 tcp 服务器发送请求, 控制终端
        client(arg);
    }
}
