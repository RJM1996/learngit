
#include "linklist.h"

//创建结点
Plinklist CreatNode()
{
	Plinklist Node = (Plinklist)malloc(sizeof(LinkList));
	return Node;
}
//销毁结点
void DestoryNode(Plinklist Node)
{
	free(Node);
}

//链表初始化
void LinkListInit(Plinklist* Plinkhead)
{
	TEST_HEAD;
	*Plinkhead = CreatNode();//给头结点申请空间
	(*Plinkhead)->next = NULL;//令头结点的指针域为空
	printf("初始化完成\n");//即创建了一个只有头结点的单链表
}

//获取链表长度
int LinkListLength(Plinklist* Plinkhead)
{
	TEST_HEAD;
	int len = 0;
	Plinklist p;
	p = (*Plinkhead)->next;//令p指向第一个结点
	while(p !=NULL)
	{
		len++;
		p = p->next;//p后移
	}
	printf("len = %d\n", len);
	return len;
}
//头插建立链表
void LinkListPushFront(Plinklist* Plinkhead, ElemType data)
{
	TEST_HEAD;
	if(Plinkhead == NULL)
	{
		printf("非法输入\n");
		return;
	}
	Plinklist Node;
	Plinklist temp;
	if((*Plinkhead)->next == NULL)
	{

		Node = CreatNode();
		Node->data = data;
		(*Plinkhead)->next = Node;
		Node->next = NULL;
	}
	else 
	{
		temp = *Plinkhead;
		Plinklist after_temp;
		Node = CreatNode();
		Node->data = data;
		after_temp = temp->next;
		temp->next = Node;
		Node->next = after_temp;
		printf("头插成功\n");
	}
	LinkListPrint(Plinkhead);
}
//头删
void LinkListPopFront(Plinklist* Plinkhead)
{
	TEST_HEAD;
	if((*Plinkhead)->next == NULL)
	{
		printf("链表已经为空\n");
		return ;
	}
	else
	{
		Plinklist temp = *Plinkhead;
		Plinklist del = temp->next;
		temp->next = temp->next->next;
		DestoryNode(del);
		del = NULL;
		printf("头删成功\n");
	}
	LinkListPrint(Plinkhead);
}

//尾插建立链表
void LinkListPushBack(Plinklist* Plinkhead, ElemType data)//Plinkhead头结点 Node要插入的节点
{
	TEST_HEAD;
	Plinklist Node;
	Plinklist temp;
	if((*Plinkhead)->next == NULL)
	{
		Node = CreatNode();
		Node->data = data;
		(*Plinkhead)->next = Node;
		Node->next = NULL;
	}
	else if((*Plinkhead)->next != NULL)
	{
		temp = *Plinkhead;
		while(temp->next)
		{
			temp = temp->next;
		}
		Node = CreatNode();
		Node->data = data;
		temp->next = Node;
		Node->next = NULL;
		temp = Node;
	}
	printf("尾插成功\n");
	LinkListPrint(Plinkhead);
}

//void Destory()

//尾删一个元素
void LinkListPopBack(Plinklist* Plinkhead)
{
	TEST_HEAD;
	Plinklist before_temp = NULL;
	if((*Plinkhead)->next == NULL)
	{
		printf("链表已经为空\n");
		return ;
	}
	else
	{
		Plinklist temp = *Plinkhead;
		while(temp->next)
		{
			before_temp = temp;
			temp = temp->next;
		}
		DestoryNode(temp);
		temp = NULL;
		before_temp->next = NULL;
		printf("尾删成功\n");
	}
	LinkListPrint(Plinkhead);
}
//查找元素在链表中的位置
Plinklist LinkListFindPos(Plinklist* Plinkhead, ElemType data)
{
	TEST_HEAD;
	if((*Plinkhead)->next == NULL)
	{
		printf("链表为空\n");
		return NULL;
	}
	else
	{
		Plinklist temp = *Plinkhead;
		while(temp->next != NULL)
		{
			//printf("进入循环\n");
			if(temp->next->data == data)
			{
				printf("%d的位置: ", temp->next->data);
				printf("[%p]->[%d]\n", temp->next, temp->next->data);
				return temp->next;
			}
			temp = temp->next;
		}
		printf("链表中没有此元素\n");
	}
	printf("\n");
}
//在位置pos之前插入元素
void LinkListInsertBeforePos(Plinklist* Plinkhead, int pos, ElemType data)
{
	TEST_HEAD;
	if((*Plinkhead)->next == NULL)
	{
		printf("链表为空，直接尾插\n");
		LinkListPushBack(Plinkhead, data);
		return ;
	}
	else
	{
		Plinklist temp = *Plinkhead;
		Plinklist Node; 
		Node = CreatNode();
		Node->data = data;
		Plinklist after_temp;
		int ret = pos-1;
		while(ret--)
		{
			//printf("进入循环\n");
			temp = temp->next;
		}

		after_temp = temp->next;
		temp->next = Node;
		Node->next = after_temp;
		printf("在第%d个元素之前插入[%d]成功\n", pos, data);
	}
	LinkListPrint(Plinkhead);
}
//在位置pos之后插入元素
void LinkListInsertAfterPos(Plinklist* Plinkhead, int pos, ElemType data)
{
	TEST_HEAD;
	if((*Plinkhead)->next == NULL)
	{
		printf("链表为空，直接尾插\n");
		LinkListPushBack(Plinkhead, data);
		return ;
	}
	else
	{
		Plinklist temp = *Plinkhead;
		Plinklist Node; 
		Node = CreatNode();
		Node->data = data;
		Plinklist after_temp;
		int ret = pos;
		while(ret--)
		{
			//printf("进入循环\n");
			temp = temp->next;
		}

		after_temp = temp->next;
		temp->next = Node;
		Node->next = after_temp;
		printf("在第%d个元素之后插入[%d]成功\n", pos, data);
	}
	LinkListPrint(Plinkhead);
}
//删除指定位置的元素
void LinkListErase(Plinklist* Plinkhead, int pos)
{
	TEST_HEAD;
	if((*Plinkhead)->next == NULL)
	{
		printf("链表已经为空\n");
		return ;
	}
	Plinklist temp = *Plinkhead;
	Plinklist before_pos;
	Plinklist pos_Node;
	int ret = pos-1;
	while(ret--)
	{
		//printf("进入循环\n");
		temp = temp->next;
	}
	before_pos = temp;
	pos_Node = before_pos->next;
	before_pos->next = pos_Node->next;
	int del_data = pos_Node->data;
	DestoryNode(pos_Node);
	pos_Node = NULL;
	printf("成功删除第%d个元素[%d]\n", pos, del_data);
	LinkListPrint(Plinkhead);
}
//查找指定值的位置
int LinkListFindData(Plinklist* Plinkhead, ElemType data)
{
	if(NULL == (*Plinkhead)->next)
	{
		printf("链表为空\n");
		return -1;
	}
	Plinklist temp = *Plinkhead;
	int pos = 0;
	while(temp)
	{
		if(temp->data == data)
		{
			return pos;
		}
		pos++;
		temp = temp->next;
	}
	return -1;
}
//删除指定值的元素
void LinkListRemove(Plinklist* Plinkhead, ElemType data)
{
	int pos = LinkListFindData(Plinkhead, data);
	LinkListErase(Plinkhead, pos);
}
//打印单链表
void LinkListPrint(Plinklist* Plinkhead)
{
	//TEST_HEAD;
	Plinklist temp;
	temp = (*Plinkhead)->next;
	printf("=====顺序输出链表=====\n");
	if(temp == NULL)
	{
		printf("链表为空\n");
		return;
	}
	while(temp)
	{
		printf("[%d|%p]\n", temp->data, temp->next);
		temp = temp->next;
	}
	printf("\n");
}


//指定值的所有元素都删掉 
void LinkListRemoveAll(Plinklist* Plinkhead, ElemType data)
{
	//TODO
	if((*Plinkhead)->next == NULL)
	{
		printf("链表已经为空\n");
		return;
	}
	Plinklist temp = *Plinkhead;
	while(temp)
	{
		if(temp->data == data)
		{

		}
	}
}

//判定链表为空 链表为空, 返回1, 否则返回0 
int LinkListEmpty(Plinklist* Plinkhead)
{
	TEST_HEAD;
	if((*Plinkhead)->next == NULL)
	  return 1;
	else
	  return 0;
}

//求链表的元素个数 
size_t LinkListSize(Plinklist* Plinkhead)
{
	TEST_HEAD;
	if(LinkListEmpty(Plinkhead) == 1)
	{
		printf("链表为空\n");
		return 0;
	}
	size_t count = 0;
	Plinklist temp = *Plinkhead;
	while(temp->next)
	{
		count++;
		temp = temp->next;
	}
	return count;
}

//逆序打印单链表. 
void LinkListReversePrint(Plinklist* Plinkhead)
{
	Plinklist temp = *Plinkhead;
	if(temp == NULL)
	{
		//printf("链表为空\n");
		return ;
	}
	//int len = LinkListLength(Plinkhead);
	//printf("len = %d\n", len);
	if(temp)
	{
		LinkListReversePrint(&(temp->next));
	}
	printf("[%d|%p]\n", temp->data, temp->next);
}

//不允许遍历链表, 在 pos 之前插入 
void LinkListInsertBefore(Plinklist* Plinkhead, Plinklist pos, ElemType data)
{
	TEST_HEAD;
	if(Plinkhead == NULL || pos == NULL)
	{
		printf("非法输入\n");
		return;
	}
	if((*Plinkhead) == NULL)
	{
		Plinklist Node = CreatNode();
		Node->data = data;
		(*Plinkhead)->next = Node;
		Node->next = NULL;
	}
	//先把Node插入pos之后
	Plinklist Node = CreatNode();
	Node->data = data;
	Node->next = pos->next;
	pos->next = Node;
	//交换pos和Node的值
	ElemType tmp = pos->data;
	pos->data = Node->data;
	Node->data = tmp;
	LinkListPrint(Plinkhead);
}
//约瑟夫环问题
LinkNode* JosephCycle(Plinklist* Plinkhead, size_t food)
{
    if(Plinkhead == NULL)
    {
        printf("非法输入\n");
        return ;
    }
    if(*Plinkhead = NULL)
    {
        printf("空链表\n");
        return ;
    }
    if((*Plinkhead)->next == NULL)
    {
        printf("只有一个元素\n");
        return ;
    }


}
