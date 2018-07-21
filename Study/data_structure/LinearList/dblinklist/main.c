
#include "dblinklist.h"


void TestFind()
{
    TESTHEAD;
    dblinklist* head;
    DbLinkListInit(&head); 
    DbLinkListPushBack(head, 'a');
    DbLinkListPushBack(head, 'b');
    DbLinkListPushBack(head, 'c');
    DbLinkListPushBack(head, 'd');
    DbLinkListPrint(head, "尾插四个元素");
    dblinklist* pos = DbLinkListFind(head, 'c');
    printf("pos = %p\n", pos);

}
void TestPushAnyPosBefore()
{
    TESTHEAD;
    dblinklist* head;
    DbLinkListInit(&head); 
    DbLinkListPushBack(head, 'a');
    DbLinkListPushBack(head, 'b');
    DbLinkListPushBack(head, 'c');
    DbLinkListPushBack(head, 'd');
    DbLinkListPrint(head, "尾插四个元素");
    dblinklist* pos = head->next->next;
    DbLinkListPushBeforeAnyPos(head, pos, 'z');
    DbLinkListPrint(head, "在[b]前面插入[z]");
}

void TestPushAnyPosAfter()
{
    TESTHEAD;
    dblinklist* head;
    DbLinkListInit(&head); 
    DbLinkListPushBack(head, 'a');
    DbLinkListPushBack(head, 'b');
    DbLinkListPushBack(head, 'c');
    DbLinkListPushBack(head, 'd');
    DbLinkListPrint(head, "尾插四个元素");
    dblinklist* pos = head->next->next;
    DbLinkListPushAfterAnyPos(head, pos, 'x');
    DbLinkListPrint(head, "在[b]后面插入[x]");
}
void TestPushBack()
{
    TESTHEAD;
    dblinklist* head;
    DbLinkListInit(&head); 
    DbLinkListPushBack(head, 'a');
    DbLinkListPushBack(head, 'b');
    DbLinkListPushBack(head, 'c');
    DbLinkListPushBack(head, 'd');
    DbLinkListPrint(head, "尾插四个元素");
}

void TestPopBack()
{
    TESTHEAD;
    dblinklist* head;
    DbLinkListInit(&head); 
    DbLinkListPushBack(head, 'a');
    DbLinkListPushBack(head, 'b');
    DbLinkListPushBack(head, 'c');
    DbLinkListPushBack(head, 'd');
    DbLinkListPopBack(head);
    DbLinkListPopBack(head);
    DbLinkListPrint(head, "尾删两个元素");
    DbLinkListPopBack(head);
    DbLinkListPopBack(head);
    DbLinkListPrint(head, "再尾删两个元素");
    DbLinkListPopBack(head);
    DbLinkListPrint(head, "对空链表尾删");
}

void TestPushFront()
{
    TESTHEAD;
    dblinklist* head;
    DbLinkListInit(&head); 
    DbLinkListPushFront(head, 'a');
    DbLinkListPushFront(head, 'b');
    DbLinkListPushFront(head, 'c');
    DbLinkListPushFront(head, 'd');
    DbLinkListPrint(head, "头插四个元素");
}

void TestRemoveAnyPos()
{
    TESTHEAD;
    dblinklist* head;
    DbLinkListInit(&head); 
    DbLinkListPushFront(head, 'a');
    DbLinkListPushFront(head, 'b');
    DbLinkListPushFront(head, 'c');
    DbLinkListPushFront(head, 'd');
    DbLinkListPrint(head, "头插四个元素");
    dblinklist* pos = DbLinkListFind(head, 'b');
    DLinkListRemoveAnyPos(head, pos);
    DbLinkListPrint(head, "删除元素[b]");
}

void TestRemoveAll()
{
    TESTHEAD;
    dblinklist* head;
    DbLinkListInit(&head); 
    DbLinkListPushFront(head, 'a');
    DbLinkListPushFront(head, 'c');
    DbLinkListPushFront(head, 'c');
    DbLinkListPushFront(head, 'd');
    DbLinkListPrint(head, "头插四个元素");
    DLinkListRemoveAll(head, 'c');
    DbLinkListPrint(head, "删除所有的[c]");
}

void TestSize()
{
    TESTHEAD;
    dblinklist* head;
    DbLinkListInit(&head); 
    DbLinkListPushFront(head, 'a');
    DbLinkListPushFront(head, 'c');
    DbLinkListPushFront(head, 'c');
    DbLinkListPushFront(head, 'd');
    DbLinkListPrint(head, "头插四个元素");
    size_t size = DLinkListSize(head);
    printf("size = %d\n", size);
}

void TestEmpty()
{
    TESTHEAD;
    dblinklist* head;
    DbLinkListInit(&head); 
    DbLinkListPushFront(head, 'a');
    DbLinkListPushFront(head, 'c');
    DbLinkListPushFront(head, 'c');
    DbLinkListPushFront(head, 'd');
    DbLinkListPrint(head, "头插四个元素");
    DLinkListEmpty(&head);
    DbLinkListPrint(head, "销毁链表");
}

int main()
{
    TestPushBack();
    TestPopBack();
    TestPushFront();
    TestPushAnyPosAfter();
    TestPushAnyPosBefore();
    TestFind();
    TestRemoveAnyPos();
    TestRemoveAll();
    TestSize();
    TestEmpty();
    printf("\n\n");
    printf("\n\n");
    printf("\n\n");
    printf("\n\n");
    return 0;
}
