
#include "comm.h"

//创建共享内存
int CommShm(int size, int flags)
{
    //通过 ftok 函数得到 key
    key_t key = ftok(PATHNAME, PROJ_ID);
    if(key < 0)
    {
        perror("ftok");
        return -1;
    }

    //通过 shmget 函数得到 shmid
    //得到一个共享内存标识符或创建一个共享内存对象并返回共享内存标识符
    //int shmget(key_t key, size_t size, int shmflg)
    //key
    //0(IPC_PRIVATE)：会建立新共享内存对象
    //大于0的32位整数：视参数shmflg来确定操作。通常要求此值来源于ftok返回的IPC键值
    //size
    //大于0的整数：新建的共享内存大小，以字节为单位
    //0：只获取共享内存时指定为0
    //shmflg
    //0：取共享内存标识符，若不存在则函数会报错
    //IPC_CREAT：当shmflg&IPC_CREAT为真时，如果内核中不存在键值与key相等的共享内存，则新建一个共享内存；
    //如果存在这样的共享内存，返回此共享内存的标识符
    //IPC_CREAT|IPC_EXCL：如果内核中不存在键值与key相等的共享内存，则新建一个共享内存；如果存在这样的共享内存则报错
    //成功：返回共享内存的标识符
    //出错：-1，错误原因存于error中
    int shmid = shmget(key, size, flags);
    if(shmid == -1)
    {
        perror("shmget");
        return -1;
    }

    return shmid;
}


int createShm(int size)
{
    //创建一个大小为 size 的共享内存, 权限666
    return CommShm(size, IPC_CREAT|IPC_EXCL|0666);
}

int getShm(int size)
{
    return CommShm(size, IPC_CREAT);
}

int destoryShm(int shmid)
{
    //完成对共享内存的控制
    //int shmctl(int shmid, int cmd, struct shmid_ds *buf)
    //shmid
    //共享内存标识符
    //cmd
    //IPC_STAT：得到共享内存的状态，把共享内存的shmid_ds结构复制到buf中
    //IPC_SET：改变共享内存的状态，把buf所指的shmid_ds结构中的uid、gid、mode复制到共享内存的shmid_ds结构内
    //IPC_RMID：删除这片共享内存
    //buf
    //共享内存管理结构体。不关心可设置为NULL
    //函数返回值
    //成功：0
    //出错：-1，错误原因存于error中
    //利用 shmctl 函数销毁共享内存标识符为 shmid 的共享内存
    if( shmctl(shmid, IPC_RMID, NULL) < 0 )
    {
        perror("shmctl");
        return -1;
    }

    return 0;
}
