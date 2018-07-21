#include"linkqueue.h"
#include <stdio.h>
#include <stdlib.h>
void LinkQueueInit(LinkQueue* q)
{
    if(q == NULL)
    {
        //非法输入
        return;
    }
    q->head = q->tail = (LinkNode*) malloc(sizeof(LinkNode));
    if(!q->head)
    {
        printf("申请内存失败！\n");
        return;
    }
    q->head = NULL;
    return;
}
void LinkQueueDestroy(LinkQueue* q)//销毁队列
{
    if(q == NULL)
    {
        //非法输入
        return;
    }
    free(q->head);
    free(q->tail);
    q->head = q->tail = NULL;
    return;
}
void DestroyLinkNode(LinkNode* q)
{
    if(q == NULL)
    {
        return;
    }
    free(q);
    q = NULL;
    return;
}
LinkQueue* CreateLinkNode()
{
    LinkQueue* tmp = (LinkQueue*)malloc(sizeof(LinkQueue));
    if(!tmp)
    {
        printf("CreateLinkNode error!\n");
        return NULL;
    }
    LinkNode* head = (LinkNode*)malloc(sizeof(LinkNode));
    LinkNode* tail = (LinkNode*)malloc(sizeof(LinkNode));
    tmp->head = head;
    tmp->tail = tail;
    return tmp;
}
void LinkQueuePush(LinkQueue* q,LinkType value)
{
    if(q == NULL)
    {
        //非法输入
        return;
    }
    LinkNode* temp = (LinkNode*)malloc(sizeof(LinkNode));
    temp->data = value;
    temp->next = NULL;
    q->tail->next = temp;
    q->tail = temp;
    return;
}
int LinkQueuePop(LinkQueue* q,LinkType* value)
{
    if(q == NULL || value == NULL)
    {
        //非法输入
        return 0;
    }
    if(q->head == NULL)
    {
        //空队列
        printf("q->head == NULL\n");
        return 0;
    }
    LinkNode* to_delete = q->head->next;
    if(q->head->next == q->tail)
    {
        //如果要删除元素为最后一个元素，让尾指针指向头节点
        q->tail = q->head;
    }
    *value = to_delete->data;
    q->head->next = to_delete->next;
    DestroyLinkNode(to_delete);
    return 1;
}
//////////////////////////////////////////////////////////////////////////
//以下为测试代码
/////////////////////////////////////////////////////////////////////////
#if 1
#define TEST_HEADER printf("\n======================%s========================\n",__FUNCTION__);
void TestQueue()
{
    TEST_HEADER;
    LinkQueue queue;
    LinkQueueInit(&queue);
    LinkQueuePush(&queue,'a');
    LinkQueuePush(&queue,'b');
    LinkQueuePush(&queue,'c');
    LinkQueuePush(&queue,'d');
    LinkType value;
    int ret = LinkQueuePop(&queue,&value);
    printf("ret expected 1,actual %d\n",ret);
    printf("value expected a,actual %c\n",value);
    ret = LinkQueuePop(&queue,&value);
    printf("ret expected 1,actual %d\n",ret);
    printf("value expected b,actual %c\n",value);
    ret = LinkQueuePop(&queue,&value);
    printf("ret expected 1,actual %d\n",ret);
    printf("value expected c,actual %c\n",value);
    ret = LinkQueuePop(&queue,&value);
    printf("ret expected 1,actual %d\n",ret);
    printf("value expected d,actual %c\n",value);
}
int main()
{
    TestQueue();
    return 0;
}
#endif
