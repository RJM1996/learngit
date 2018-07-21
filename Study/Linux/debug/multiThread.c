/*================================================================
  Copyright (C) 2018 Sangfor Ltd. All rights reserved.
# File Name: multiThread.c
# Author: rjm
# mail: rjm96@foxmail.com
# Created Time: 2018年04月22日 星期日 10时27分41秒

================================================================*/


//多线程 gdb 调试

#include <stdio.h>
#include <pthread.h>

void* thread1(void* arg)
{
    printf("i am thread1, my tid is : %lu \n", pthread_self());
    return NULL;
}

void* thread2(void* arg)
{
    printf("i am thread2, my tid is : %lu \n", pthread_self());
    return NULL;
}

int main()
{
    pthread_t tid1, tid2;

    //创建两个线程
    pthread_create(&tid1, NULL, thread1, NULL);
    pthread_create(&tid2, NULL, thread2, NULL);

    //等待进程
    pthread_join(tid1, NULL);
    pthread_join(tid2, NULL);

    return 0;
}
