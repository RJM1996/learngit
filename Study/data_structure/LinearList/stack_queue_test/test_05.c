
#include <stdio.h>
// 一个数组实现两个栈(共享栈)
// 从两边向中间延伸
// top1 第一个栈的栈顶 [0, top1)
// top2 第二个栈的栈顶 [top2, MAX_SIZE)

#define MAX_SIZE 10
typedef char DataType;

typedef struct shareStack
{
    DataType data[MAX_SIZE];
    int top1;
    int top2;
}shareStack;

//初始化共享栈
void shareStackInit(shareStack* stack)
{
    if(stack == NULL)
    {
        return ;
    }
    stack->top1 = -1;
    stack->top2 = MAX_SIZE;
}

//入栈
void shareStackPush(shareStack* stack, int stackNum, DataType data)
{
    if(stack == NULL)
    {
        return ;
    }
    if(stack->top1+1 ==stack->top2)
    {
        printf("\n栈已满, 无法入栈\n");
        return ;
    }
    if(stackNum == 1)
    {
        stack->data[++stack->top1] = data;
    }
    if(stackNum == 2)
    {
        stack->data[--stack->top2] = data;
    }
}

//出栈
void shareStackPop(shareStack* stack, int stackNum)
{
    if(stack == NULL)
      return ;
    if(stackNum == 1)
    {
        if(stack->top1 == -1)
        {
            //空栈
            return ;
        }
        --stack->top1;
    }
    if(stackNum == 2)
    {
        if(stack->top2 == MAX_SIZE)
        {
            //空栈
            return ;
        }
        ++stack->top2;
    }
}

//打印栈
void shareStackPrint(shareStack* stack, char* msg)
{
    printf("\n=====%s=====\n", msg);
    if(stack == NULL)
    {
        return ;
    }
    printf("\n=====top1=====\n");
    for(int i=stack->top1; i>=0; i--)
    {
        printf("[%c]\n", stack->data[i]);
    }
    printf("\n=====top2=====\n");
    for(int i=stack->top2; i<MAX_SIZE; i++)
    {
        printf("[%c]\n", stack->data[i]);
    }
}


void TestShareStack()
{
    shareStack mystack;
    shareStackInit(&mystack);
    shareStackPush(&mystack, 1, 'a');
    shareStackPush(&mystack, 1, 'b');
    shareStackPush(&mystack, 1, 'c');
    shareStackPush(&mystack, 1, 'd');
    shareStackPrint(&mystack, "往top1里入栈4个元素");
    shareStackPush(&mystack, 2, 'z');
    shareStackPush(&mystack, 2, 'x');
    shareStackPush(&mystack, 2, 'c');
    shareStackPush(&mystack, 2, 'v');
    shareStackPrint(&mystack, "往top2里入栈4个元素");
    shareStackPop(&mystack, 1);
    shareStackPrint(&mystack, "top1出栈1次");
    shareStackPop(&mystack, 1);
    shareStackPop(&mystack, 1);
    shareStackPrint(&mystack, "top1再出栈2次");
    shareStackPop(&mystack, 1);
    shareStackPrint(&mystack, "top1再出栈1次");
    shareStackPop(&mystack, 1);
    shareStackPrint(&mystack, "尝试对空 top1 出栈");
    shareStackPop(&mystack, 2);
    shareStackPrint(&mystack, "top2出栈1次");
    shareStackPop(&mystack, 2);
    shareStackPop(&mystack, 2);
    shareStackPrint(&mystack, "top2再出栈2次");
    shareStackPop(&mystack, 2);
    shareStackPrint(&mystack, "top2再出栈1次");
    shareStackPop(&mystack, 2);
    shareStackPrint(&mystack, "尝试对空 top2 出栈");
}

int main()
{
    TestShareStack();
    printf("\n\n\n");
    printf("\n\n\n");
    printf("\n\n\n");
    printf("\n\n\n");
    return 0;
}
