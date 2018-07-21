
//两个队列实现一个栈
#include <stdio.h>
#include <stdlib.h>

#define DEFAULT_SZ 4

typedef char DataType;

typedef struct seqQueue
{
    DataType* data;
    int size;
    int capacity;
}seqQueue;


//初始化
void queueInit(seqQueue* queue)
{
    if(queue == NULL)
      return ;
    queue->data = (DataType*)malloc(sizeof(DataType) * DEFAULT_SZ);
    queue->size = 0;
    queue->capacity = DEFAULT_SZ;
}

//入队列
void queuePush(seqQueue* queue, DataType data)
{
    if(queue == NULL)
      return ;
    if(queue->size == queue->capacity)
    {
        //需要扩容
        DataType* ptr = (DataType*)realloc(queue->data, sizeof(DataType) * queue->capacity * 2 + 1);
        queue->data = ptr;
    }
    queue->data[queue->size] = data;
    queue->size++;
}

//出队列
void queuePop(seqQueue* queue)
{
    if(queue == NULL)
      return ;
    if(queue->size == 0)
    {
        //空队列
        return ;
    }
    int i = 0;
    for(; i<=queue->size-1; i++)
    {
        queue->data[i] = queue->data[i+1];
    }
    queue->size--;
}

//打印队列
void queuePrint(seqQueue* queue, char* msg)
{
    printf("=====%s=====\n", msg);
    if(queue == NULL)
      return ;
    for(int i=queue->size-1; i>=0; i--)
    {
        printf("[%c] \n", queue->data[i]);
    }
    printf("\n");
}

void TestQueue()
{
    seqQueue queue;
    queueInit(&queue);
    queuePush(&queue, 'a');
    queuePush(&queue, 'b');
    queuePush(&queue, 'c');
    queuePush(&queue, 'd');
    queuePrint(&queue, "入队列4个元素");
    queuePop(&queue);
    queuePrint(&queue, "出队列1个元素");
    queuePop(&queue);
    queuePrint(&queue, "再出队列1个元素");
    queuePop(&queue);
    queuePop(&queue);
    queuePrint(&queue, "再出队列2个元素");
    queuePop(&queue);
    queuePrint(&queue, "尝试对空队列出队");
}

/////////////////////////////////////////////
//两个队列实现一个栈
/////////////////////////////////////////////

//初始化
void stackInit(seqQueue* queue1, seqQueue* queue2)
{
    if(queue1 == NULL || queue2 == NULL)
      return ;
    queueInit(queue1);
    queueInit(queue2);
}
//入栈
void stackPush(seqQueue* queue1, seqQueue* queue2, DataType data)
{
    if(queue1 == NULL || queue2 == NULL)
      return ;

    //先判断哪个队列不为空,就往哪个队列入
    if(queue2->size != 0)
    {
        //证明queue2是非空的,就往其中加入元素
        queuePush(queue2, data);
    }
    else
    {
        //否则证明queue1是非空的,往其中加入元素
        queuePush(queue1, data);
    }
}

//出栈
void stackPop(seqQueue* queue1, seqQueue* queue2)
{
    if(queue1 == NULL || queue2 == NULL)
      return ;
    //先将非空队列出队列到另一个队列,直到只剩一个元素
    if(queue1->size != 0)
    {
        int i = 0;
        int size = queue1->size;
        while(i<size-1)
        {
            DataType to_push = queue1->data[0];
            queuePop(queue1);
            queuePush(queue2, to_push);
            i++;
        }
        //再将剩余的一个元素出队列
        queuePop(queue1);
    }
    else
    {
        int i = 0;
        int size = queue2->size;
        while(i<size-1)
        {
            DataType to_push = queue2->data[0];
            queuePop(queue2);
            queuePush(queue1, to_push);
            i++;
        }
        //再将剩余的一个元素出队列
        queuePop(queue2);
    }
}

void stackPrint(seqQueue* queue1, seqQueue* queue2, char* msg)
{
    if(queue1 == NULL || queue2 == NULL)
      return ;
    if(queue1->size != 0)
    {
        queuePrint(queue1, msg);
    }
    else
    {
        queuePrint(queue2, msg);
    }
}

void Test_TwoQueue_to_Stack()
{
    seqQueue queue1, queue2;
    stackInit(&queue1, &queue2);
    stackPush(&queue1, &queue2, 'a');
    stackPush(&queue1, &queue2, 'b');
    stackPush(&queue1, &queue2, 'c');
    stackPush(&queue1, &queue2, 'd');
    stackPrint(&queue1, &queue2, "入栈4个元素");
    stackPop(&queue1, &queue2);
    stackPrint(&queue1, &queue2, "出栈1个元素");
    stackPop(&queue1, &queue2);
    stackPrint(&queue1, &queue2, "再出栈1个元素");
    stackPop(&queue1, &queue2);
    stackPop(&queue1, &queue2);
    stackPrint(&queue1, &queue2, "再出栈2个元素");
    stackPop(&queue1, &queue2);
    stackPrint(&queue1, &queue2, "尝试对空栈出栈");
}


int main()
{
    TestQueue();
    Test_TwoQueue_to_Stack();
    printf("\n\n\n");
    printf("\n\n\n");
    printf("\n\n\n");
    printf("\n\n\n");
    return 0;
}
