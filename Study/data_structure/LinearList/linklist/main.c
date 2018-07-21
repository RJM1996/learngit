
#include "linklist.h"
	

int main()
{
	Plinklist myLinkList;//定义一个链表
	LinkListInit(&myLinkList);//初始化链表

	LinkListLength(&myLinkList);//获取链表长度
	//尾插元素
	LinkListPushBack(&myLinkList, 9);
	LinkListPushBack(&myLinkList, 5);
	LinkListPushBack(&myLinkList, 2);
	LinkListPushBack(&myLinkList, 7);
	//头插元素
	LinkListPushFront(&myLinkList, 2);
	LinkListPushFront(&myLinkList, 4);
	LinkListPushFront(&myLinkList, 6);
	LinkListPushFront(&myLinkList, 8);
	//寻找元素位置
	LinkListFindPos(&myLinkList, 7);
	LinkListFindPos(&myLinkList, 2);
	LinkListFindPos(&myLinkList, 5);
	LinkListFindPos(&myLinkList, 9);
	//指定位置之前插入
	LinkListInsertBeforePos(&myLinkList, 3, 6);
	//指定位置之后插入
	LinkListInsertAfterPos(&myLinkList, 3, 4);
	//删除指定位置元素
	LinkListErase(&myLinkList, 2);
	//删除指定元素
	LinkListRemove(&myLinkList, 7);
	//printf("size = %d\n", LinkListSize(&myLinkList));
	//判断链表是否为空 求链表元素个数
//	if(LinkListEmpty(&myLinkList) == 1)
//		printf("链表为空\n");
//	else
//		printf("size = %d\n", LinkListSize(&myLinkList));

	//顺序打印链表
	LinkListPrint(&myLinkList);
	//逆序打印链表
	printf("=====逆序输出链表=====\n");	
	LinkListReversePrint(&myLinkList);
	//头删元素
	LinkListPopFront(&myLinkList);
	LinkListPopFront(&myLinkList);
	//尾删元素
	LinkListPopBack(&myLinkList);
	LinkListPopBack(&myLinkList);
	//不允许遍历链表, 在 pos 之前插入
	Plinklist pos = myLinkList->next->next;
	LinkListInsertBefore(&myLinkList, pos, 18);
	return 0;
}
