
#include <stdio.h>
#include <stdlib.h>

//顺序表实现队列

#define TEST_HEAD printf("\n=====%s=====\n", __FUNCTION__)
#define DEFAULT_SZ 5

typedef char DataType;

typedef struct seqQueue
{
    DataType* data;
    int size;
    int capacity;
}seqQueue;

//初始化
void seqQueueInit(seqQueue* queue)
{
    if(queue == NULL)
    {
        //非法输入
        return ;
    }
    queue->data = (DataType*)malloc(sizeof(DataType)*DEFAULT_SZ);
    queue->size = 0;
    queue->capacity = DEFAULT_SZ;
}

//入队列(在队尾插入)
void seqQueuePush(seqQueue* queue, DataType data)
{
    if(queue->size == queue->capacity)
    {
        //此时需要扩容
        DataType* ptr = NULL;
        ptr = (DataType*)realloc(queue->data, sizeof(DataType)*(queue->capacity) + 1);
        queue->data = ptr;
    }
    queue->data[queue->size++] = data;
}

//出队列(在队首删除)
void seqQueuePop(seqQueue* queue)
{
    if(queue->size == 0)
    {
        //空队列
        return ;
    }
    for(int i=0; i<queue->size-1; i++)
    {
        queue->data[i] = queue->data[i+1];
    }
    queue->size--;
}

//取队首元素
DataType seqQueueGetTop(seqQueue* queue)
{
    if(queue->size == 0)
    {
        //空队列
        return 0;
    }
    return queue->data[0];
}

//清空队列
void seqQueueEmpty(seqQueue* queue)
{
    if(queue == NULL)
    {
        return ;
    }
    queue->size = 0;
    queue->capacity = 0;
    queue->data = NULL;
}

//打印队列
void seqQueuePrint(seqQueue* queue, char* msg)
{
    printf("\n\n[%s]\n", msg);
    if(queue == NULL)
    {
        //非法输入
        return ;
    }
    if(queue->size == 0)
    {
        //空队列
        return ;
    }
    for(int i=queue->size-1; i>=0; i--)
    {
        printf("[%c] ", queue->data[i]);
    }
    return ;
}


///////////////////////////////
//测试函数
///////////////////////////////

void TestSeqQueue()
{
    TEST_HEAD;
    seqQueue myqueue;
    seqQueueInit(&myqueue);
    seqQueuePush(&myqueue, 'a');
    seqQueuePush(&myqueue, 'b');
    seqQueuePush(&myqueue, 'c');
    seqQueuePush(&myqueue, 'd');
    seqQueuePrint(&myqueue, "入队列4个元素");
    seqQueuePop(&myqueue);
    seqQueuePrint(&myqueue, "出队列1个元素");
    seqQueuePush(&myqueue, 'z');
    seqQueuePush(&myqueue, 'x');
    seqQueuePush(&myqueue, 'c');
    seqQueuePush(&myqueue, 'v');
    seqQueuePrint(&myqueue, "再入队列4个元素");
    DataType ret = seqQueueGetTop(&myqueue);
    seqQueuePrint(&myqueue, "取队首元素");
    printf("\nret expect [b], actual [%c]\n", ret);
    seqQueueEmpty(&myqueue);
    seqQueuePrint(&myqueue, "清空队列");
}

int main()
{
    TestSeqQueue();
    printf("\n\n\n");
    printf("\n\n\n");
    printf("\n\n\n");
    printf("\n\n\n");
    return 0;
}
