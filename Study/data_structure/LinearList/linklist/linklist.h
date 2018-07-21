
#include<stdio.h>
#include<stdlib.h>

#define TEST_HEAD printf("=====%s=====\n", __FUNCTION__);

typedef int ElemType; 

typedef struct LinkList
{
	ElemType data;//数据域
	struct LinkList* next;//指针域
}LinkList, *Plinklist;

void LinkListInit(Plinklist* Plinkhead);//链表初始化
int LinkListLength(Plinklist* Plinkhead);//获取链表长度
void LinkListPushFront(Plinklist* Plinkhead, ElemType data);//头插
void LinkListPopFront(Plinklist* Plinkhead);//头删
void LinkListPushBack(Plinklist* Plinkhead, ElemType data);//尾插
void LinkListPopBack(Plinklist* Plinkhead);//尾删
Plinklist LinkListFindPos(Plinklist* Plinkhead, ElemType data);//查找pos位置的元素
void LinkListInsertBeforePos(Plinklist* Plinkhead, int pos, ElemType data);//在pos之前插入元素
void LinkListInsertAfterPos(Plinklist* Plinkhead, int pos, ElemType data);//在pos之后插入元素
void LinkListInsertBefore(Plinklist* Plinkhead, Plinklist pos, ElemType data);//不允许遍历链表, 在 pos 之前插入
void LinkListErase(Plinklist* Plinkhead, int pos);//删除指定位置元素
void LinkListRemove(Plinklist* Plinkhead, ElemType data);//删除指定值的元素
int LinkListFindData(Plinklist* Plinkhead, ElemType data);//查找指定值的位置
void LinkListPrint(Plinklist* Plinkhead);//打印链表
int LinkListEmpty(Plinklist* Plinkhead);//判断链表是否为空
size_t LinkListSize(Plinklist* Plinkhead);//求元素个数
void LinkListReversePrint(Plinklist* Plinkhead);

