
//练习open/read/write/close等文件相关系统调用接口，纵向对比fd与FILE结构体 
#include<stdio.h>
#include<sys/types.h>
#include<sys/stat.h>
#include<fcntl.h>
#include<string.h>
#include<unistd.h>

ssize_t read(int fd, void* buf, size_t count);
//从fd里读取count大小的数据到buf中

//ssize_t write(int fd, const void *buf, size_t nbyte);
ssize_t write(int fd, const void* buf, size_t nbyte);
//把buf中的nbyte大小的数据写入fd

const char* file = "hello,world\n";

int main()
{
    //int open(constchar*pathname,intflags);
    //int open(constchar*pathname,intflags,mode_tmode);
    //返回值：成功则返回文件描述符，否则返回-1
    int fd = open("myfile", O_RDWR | O_CREAT, 0664);
    if(fd < 0)
    {
        perror("open");
        return -1;
    }

    char* msg = "world,hello\n";
    ssize_t sw = write(fd, msg, strlen(file));
    printf("sw = %d\n", sw);
    if(sw < 0)
    {
        perror("write");
        return -1;
    }
    printf("写入成功\n");
    sleep(1);

    //off_t lseek(int filde,off_t offset ,int whence);
    //每一个已打开的文件都有一个读写位置，当打开文件时通常其读写位置是指向文件开头，
    //若是以附加的方式打开文件(如O_APPEND)，则读写位置会指向文件尾。
    //当read()或write()时，读写位置会随之增加，lseek()便是用来控制该文件的读写位置。
    //参数fildes 为已打开的文件描述词，参数offset 为根据参数whence来移动读写位置的位移数。
    //Offset：偏移量，每一读写操作所需要移动的距离，单位是字节的数量，可正可负（向前移，向后移）。
    lseek(fd,0,SEEK_SET);//令读写位置指向开头

    char buf[13];
    //while(1)
    {
        ssize_t sr = read(fd, buf, 12);
        printf("sr = %d\n", sr);
        //ssize_t read(int handle, void *buf, int nbyte);
        if( sr <= 0 )
        {
            perror("read error");
            return -1;
        }
        printf("读取成功\n");
    }
    printf("buf = %s\n", buf);
    //close(fd);
    return 0;
}
