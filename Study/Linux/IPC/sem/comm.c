
#include "comm.h"

//设置信号量
int commSemSet(int nums, int flags)
{
    //获取 key
    key_t key = ftok(PATHNAME, PROJ_ID);
    if(key < 0)
    {
        perror("ftok");
        return -1;
    }
    //获取 semid
    //int semget(key_t key, int nsems, int semflg);
    //key：所创建或打开信号量集的键值。
    //nsems：创建的信号量集中的信号量的个数，该参数只在创建信号量集时有效。
    //semflg：调用函数的操作类型，也可用于设置信号量集的访问权限，两者通过or表示
    //如果成功，则返回信号量集的IPC标识符。
    //如果失败，则返回-1
    int semid = semget(key, nums, flags);
    if(semid < 0)
    {
        perror("semget");
        return -1;
    }
    return semid;
}

//创建信号量 权限666
int createSemSet(int nums)
{
    return commSemSet(nums, IPC_CREAT|IPC_EXCL|0666);
}

int getSemSet(int nums)
{
    return commSemSet(nums, IPC_CREAT);
}

//初始化信号量
int initSem(int semid, int nums, int initVal)
{
    union semun un;
    un.val = initVal;
    //int semctl(int semid,int semnum,int cmd, /*union semun arg*/);
    //第一个参数是信号量集IPC标识符。第二个参数是操作信号在信号集中的编号，第一个信号的编号是0
    //SETVAL设置信号量集中的一个单独的信号量的值。
    //参数arg代表一个semun的实例。semun是在linux/sem.h中定义的：
    ///*arg for semctl systemcalls.*/
    //union semun{
    //  int val;/*value for SETVAL*/
    //  struct semid_ds *buf;/*buffer for IPC_STAT&IPC_SET*/
    //  ushort *array;/*array for GETALL&SETALL*/
    //  struct seminfo *__buf;/*buffer for IPC_INFO*/
    //  void *__pad;
    //}
    if(semctl(semid, nums, SETVAL, un)<0)
    {
        perror("semctl");
        return -1;
    }
    return 0;
}

//P V 操作
int commPV(int semid, int who, int op)
{
    //在 Linux 下，PV 操作通过调用semop函数来实现。
    struct sembuf sf;
    sf.sem_num = who;
    sf.sem_op = op;
    sf.sem_flg = 0;
    //int semop(int semid, struct sembuf *sops, unsigned nsops);
    //semid：信号集的识别码，可通过semget获取。
    //sops：指向存储信号操作结构的数组指针，信号操作结构的原型如下
    //struct sembuf
    //{
    //  unsigned short sem_num; /* semaphore number */
    //  short sem_op; /* semaphore operation */
    //  short sem_flg; /* operation flags */
    //};
    //sem_op：如果其值为正数，该值会加到现有的信号内含值中。通常用于释放所控资源的使用权；
    //如果sem_op的值为负数，而其绝对值又大于信号的现值，操作将会阻塞，直到信号值大于或等于sem_op的绝对值。
    //nsops：信号操作结构的数量，恒大于或等于1。
    if(semop(semid, &sf, 1) < 0)
    {
        perror("semop");
        return -1;
    }
    return 0;
}


int P(int semid, int who)
{
    return commPV(semid, who, -1);
}

int V(int semid, int who)
{
    return commPV(semid, who, 1);
}


//销毁信号量
int destroySemSet(int semid)
{
    if(semctl(semid, 0, IPC_RMID) < 0)
    {
        perror("semctl");
        return -1;
    }
    return 0;
}
