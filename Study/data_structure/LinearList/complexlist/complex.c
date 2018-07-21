#include<stdio.h>
#include<stdlib.h>
#include<malloc.h>

#define DataType int

//复杂链表
typedef struct ComplexNode { 
    DataType data; 
    struct ComplexNode* next; 
    struct ComplexNode* random; 
} ComplexNode; 

//创建复杂链表结点
ComplexNode* CreateComplexNode()
{
    ComplexNode* Node = (ComplexNode*)malloc(sizeof(ComplexNode));
    return Node;
}

//复杂链表初始化
void ComplexNodeInit(ComplexNode* head)
{
    head = CreateComplexNode();
    head->data = 0;
    head->next = NULL;
    head->random = NULL;
}

//复杂链表的插入
void ComplexNodePushBack(ComplexNode* head, DataType data)
{
    if(head->next == NULL)
    {
        ComplexNode* Node = CreateComplexNode();
        Node->data = data;
        head->next = Node;
        Node->next = NULL;
    }
    ComplexNode* cur = head;
    while(cur->next)
    {
        cur = cur->next;
    }
    ComplexNode* Node = CreateComplexNode();
    Node->data = data;
    cur->next = Node;
    Node->next = NULL;
}

void printComplexList(ComplexNode* head)
{
    if(head->next == NULL)
    {
        printf("空链表\n");
    }
    ComplexNode* cur = head;
    while(cur->next)
    {
        printf("[%d|%p|%p]", cur->data, cur->next, cur->random);
        cur = cur->next;
    }
    printf("打印完成\n");
}

/*
//复杂链表插入
void ComplexNodePush(ComplexNode** head, DataType data)
{
    if(head == NULL)
    {
        return ;
    }
    if((*head)->next == NULL)
    {
        ComplexNode* Node = CreateComplexNode();
        Node->data = data;
        (*head)->next = Node;
        Node->next = NULL;
    }
    else
    {
        ComplexNode* cur = *head;
        while(cur->next)
        {
            cur = cur->next;
        }
        ComplexNode* Node = CreateComplexNode();
        Node->data = data;
        cur->next = Node;
        Node->next = NULL;
    }
    printf("尾插完成\n");
}
//拷贝复杂链表 
ComplexNode* CopyComplex(ComplexNode* head) 
{
   if(head == NULL) 
   {
       return NULL;
   }
   //把每个结点的后面都插入一个自身节点
   ComplexNode* cur = head->next;
   ComplexNode* after_cur = NULL;
   while(cur)
   {
       //创建新结点, 拷贝它前一个结点的值, 并插入其后
       ComplexNode* Node = CreateComplexNode();
       Node->data = cur->data;
       after_cur = cur->next;
       cur->next = Node;
       Node->next = after_cur;

       //新结点的random指针指向的就是它前一个结点random指针指向结点的下一个结点
       Node->random = cur->random->next;  

       cur = cur->next;
   }
   //接下来,将链表分离为两份
   ComplexNode* new_head = CreateComplexNode();
   ComplexNode* new_tail = CreateComplexNode();
   new_head->next = new_tail;
   new_tail->next = NULL;
   while(cur->next)
   {
       //将拷贝号的结点分离,插入新的链表
       ComplexNode* to_sep = cur->next;
       new_head->next = to_sep;
       to_sep->next = new_tail;

       cur->next = cur->next->next;
   }
   return new_head;
}
*/



//测试函数
void TestCopyComplexlist()
{
    ComplexNode* list;
    ComplexNodeInit(list);
    ComplexNodePushBack(list, 1);
    ComplexNodePushBack(list, 3);
    ComplexNodePushBack(list, 5);
    ComplexNodePushBack(list, 7);
    printComplexList(list);
    printf("\n");

   // ComplexNode* p1 = list->next;
   // p1->random = p1->next->next;
   // list->next->next->random = list->next->next;

   // ComplexNode* copylist = CopyComplex(list);
   // printComplexList(copylist);
   // printf("\n");
}

int main()
{
    TestCopyComplexlist();
    return 0;
}
