/*************************************************************************
# File Name: test.c
# Author: rjm
# mail: rjm96@foxmail.com
# Created Time: 2018年04月21日 星期六 09时44分24秒
 ************************************************************************/
#include <unistd.h> 
#include <sys/types.h> 
#include <pthread.h> 
#include <semaphore.h>

#include <stdlib.h> 
#include <stdio.h> 
#include <errno.h> 
#include <string.h>


//基于固定大小环形队列的生产者--消费者模型

//一个生产者, 一个消费者
#define CONSUMERS_COUNT 1
#define PRODUCERS_COUNT 1
//队列大小为10
#define BUFFSIZE 10

//定义一个整形数组, 代表队列
int g_buffer[BUFFSIZE];

unsigned short in = 0;
unsigned short out = 0;
unsigned short produce_id = 0;
unsigned short consume_id = 0;

//定义两个全局的信号量
sem_t g_sem_full;
sem_t g_sem_empty;

//定义一把全局的互斥锁
pthread_mutex_t g_mutex;

//定义一个全局数组, 保存线程id
pthread_t g_thread[CONSUMERS_COUNT + PRODUCERS_COUNT]; 

//消费者函数
void *consume(void *arg)
{
    int i;
    int num = *(int *)arg;
    free(arg);

    while (1)
    {
        printf("%2d 等待缓冲区不为空\n", num);
        //等待信号量g_sem_empty, 将信号量的值 -1
        sem_wait(&g_sem_empty);
        //加锁
        pthread_mutex_lock(&g_mutex);

        for (i = 0; i < BUFFSIZE; i++)
        {
            printf("%2d ", i);
            if (g_buffer[i] == -1)                
              printf("%s", "缓冲区为空");
            else                
              printf("%2d", g_buffer[i]);
            if (i == out)                
              printf("\t<--consume");
            printf("\n");
        }

        consume_id = g_buffer[out];

        printf("%2d 开始消费产品 %2d\n", num, consume_id);
        g_buffer[out] = -1;
        out = (out + 1) % BUFFSIZE;
        printf("%2d 停止消费产品 %2d\n", num, consume_id);
        //解锁
        pthread_mutex_unlock(&g_mutex);
        //发布信号量，表示资源使用完毕，可以归还资源了。将信号量值加1。
        sem_post(&g_sem_full);
        sleep(1);
    }
    return NULL;
}

//生产者函数
void *produce(void *arg)
{
    int i;
    int num = *(int *)arg;
    free(arg);

    while (1)
    {
        printf("%2d 等待缓冲区不为满\n", num);
        //g_sem_full信号量值 -1
        sem_wait(&g_sem_full);
        //加锁
        pthread_mutex_lock(&g_mutex);

        for (i = 0; i < BUFFSIZE; i++)
        {
            printf("%2d ", i);
            if (g_buffer[i] == -1)
              printf("%s", "缓冲区为空");
            else
              printf("%2d", g_buffer[i]);
            if (i == in)
              printf("\t<--produce");
            printf("\n");
        }

        g_buffer[in] = produce_id;

        printf("%2d 开始生产产品 %2d\n", num, produce_id);
        in = (in + 1) % BUFFSIZE;
        printf("%2d 停止生产产品 %2d\n", num, produce_id++);
        //解锁
        pthread_mutex_unlock(&g_mutex);
        //信号量值 +1
        sem_post(&g_sem_empty);
        sleep(2);
    }
    return NULL;
}


int main()
{
    int i;
    for (i = 0; i < BUFFSIZE; i++)
    {
        g_buffer[i] = -1;
    }

    sem_init(&g_sem_full, 0, BUFFSIZE);
    sem_init(&g_sem_empty, 0, 0);
    pthread_mutex_init(&g_mutex, NULL);

    for (i = 0; i < CONSUMERS_COUNT; i++)
    {
        int *p = (int *)malloc(sizeof(int));
        *p = i;
        pthread_create(&g_thread[i], NULL, consume, (void *)p);
    }

    for (i = 0; i < PRODUCERS_COUNT; i++)
    {
        int *p = (int *)malloc(sizeof(int));
        *p = i;
        pthread_create(&g_thread[CONSUMERS_COUNT + i], NULL, produce, (void *)p);
    }

    for (i = 0; i < CONSUMERS_COUNT + PRODUCERS_COUNT; i++)
    {
        pthread_join(g_thread[i], NULL);
    }

    sem_destroy(&g_sem_full);
    sem_destroy(&g_sem_empty);
    pthread_mutex_destroy(&g_mutex);

    return 0;
}
