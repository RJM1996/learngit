
//单链表实现队列
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

//入队列(尾插)
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
    while(temp->next != NULL)
    {
        temp = temp->next;
    }
    temp->next = new_node;
    new_node->next = NULL;
}

//出队列(头删, 要修改头指针的指向)
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

//取队首元素
DataType linkStackGetTop(linkStack* head)
{
    if(head == NULL)
      return 0;
    linkStack* temp = head;
    return temp->data;
}

//打印队列
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
        printf("[%c] ", temp->data);
        temp = temp->next;
    }
    printf("\n");
}

//销毁队列
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
    linkStackPrint(myStack, "入队列4个元素");
    DataType ret = linkStackGetTop(myStack);
    linkStackPrint(myStack, "取队首元素");
    printf("\nret expect [a], actual [%c]\n", ret);
    linkStackPop(&myStack);
    linkStackPrint(myStack, "出队列一次");
    linkStackPop(&myStack);
    linkStackPrint(myStack, "再出队列一次");
    linkStackPop(&myStack);
    linkStackPop(&myStack);
    linkStackPrint(myStack, "再出队列二次");
    linkStackPop(&myStack);
    linkStackPrint(myStack, "尝试对空队列出队列");
    linkStackPush(&myStack, 'a');
    linkStackPush(&myStack, 'b');
    linkStackPush(&myStack, 'c');
    linkStackPush(&myStack, 'd');
    linkStackPrint(myStack, "入队列4个元素");
    linkStackDestory(&myStack);
    linkStackPrint(myStack, "销毁队列");
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

