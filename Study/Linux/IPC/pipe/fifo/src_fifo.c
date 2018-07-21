
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
//把数据从abc文件写入管道

int main()
{
    //创建一个名为 tmp 的命名管道, 权限664
    mkfifo("tmp", 0664);
    //以只读方式打开 abc 文件
    int in_fd = open("abc", O_RDONLY);
    if(in_fd == -1)
    {
        ERR_EXIT("open error");
    }

    //以读写方式打开 tmp 管道文件
    int out_fd = open("tmp", O_WRONLY);
    if(out_fd == -1)
    {
        ERR_EXIT("open error");
    }

    char buf[1024] = {0};
    int len = 0;

    //从in_fd读数据到buf
    if((len = read(in_fd, buf, 1024)) > 0)
    {
        //从buf写数据到out_fd
        write(out_fd, buf, len);
    }

    close(in_fd);
    close(out_fd);

    return 0;
}
