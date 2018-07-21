
//带头结点的带环双链表
#include<stdio.h>
#include<stdlib.h>

#define DataType char
#define TESTHEAD printf("\n=======%s=======\n", __FUNCTION__);

typedef struct dblinklist
{
    DataType data; 
    struct dblinklist* next;
    struct dblinklist* prev;
}dblinklist;

//创建结点
dblinklist* CreatNode();

//链表初始化
void DbLinkListInit(dblinklist** head);

//销毁结点
void DestoryNode(dblinklist* Node);

//尾插元素
void DbLinkListPushBack(dblinklist* head, DataType data);

//尾删元素
void DbLinkListPopBack(dblinklist* head);

//头插元素
void DbLinkListPushFront(dblinklist* head, DataType data);

//任意位置后插入
void DbLnkListPushAfterAnyPos(dblinklist* head, dblinklist* pos, DataType data);

//任意位置前插入
void DbLnkListPushBeforeAnyPos(dblinklist* head, dblinklist* pos, DataType data);

//寻找元素的位置
dblinklist* DbLinkListFind(dblinklist* head, DataType to_find);

//删除指定位置的元素
void DLinkListRemoveAnyPos(dblinklist* head, dblinklist* pos);

//删除与指定元素相同的所有结点
void DLinkListRemoveAll(dblinklist* head, DataType data);

//求环的大小
size_t DLinkListSize(dblinklist* head);

//清空,销毁链表
int DLinkListEmpty(dblinklist** head);

//打印链表
void DbLinkListPrint(dblinklist* head, char* msg); 
