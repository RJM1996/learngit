
#include "comm.h"

int main()
{
    //创建一块大小为 4096 字节的共享内存
    int shmid = createShm(4096);

    //连接共享内存标识符为shmid的共享内存，连接成功后把共享内存区对象映射到调用进程的地址空间
    //随后可像本地空间一样访问
    //void *shmat(int shmid, const void *shmaddr, int shmflg)
    //msqid
    //共享内存标识符
    //shmaddr
    //指定共享内存出现在进程内存地址的什么位置，直接指定为NULL让内核自己决定一个合适的地址位置
    //shmflg
    //SHM_RDONLY：为只读模式，其他为读写模式
    //函数返回值 
    //成功：附加好的共享内存地址
    //出错：-1，错误原因存于error中

    //利用 shmat 函数连接共享内存
    char* address = shmat(shmid, NULL, 0);
    sleep(2);
    int i = 0;

    while(i++ < 30)
    {
        printf("client say: %s\n", address);
        sleep(1);
    }

    //shmdt与shmat函数相反，是用来断开与共享内存附加点的地址，禁止本进程访问此片共享内存
    //int shmdt(const void *shmaddr)
    //函数传入值
    //shmaddr：连接的共享内存的起始地址
    //函数返回值
    //成功：0
    //出错：-1，错误原因存于error中
    //本函数调用并不删除所指定的共享内存区，而只是将先前用shmat函数连接好的共享内存脱离目前的进程

    //利用 shmdt 函数断开与共享内存的连接
    shmdt(address);
    sleep(2);
    //销毁共享内存
    destoryShm(shmid);

    return 0;
}
