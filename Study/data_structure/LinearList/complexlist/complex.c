#include<stdio.h>
#include<stdlib.h>
#include<malloc.h>

#define DataType int

//��������
typedef struct ComplexNode { 
    DataType data; 
    struct ComplexNode* next; 
    struct ComplexNode* random; 
} ComplexNode; 

//��������������
ComplexNode* CreateComplexNode()
{
    ComplexNode* Node = (ComplexNode*)malloc(sizeof(ComplexNode));
    return Node;
}

//���������ʼ��
void ComplexNodeInit(ComplexNode* head)
{
    head = CreateComplexNode();
    head->data = 0;
    head->next = NULL;
    head->random = NULL;
}

//��������Ĳ���
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
        printf("������\n");
    }
    ComplexNode* cur = head;
    while(cur->next)
    {
        printf("[%d|%p|%p]", cur->data, cur->next, cur->random);
        cur = cur->next;
    }
    printf("��ӡ���\n");
}

/*
//�����������
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
    printf("β�����\n");
}
//������������ 
ComplexNode* CopyComplex(ComplexNode* head) 
{
   if(head == NULL) 
   {
       return NULL;
   }
   //��ÿ�����ĺ��涼����һ������ڵ�
   ComplexNode* cur = head->next;
   ComplexNode* after_cur = NULL;
   while(cur)
   {
       //�����½��, ������ǰһ������ֵ, ���������
       ComplexNode* Node = CreateComplexNode();
       Node->data = cur->data;
       after_cur = cur->next;
       cur->next = Node;
       Node->next = after_cur;

       //�½���randomָ��ָ��ľ�����ǰһ�����randomָ��ָ�������һ�����
       Node->random = cur->random->next;  

       cur = cur->next;
   }
   //������,���������Ϊ����
   ComplexNode* new_head = CreateComplexNode();
   ComplexNode* new_tail = CreateComplexNode();
   new_head->next = new_tail;
   new_tail->next = NULL;
   while(cur->next)
   {
       //�������ŵĽ�����,�����µ�����
       ComplexNode* to_sep = cur->next;
       new_head->next = to_sep;
       to_sep->next = new_tail;

       cur->next = cur->next->next;
   }
   return new_head;
}
*/



//���Ժ���
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
