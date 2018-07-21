
//带头结点的带环双链表
#include"dblinklist.h"

//创建结点
dblinklist* CreatNode()
{
    dblinklist* Node = (dblinklist*)malloc(sizeof(dblinklist));
    Node->next = NULL;
    Node->prev = NULL;
}

//链表初始化
void DbLinkListInit(dblinklist** head)
{
    //创建一个空的头结点
    *head = CreatNode();
    (*head)->next = *head;
    (*head)->prev = *head;
    printf("初始化完成\n");
}

//销毁结点
void DestoryNode(dblinklist* Node)
{
    free(Node);
    Node = NULL;
}

//尾插元素
void DbLinkListPushBack(dblinklist* head, DataType data)
{
    if(head == NULL)
    {
        //非法输入
        return ;
    }
    dblinklist* new_node = CreatNode();
    new_node->data = data;

    dblinklist* temp = head;

    dblinklist* last = head->prev;

    last->next = new_node;
    new_node->prev = last;

    new_node->next = temp;
    temp->prev = new_node;
}

//尾删
void DbLinkListPopBack(dblinklist* head)
{
    if(head == NULL)
    {
        //非法输入
        return ;
    }
    if(head->next == head)
    {
        printf("链表已经为空\n");
        return ;
    }
    dblinklist* to_delete = head->prev;

    to_delete->prev->next = head;
    head->prev = to_delete->prev;

    DestoryNode(to_delete);
}

//头插
void DbLinkListPushFront(dblinklist* head, DataType data)
{
    if(head == NULL)
    {
        //非法输入
        return ;
    }
    dblinklist* Node = CreatNode();
    Node->data = data;
    dblinklist* temp = head->next;
    temp->prev = Node;
    Node->next = temp;
    head->next = Node;
    Node->prev = head;
}

//从任意位置后插入
void DbLinkListPushAfterAnyPos(dblinklist* head, dblinklist* pos, DataType data)
{
    if(head == NULL)
    {
        return ;
    }
    dblinklist* Node = CreatNode();
    Node->data = data;

    dblinklist* after_pos = pos->next;
    pos->next = Node;
    Node->prev = pos;

    Node->next = after_pos;
    after_pos->prev = Node;
}

//从任意位置前插入
void DbLinkListPushBeforeAnyPos(dblinklist* head, dblinklist* pos, DataType data)
{
    if(head == NULL)
    {
        return ;
    }
    dblinklist* Node = CreatNode();
    Node->data = data;
    dblinklist* before_pos = pos->prev;

    before_pos->next = Node;
    Node->prev = before_pos;

    Node->next = pos;
    pos->prev = Node;
}

//寻找元素的位置
dblinklist* DbLinkListFind(dblinklist* head, DataType to_find)
{
    if(head == NULL)
      return NULL;
    if(head->next == head)
      return NULL;

    dblinklist* temp = head->next;
    while(temp->next != head)
    {
        if(temp->data == to_find)
        {
            return temp;
        }
        temp = temp->next;
    }
    return NULL;
}

//删除任意位置的元素
void DLinkListRemoveAnyPos(dblinklist* head, dblinklist* pos) 
{
    if(head == NULL)
      return ;
    if(head->next == head)
      return ;

    dblinklist* before_pos = pos->prev;
    dblinklist* after_pos = pos->next;
    before_pos->next = after_pos;
    after_pos->prev = before_pos;

    DestoryNode(pos);
}

//删除与指定元素相同的所有结点
void DLinkListRemoveAll(dblinklist* head, DataType data) 
{
    if(head == NULL)
      return ;
    if(head->next == head)
      return ;

    dblinklist* temp = head->next;
    while(temp->next != head)
    {
        dblinklist* pos = DbLinkListFind(head, data);
        DLinkListRemoveAnyPos(head, pos); 
        temp = temp->next;
    }

}

//求环的大小
size_t DLinkListSize(dblinklist* head) 
{
    if(head == NULL)
      return 0;
    if(head->next == head)
      return 0;

    size_t count = 0;
    dblinklist* temp = head;
    while(temp->next != head)
    {
        count++;
        temp = temp->next;
    }
    return count;
}

//清空链表
int DLinkListEmpty(dblinklist** head)
{
    if(head == NULL)
      return 0;
    if((*head)->next == (*head))
      return 0;

    dblinklist* temp = *head;
    dblinklist* to_free = temp->next;
    while(to_free != *head)
    {
        temp->next = to_free->next;
        to_free->next->prev = temp;
        DestoryNode(to_free);
        to_free = temp->next;
    }
    (*head)->next = NULL;
    (*head)->prev = NULL;
    DestoryNode((*head));
    *head = NULL;

    return 0;
}

//打印链表
void DbLinkListPrint(dblinklist* head, char* msg)
{
    printf("[%s]\n", msg);
    if(head == NULL)
    {
        //非法输入
        printf("链表不存在\n");
        return ; 
    }
    if(head->next == head)
    {
        printf("空链表\n");
        return ;
    }
    dblinklist* temp = head->next;
    while(temp != head)
    {
        printf("[%c|%p] ", temp->data, temp->next);
        temp = temp->next;
    }
    printf("\n");
    dblinklist* temp1 = head->prev;
    while(temp1 != head)
    {
        printf("[%c|%p] ", temp1->data, temp1->prev);
        temp1 = temp1->prev;
    }
    printf("\n");
    return ;
}
