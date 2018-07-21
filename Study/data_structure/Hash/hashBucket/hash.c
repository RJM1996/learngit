/*================================================================

# File Name: hash.c
# Author: rjm
# mail: rjm96@foxmail.com
# Created Time: 2018年05月20日 星期日 13时06分36秒

================================================================*/

#include <stdlib.h>
#include "hash.h"

int func(KeyType key)
{
    return key % BucketMaxSize;
}

// 初始化
void HashInit(HashBucket* hb, HashFunc func)
{
    if(hb == NULL)
      return ;
    for(int i=0; i<BucketMaxSize; i++)
    {
        hb->data[i] = NULL;
    }
    hb->size = 0;
    hb->func = func;
}
// 创建新节点
HashElem* CreateNewNode(KeyType key, ValType value)
{
    HashElem* he = (HashElem*)malloc(sizeof(HashElem));
    he->key = key;
    he->value = value;
    he->next = NULL;
    return he;
}
// 插入元素
void HashInsert(HashBucket* hb, KeyType key, ValType value)
{
    if(hb == NULL)
      return ;
    // 根据key算出下标
    int offset = func(key);
    // 创建一个节点保存key和value
    HashElem* new_node = CreateNewNode(key, value);
    // 如果这个下标所保存链表的头指针为 NULL
    // 就直接让头指针指向新节点
    if(hb->data[offset] == NULL)
    {
        hb->data[offset] = new_node;
    }
    // 如果这个下标所保存链表的头指针已经指向了一个节点
    // 就把新节点头插到这个链表中
    else
    {
        if(key == hb->data[offset]->key)
        {
            // 元素相同, 不能插入
            return ;
        }
        else
        {
            // 直接头插
            HashElem* pre = hb->data[offset];
            hb->data[offset] = new_node;
            new_node->next = pre;
        }
    }
    ++hb->size;
}
// 查找元素
HashElem* HashFind(HashBucket* hb, KeyType key, ValType* value)
{
    if(hb == NULL)
      return NULL;
    if(hb->size == 0)
      return NULL;
    int offset = func(key);
    while(hb->data[offset] != NULL)
    {
        if(hb->data[offset]->key == key)
        {
            *value = hb->data[offset]->value;
            return hb->data[offset];
        }
        hb->data[offset] = hb->data[offset]->next;
    }
    return NULL;
}
// 删除元素
void HashRemove(HashBucket* hb, KeyType key)
{
    if(hb == NULL)
      return ;
    if(hb->size == 0)
      return ;
    int offset = func(key);
    HashElem* cur = hb->data[offset];
    HashElem* pre = hb->data[offset];
    if(cur == NULL)
      // 元素不存在
      return ;
    if(cur->next == NULL)
    {
        // 该位置的链表只有一个节点
        free(hb->data[offset]);
        hb->data[offset] = NULL;
        --hb->size;
        return ;
    }
    while(cur->next != NULL)
    {
        if(cur->key == key)
        {
            pre = cur;
        }
        cur = cur->next;
    }
    pre->next = cur->next;
    free(cur);
    cur = NULL;
    --hb->size;
}
// 销毁
void HashDestroy(HashBucket* hb)
{
    if(hb == NULL)
      return ;
    for(int i=0; i<BucketMaxSize; i++)
    {
        hb->data[i] = NULL;
    }
    hb->size = 0;
    hb->func = NULL;
}


///////////////////////////////////////////
// 测试函数
///////////////////////////////////////////
void HashPrint(HashBucket* hb, char* msg)
{
    printf("[ %s ]\n", msg);
    if(hb == NULL)
      return ;
    if(hb->size == 0)
      return ;
    for(int i=0; i<BucketMaxSize; i++)
    {
        HashElem* he = hb->data[i];
        if(hb->data[i] != NULL)
        {
            printf("[%d]\n", i);
            while(hb->data[i] != NULL)
            {
                printf("---[%d:%d]\n", hb->data[i]->key, hb->data[i]->value);
                hb->data[i] = hb->data[i]->next;
            }
        }
        hb->data[i] = he;
    }
}

void TestInit()
{
    TEST_HEAD;
    HashBucket hb;
    HashInit(&hb, func);
    HashPrint(&hb, "初始化哈希桶");
}
void TestInsert()
{
    TEST_HEAD;
    HashBucket hb;
    HashInit(&hb, func);
    HashInsert(&hb, 1001, 18);
    HashInsert(&hb, 1007, 13);
    HashInsert(&hb, 7, 11);
    HashInsert(&hb, 101, 12);
    HashPrint(&hb, "插入 4 个元素");
    HashInsert(&hb, 101, 12);
    HashPrint(&hb, "再插入一个已有的元素");
}
void TestFind()
{
    TEST_HEAD;
    HashBucket hb;
    HashInit(&hb, func);
    HashInsert(&hb, 1001, 18);
    HashInsert(&hb, 1007, 13);
    HashInsert(&hb, 7, 11);
    HashInsert(&hb, 101, 12);

    ValType value;
    HashElem* ret = HashFind(&hb, 1007, &value);
    printf("[查找元素 1007]\n");
    printf("ret excepted 1007, actual %d\n", ret->key);
    printf("value excepted 13, actual %d\n", value);

    ret = HashFind(&hb, 1008, &value);
    printf("[查找不存在的元素 1008]\n");
    printf("ret excepted NULL, actual %p\n", ret);
}
void TestRemove()
{
    TEST_HEAD;
    HashBucket hb;
    HashInit(&hb, func);
    HashInsert(&hb, 1001, 18);
    HashInsert(&hb, 1007, 13);
    HashInsert(&hb, 7, 11);
    HashInsert(&hb, 101, 12);
    HashPrint(&hb, "插入 4 个元素");
    HashRemove(&hb, 1007);
    HashPrint(&hb, "删除一个元素 1007");
    HashRemove(&hb, 1001);
    HashRemove(&hb, 7);
    HashPrint(&hb, "再删除2个元素 1001, 7");
    HashRemove(&hb, 101);
    HashPrint(&hb, "再删除1个元素 101");
    HashRemove(&hb, 101);
    HashPrint(&hb, "对空表进行删除");
}
void TestDestroy()
{
    TEST_HEAD;
    HashBucket hb;
    HashInit(&hb, func);
    HashInsert(&hb, 1001, 18);
    HashInsert(&hb, 1007, 13);
    HashInsert(&hb, 7, 11);
    HashInsert(&hb, 101, 12);
    HashPrint(&hb, "插入 4 个元素");

    HashDestroy(&hb);
    HashPrint(&hb, "销毁哈希表");
}

int main()
{
    TestInit();
    TestInsert();
    TestFind();
    TestRemove();
    TestDestroy();

    printf("\n");
    printf("\n");
    printf("\n");
    return 0;
}
