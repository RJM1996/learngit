
//两个栈实现一个队列
//定义两个栈 一个stack栈 一个output栈
//人队列从stack入, 出队列先把stack栈的元素入栈到output栈, 再从output栈出
#include <stdio.h>
#include <stdlib.h>

#define DEFAULT_SZ 4

typedef char DataType;

typedef struct seqStack
{
    DataType* data;
    int size;//当前栈内元素的数量
    int capacity;//栈的容量
}seqStack;

//初始化栈
void seqStackInit(seqStack* stack)
{
    stack->data = (DataType*)malloc(sizeof(DataType) * DEFAULT_SZ);
    stack->size = 0;
    stack->capacity = DEFAULT_SZ;
}

//入栈 Push
void seqStackPush(seqStack* stack, DataType data)
{
    if(stack == NULL)
    {
        //非法输入
        return ;
    }
    if(stack->size == stack->capacity)
    {
        //栈满, 需要扩容
        DataType* ptr = (DataType*)realloc(stack->data, sizeof(DataType)*stack->capacity*2 + 1);
        stack->data = ptr;
    }  
    stack->data[stack->size] = data;
    ++stack->size;
}

//出栈 Pop
void seqStackPop(seqStack* stack)
{
    if(stack == NULL)
    {
        //非法输入
        return ;
    }
    if(stack->size == 0)
    {
        //空栈
        return ;
    }
    --stack->size;
}


//打印栈
void seqStackPrint(seqStack* stack, char* msg)
{
    printf("\n=====%s=====\n", msg);
    if(stack == NULL)
    {
        return ;
    }
    if(stack->size == 0)
    {
        return ;
    }
    printf("队尾 ");
    for(int i=stack->size - 1; i>=0; i--)
    {
        printf("[%c] ", stack->data[i]);
    }
    printf("队首\n");
    printf("\n");
}


//初始化"队列"
void queueInit(seqStack* input, seqStack* output)
{
    if(input == NULL || output == NULL)
      return ;
    seqStackInit(input);
    seqStackInit(output);
}
//入"队列"
void queuePush(seqStack* input, seqStack* output, DataType data)
{
    if(input == NULL || output == NULL)
      return ;
//    //先判断output栈是否为空, 若不为空需要先把output栈的元素入栈到input
//    if(output->size != 0)
//    {
//        while(output->size--)
//        {
//            DataType to_push = output->data[output->size-1];
//            seqStackPop(output);
//            seqStackPush(input, to_push);
//        }
//    }
    //往input栈里入栈
    seqStackPush(input, data);
}
//出"队列"
void queuePop(seqStack* input, seqStack* output)
{
    if(input == NULL || output == NULL)
      return ;
    if(input->size == 0)
      return ;
    else
    {
        //先把input里的元素入栈到output
        int i = input->size;
        while(i>0)
        {
            DataType to_push = input->data[i-1];
            seqStackPop(input);
            seqStackPush(output, to_push);
            i--;
        }
    }
    //再从output出栈
    seqStackPop(output);
    //出完队列以后,如果output还剩元素,应该把output里的元素放回input
    if(output->size == 0)
      return ;
    else
    {
        int j = output->size;
        while(j>0)
        {
            DataType to_back = output->data[j - 1];
            seqStackPop(output);
            seqStackPush(input, to_back);
            j--;
        }
    }
}
//打印"队列"
void queuePrint(seqStack* input, seqStack* output, char *msg)
{
    seqStackPrint(input, msg);
}

void TestQueue()
{
    //定义两个栈
    seqStack input;
    seqStack output;
    queueInit(&input, &output);
    queuePush(&input, &output, 'a');
    queuePush(&input, &output, 'b');
    queuePush(&input, &output, 'c');
    queuePush(&input, &output, 'd');
    queuePrint(&input, &output, "入队列4个元素");
    queuePop(&input, &output);
    queuePrint(&input, &output, "出队列1个元素");
    queuePop(&input, &output);
    queuePrint(&input, &output, "再出队列1个元素");
    queuePop(&input, &output);
    queuePop(&input, &output);
    queuePrint(&input, &output, "再出队列2个元素");
    queuePop(&input, &output);
    queuePrint(&input, &output, "尝试对空队列出队");
}

int main()
{
    TestQueue();

    printf("\n\n\n");
    printf("\n\n\n");
    printf("\n\n\n");
    printf("\n\n\n");
    return 0;
}
