
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <errno.h>

//父子进程通过匿名管道进行通信

//错误处理
#define ERR_EXIT(m)     \ 
do                      \ 
{                       \ 
    perror(m);          \
    exit(EXIT_FAILURE); \
}while(0);

int main(int agrc, char argv[])
{
    int fds[2];
    //创建匿名管道
    if(pipe(fds) != 0)
    {
        ERR_EXIT("pipe error");
        return -1;
    }

    //创建子进程
    pid_t pid = fork();
    if(pid == -1)
    {
        ERR_EXIT("fork error");
        return -1;
    }

    //子进程
    if(pid == 0)
    {
        //关闭子进程的读端
        close(fds[0]);
        //往写端写入hello
        if(write(fds[1], "hello", 5) == -1)
        {
            ERR_EXIT("write error");
            return -1;
        }
        close(fds[1]);
    }

    //父进程
    //关闭父进程的写端
    close(fds[1]);
    char buf[10] = {0};
    //从读端读入到buf
    if(read(fds[0], buf, 5) > 0)
    {
        printf("buf = %s\n", buf);
    }
    return 0;
}
