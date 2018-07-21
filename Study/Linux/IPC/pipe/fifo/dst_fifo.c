
//命名管道, 可用于不相关的进程间通信
//表头文件
#include<sys/types.h>
#include<sys/stat.h>
#include<unistd.h>
#include<errno.h>
#include<stdlib.h>
#include<stdio.h>
#include<fcntl.h>
//定义函数
//int mkfifo(const char* pathname,mode_t mode);
//若成功则返回0，否则返回-1，错误原因存于errno中

#define ERR_EXIT(m)     \                                                                                                
do                      \
{                       \
    perror(m);          \
    exit(EXIT_FAILURE); \
}while(0);


//用命名管道实现文件拷贝
//把数据从tmp文件写入abc_cp

int main()
{
    int out_fd = open("abc_cp", O_WRONLY | O_CREAT | O_TRUNC, 0664);
    if(out_fd == -1)
    {
        ERR_EXIT("open error");
    }

    int in_fd = open("tmp", O_RDONLY);
    if(in_fd == -1)
    {
        ERR_EXIT("open error");
    }

    char buf[1024] = {0};
    int len = 0;

    if((len = read(in_fd, buf, 1024)) > 0)
    {
        //从buf写数据到out_fd
        write(out_fd, buf, len);
    }

    close(in_fd);
    close(out_fd);
    unlink("tmp");
    return 0;
}
