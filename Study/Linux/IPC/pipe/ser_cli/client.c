
#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>

//利用命名管道实现server和client的对话

#define ERR_EXIT(m) \
    do{\
    perror(m);\
    exit(EXIT_FAILURE);\
    }while(0);

int main()
{
    //读写打开 tmp 管道文件
    int wfd = open("tmp", O_WRONLY);
    if(wfd < 0)
    {
        ERR_EXIT("opne error");
    }

    char buf[1024] = {0};
    while(1)
    {
        buf[0] = 0;
        printf("I say: ");
        fflush(stdout);

        size_t s = read(0, buf, sizeof(buf)-1);
        if(s > 0)
        {
            buf[s] = 0;
            write(wfd, buf, sizeof(buf)-1);
        }
        if(s <= 0)
        {
            ERR_EXIT("read error");
        }
    }

    close(wfd);
    return 0;
}
