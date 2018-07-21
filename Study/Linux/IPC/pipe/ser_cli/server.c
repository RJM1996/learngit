
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
    umask(0);
    //创建 tmp 管道, 权限664
    if ( mkfifo("tmp", 0664) < 0 )
    {
        ERR_EXIT("mkfifo error");
    }

    //只读打开 tmp 管道文件
    int rfd = open("tmp", O_RDONLY);
    if(rfd == -1)
    {
        ERR_EXIT("opne error");
    }

    char buf[1024] = {0};
    while(1)
    {
        buf[0] = 0;
        printf("Please Wait ... \n");

        size_t s = read(rfd, buf, sizeof(buf)-1);
        if(s > 0)
        {
            buf[s-1] = 0;
            printf("client say: %s\n", buf);
        }
        if(s == 0)
        {
            printf("client quit, me too \n");
            exit(EXIT_SUCCESS);
        }
        if(s < 0)
        {
            ERR_EXIT("read error");
        }
    }

    close(rfd);
    return 0;
}
