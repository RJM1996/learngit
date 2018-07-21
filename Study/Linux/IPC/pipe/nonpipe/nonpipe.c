
//匿名管道

#include <stdio.h>
#include <string.h>
#include <unistd.h>

//创建一个匿名管道 fd:文件描述符数组  fd[0]:读端  fd[1]:写端
//成功返回 0 , 失败返回错误代码
int pipe(int fd[2]);

//创建一个匿名管道, 从键盘写入数据到管道, 从管道读取数据, 显示到屏幕
int main()
{
    int fds[2];
    char buf[1024];
    int len = 0;

    if(pipe(fds) != 0)
    {
        perror("pipe");
        return -1;
    }

    //从键盘读数据
    //char *fgets(char *buf, int bufsize, FILE *stream);
    //参数
    //*buf: 字符型指针，指向用来存储所得数据的地址。
    //bufsize: 整型数据，指明存储数据的大小。
    //*stream: 文件结构体指针，将要读取的文件流。
    while(fgets(buf, 1024, stdin) != NULL)
    {
        len = strlen(buf);
        //数据写入管道
        //ssize_t write(int fd, const void *buf, size_t nbyte);
        //fd：文件描述符；
        //buf：指定的缓冲区，即指针，指向一段内存单元；
        //nbyte：要写入文件指定的字节数；
        //返回值：写入文档的字节数（成功）；-1（出错）
        if(write(fds[1], buf, len) < 0)
        {
            perror("write");
            break;
        }
        //清空buf
        //void *memset(void *s, int ch, size_t n);
        //函数解释：将s中当前位置后面的n个字节 （typedef unsigned int size_t ）用 ch 替换并返回 s 。
        //memset：作用是在一段内存块中填充某个给定的值，它是对较大的结构体或数组进行清零操作的一种最快方法
        memset(buf, 0x00, sizeof(buf));

        //从管道读取数据
        //函数名: read
        //功 能: 从文件中读
        //用 法: int read(int handle, void *buf, int nbyte);
        if(read(fds[0], buf, 1024) < 0)
        {
            perror("read");
            return -1;
        }

        len = strlen(buf);

        //写到屏幕上
        if(write(1, buf, len) < 0)
        {
            perror("write");
            return -1;
        }
    }
}
