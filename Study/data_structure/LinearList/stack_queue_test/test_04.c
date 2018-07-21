
//判定字符串是否满足出栈顺序
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
    for(int i=stack->size - 1; i>=0; i--)
    {
        printf("[%c]\n", stack->data[i]);
    }
    printf("\n");
}

//取栈顶元素
DataType* seqStackTop(seqStack* stack)
{
    if(stack == NULL)
      return NULL;
    if(stack->size == 0)
    {
        return NULL;
    }
    return &stack->data[stack->size - 1];
}

//判断字符串出栈合法性
int JudgeString(seqStack* stack, char* to_push_msg, char* to_judge_msg)
{
    if(stack == NULL || to_push_msg == NULL || to_judge_msg == NULL)
      return 0;
    //定义p_push指针指向将入栈的字符串, 定义p_judge指针指向要判断的字符串
    //比较两个指针指向字符是否相等
    //如果相等,*p_push 入栈再出栈 p_push++ p_judge++
    //如果不相等,*p_push入栈, p_push++, 再比较
    char* p_push = to_push_msg;
    char* p_judge = to_judge_msg;

    while(*p_push != 0)
    {
        if(*p_push != *p_judge)
        {
            seqStackPush(stack, *p_push);
            p_push++;
        }
        else
        {
            p_push++;
            p_judge++;
        }
    }
    if(*p_judge != 0)
    {
        DataType* top = seqStackTop(stack);
        while(top != NULL && *p_judge == *top)
        {
            seqStackPop(stack);
            p_judge++;
            top = seqStackTop(stack);
        }
        if(*p_judge == 0)
        {
            //printf("p_judge走完了\n");
            return 1;
        }
        return 0;
    }
    else
    {
        return 1;
    }
}


int main()
{
    seqStack stack;
    seqStackInit(&stack);
    seqStackPush(&stack, 'a');
    seqStackPush(&stack, 'b');
    seqStackPush(&stack, 'c');
    seqStackPush(&stack, 'd');
    seqStackPrint(&stack, "入栈4个元素");
    seqStackPop(&stack);
    seqStackPrint(&stack, "出栈1个元素");
    seqStackPop(&stack);
    seqStackPop(&stack);
    seqStackPrint(&stack, "再出栈2个元素");
    seqStackPop(&stack);
    seqStackPrint(&stack, "再出栈1个元素");
    seqStackPop(&stack);
    seqStackPrint(&stack, "尝试对空栈出栈");

    //测试出栈合法性
    printf("\n===测试出栈合法性===\n");
    int ret = JudgeString(&stack, "abcde", "cdeab");
    if(ret == 1)
      printf("[ %s ] to [ %s ] 合法\n", "abcde", "cdeab");
    else
      printf("[ %s ] to [ %s ] 不合法\n", "abcde", "cdeab");
    ret = JudgeString(&stack, "abcde", "cdeba");
    if(ret == 1)
      printf("[ %s ] to [ %s ] 合法\n", "abcde", "cdeba");
    else
      printf("[ %s ] to [ %s ] 不合法\n", "abcde", "cdeba");

    printf("\n\n\n");
    printf("\n\n\n");
    printf("\n\n\n");
    printf("\n\n\n");
    return 0;
}
