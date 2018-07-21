
#include <stdio.h>
#include <stdlib.h>

//顺序表实现栈

#define TEST_HEAD printf("\n======%s======\n", __FUNCTION__);
#define DEFAULT_SZ 5

typedef char DataType;

typedef struct seqStack
{
    DataType* data;
    int size;//当前栈的大小
    int capacity;//栈的总大小
}seqstack;

//栈的初始化
void StackInit(seqstack* pStack)
{
    if(pStack == NULL)
    {
        //非法输入
        return ;
    }
    //开辟空间
    (pStack)->data = (DataType*)malloc(DEFAULT_SZ*sizeof(DataType));
    if((pStack)->data == NULL)
    {
        perror("malloc error");
        exit(EXIT_FAILURE);
    }
    (pStack)->size = 0;
    (pStack)->capacity = DEFAULT_SZ;
}

//入栈--即在顺序表尾部插入元素
void StackPush(seqstack* pStack, DataType data)
{
    if(pStack == NULL)
    {
        //非法输入
        return ;
    }
    if(pStack->capacity == pStack->size)
    {
        //顺序表已满,需要扩容
        DataType* ptr = NULL;
        ptr = (DataType*)realloc(pStack->data, sizeof(DataType)*(pStack->capacity)*2 + 1);
        if(ptr == NULL)
        {
            perror("malloc error");
            exit(EXIT_FAILURE);
        }
        pStack->data = ptr;
        pStack->capacity = (pStack->capacity)*2 + 1;
    }
    pStack->data[pStack->size] = data;
    ++pStack->size;
}

//出栈
void StackPop(seqstack* pStack)
{
    if(pStack == NULL)
    {
        //非法输入
        return ;
    }
    if(pStack->size == 0)
    {
        printf("栈已经为空\n");
        return ;
    }
    --pStack->size;
}

//取栈顶元素
DataType StackGetTop(seqstack* pStack)
{
    if(pStack == NULL)
    {
        //非法输入
        return -1;
    }
    return pStack->data[(pStack->size)-1];
}

//打印栈
void StackPrint(seqstack* pStack, char* msg)
{
    printf("[%s]\n", msg);
    if(pStack == NULL)
    {
        printf("栈不存在\n");
        return ;
    }
    if(pStack->size == 0)
    {
        printf("空栈\n");
        return ;
    }
    int i = 0;
    for(i = (pStack->size)-1; i>=0; --i)
    {
        printf("[%c]\n", pStack->data[i]);
    }
}

void insert(seqstack* pStack, DataType data)
{
    if(pStack->size == 0)
    {
        StackPush(pStack, data);
        return ;
    }
    DataType temp = StackGetTop(pStack);
    StackPop(pStack);
    insert(pStack, data);
    StackPush(pStack, temp);
}
// 栈的逆置
seqstack* ReverseStack(seqstack* pStack, int size)
{
    if(pStack == NULL)
      return pStack ;
    if(size <= 1)
      return pStack;
    DataType temp = StackGetTop(pStack);
    StackPop(pStack);
    ReverseStack(pStack, size-1);
    insert(pStack, temp);
    return pStack;
}


//清空栈
void StackEmpty(seqstack* pStack)
{
    if(pStack == NULL)
      return ;
    (pStack)->size = 0;
    (pStack)->capacity = 0;
    free((pStack)->data);
    (pStack)->data = NULL;
}

//销毁栈
void StackDestory(seqstack* pStack)
{
    StackEmpty(pStack);
    pStack = NULL;
}

////////////////////////////
//测试函数
////////////////////////////

void TestStack()
{
    TEST_HEAD;
    seqstack myStack;
    StackInit(&myStack);
    StackPush(&myStack, 'a');
    StackPush(&myStack, 'b');
    StackPush(&myStack, 'c');
    StackPush(&myStack, 'd');
    StackPush(&myStack, 'e');
    StackPrint(&myStack, "入栈5个元素");
    DataType ret = StackGetTop(&myStack);
    StackPrint(&myStack, "取栈顶元素");
    printf("expect [e], actual [%c]\n", ret);
    StackPop(&myStack);
    StackPop(&myStack);
    StackPrint(&myStack, "出栈两次");
    StackPop(&myStack);
    StackPop(&myStack);
    StackPop(&myStack);
    StackPrint(&myStack, "再出栈三次");
    StackPop(&myStack);
    StackPrint(&myStack, "尝试对空栈出栈");
    StackPush(&myStack, 'a');
    StackPush(&myStack, 'b');
    StackPush(&myStack, 'c');
    StackPush(&myStack, 'd');
    StackPush(&myStack, 'e');
    StackPrint(&myStack, "入栈5个元素");
    StackPush(&myStack, 'z');
    StackPush(&myStack, 'x');
    StackPush(&myStack, 'y');
    StackPrint(&myStack, "再入栈3个元素");
    StackEmpty(&myStack);
    StackPrint(&myStack, "清空栈");
    StackPush(&myStack, 'z');
    StackPush(&myStack, 'x');
    StackPush(&myStack, 'y');
    StackPrint(&myStack, "再入栈3个元素");
    StackDestory(&myStack);
    StackPrint(&myStack, "销毁栈");
}

void TestReverse()
{
    TEST_HEAD;
    seqstack myStack;
    StackInit(&myStack);
    StackPush(&myStack, 'a');
    StackPush(&myStack, 'b');
    StackPush(&myStack, 'c');
    StackPush(&myStack, 'd');
    StackPush(&myStack, 'e');
    StackPrint(&myStack, "入栈5个元素");
    seqstack* s = ReverseStack(&myStack, 5);
    StackPrint(s, "逆置之后");
}

int main()
{
    TestStack();
    TestReverse();
    printf("\n\n\n");
    printf("\n\n\n");
    printf("\n\n\n");
    printf("\n\n\n");
    return 0;
}
