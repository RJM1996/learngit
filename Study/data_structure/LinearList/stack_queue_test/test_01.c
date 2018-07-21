
//实现一个栈，要求实现Push、Pop、Min(返回最小值)的时间复杂度为O(1)
//方法一: 每次入栈之前和当前栈顶元素比较
//        如果入栈的元素小,就直接入栈两个此元素
//        如果栈顶元素小,就先入栈当前元素,再将栈顶元素入栈
//        这样每次入栈时都是入栈两个元素,并且保证栈顶元素永远是最小的
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
    //将入栈元素和栈顶元素比较
    if(data <= stack->data[stack->size-1] || stack->size == 0)
    {
        //入栈元素小于等于栈顶元素,就直接入栈两个此元素
        stack->data[stack->size] = data;
        ++stack->size;
        stack->data[stack->size] = data;
        ++stack->size;
    }
    else
    {
        //如果大于栈顶元素,就先入栈此元素,再入栈栈顶元素
        DataType min = stack->data[stack->size - 1];
        stack->data[stack->size] = data;
        ++stack->size;
        stack->data[stack->size] = min;
        ++stack->size;
    }
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
    //出栈也要每次都出两个元素,才能保证当前栈顶永远是最小值
    //free(&stack->data[stack->size-1]);
    --stack->size;
    //free(&stack->data[stack->size-1]);
    --stack->size;
}

//返回最小值 Min
DataType* seqStackMin(seqStack* stack)
{
    if(stack == NULL)
    {
        return NULL;
    }
    if(stack->size == 0)
    {
        return NULL;
    }
    //返回最小值就是获取栈顶元素就可以了
    return &(stack->data[stack->size - 1]);
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
    for(int i=stack->size - 1; i>=0; i--)
    {
        printf("[%c]\n", stack->data[i]);
    }
    printf("\n");
}

int main()
{
    seqStack stack;
    seqStackInit(&stack);
    seqStackPush(&stack, 'a');
    seqStackPush(&stack, 'b');
    seqStackPush(&stack, 'c');
    seqStackPush(&stack, 'd');
    seqStackPrint(&stack, "入栈4次");

    DataType* min;
    min = seqStackMin(&stack);
    printf("min expect a, actual %c\n", *min);

    seqStackPop(&stack);
    seqStackPop(&stack);
    seqStackPrint(&stack, "出栈2次");

    min = seqStackMin(&stack);
    printf("min expect a, actual %c\n", *min);

    seqStackPop(&stack);
    seqStackPop(&stack);
    seqStackPrint(&stack, "再出栈2次");

    seqStackPop(&stack);
    seqStackPrint(&stack, "尝试对空栈出栈");

    printf("\n\n\n");
    printf("\n\n\n");
    printf("\n\n\n");
    printf("\n\n\n");
    return 0;
}
