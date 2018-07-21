
//单链表实现栈
#include <stdio.h>
#include <stdlib.h>

typedef char DataType;

typedef struct linkStack
{
    DataType data;
    struct linkStack* next;
}linkStack;

//初始化
void linkStackInit(linkStack** head)
{
    *head = NULL;
}

//创建新结点
linkStack* CreatNode(DataType data)
{
    linkStack* new_node = (linkStack*)malloc(sizeof(DataType));
    new_node->data = data;
    return new_node;
}

//入栈(头插, 要改变头指针的指向)
void linkStackPush(linkStack** head, DataType data)
{
    if(head == NULL)
    {
        return ;
    }

    linkStack* new_node = CreatNode(data);
    if(*head == NULL)
    {
        //空链表
        *head = new_node;
        new_node->next = NULL;
        return ;
    }
    linkStack* temp = *head;
    new_node->next = temp;
    *head = new_node;
}

//出栈(头删, 也要修改头指针的指向)
void linkStackPop(linkStack** head)
{
    if(head == NULL)
    {
        //非法输入
        return ;
    }
    if(*head == NULL)
    {
        //空链表
        return ;
    }
    linkStack* temp = *head;
    *head = temp->next;
    free(temp);
}

//取栈顶元素
DataType linkStackGetTop(linkStack* head)
{
    if(head == NULL)
      return 0;
    linkStack* temp = head;
    return temp->data;
}

//打印栈
void linkStackPrint(linkStack* head, char* msg)
{
    printf("\n[%s]\n", msg);
    if(head == NULL)
    {
        return ;
    }

    linkStack* temp = head;
    while(temp != NULL)
    {
        printf("[%c|%9p]\n", temp->data, temp->next);
        temp = temp->next;
    }
}

//销毁栈
void linkStackDestory(linkStack** head)
{
    if(head == NULL)
    {
        //栈已经不存在了
        return ;
    }
    if(*head == NULL)
    {
        //空栈
        head = NULL;
        return ;
    }
    linkStack* temp = *head;
    linkStack* cur = NULL;
    while(temp != NULL)
    {
        cur = temp->next;
        free(temp);
        temp = cur;
    }
    *head = NULL;
    head = NULL;
}


////////////////////////////
//测试函数
////////////////////////////

void TestLinkStack()
{
    linkStack* myStack;
    linkStackInit(&myStack);
    linkStackPush(&myStack, 'a');
    linkStackPush(&myStack, 'b');
    linkStackPush(&myStack, 'c');
    linkStackPush(&myStack, 'd');
    linkStackPrint(myStack, "入栈4个元素");
    DataType ret = linkStackGetTop(myStack);
    linkStackPrint(myStack, "取栈顶元素");
    printf("ret expect [d], actual [%c]\n", ret);
    linkStackPop(&myStack);
    linkStackPrint(myStack, "出栈一次");
    linkStackPop(&myStack);
    linkStackPop(&myStack);
    linkStackPop(&myStack);
    linkStackPrint(myStack, "再出栈三次");
    linkStackPop(&myStack);
    linkStackPrint(myStack, "尝试对空栈出栈");
    linkStackPush(&myStack, 'a');
    linkStackPush(&myStack, 'b');
    linkStackPush(&myStack, 'c');
    linkStackPush(&myStack, 'd');
    linkStackPrint(myStack, "入栈4个元素");
    linkStackDestory(&myStack);
    linkStackPrint(myStack, "销毁栈");
}



int main()
{
    TestLinkStack();
    printf("\n\n\n");
    printf("\n\n\n");
    printf("\n\n\n");
    printf("\n\n\n");
    return 0;
}

