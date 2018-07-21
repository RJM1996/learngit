/*================================================================

# File Name: hash.c
# Author: rjm
# mail: rjm96@foxmail.com
# Created Time: 2018年05月18日 星期五 18时25分38秒

================================================================*/

// 哈希表
#include <stdio.h>
#include "hash.h"

// 初始化
void HashInit(HashTable* ht, HashFunc hash_func)
{
    ht->size = 0;
    ht->func = hash_func;
    for(int i=0; i<HashMaxSize; i++)
    {
        ht->data[i].stat = Empty;
    }
    return ;
}
// 插入
void HashInsert(HashTable* ht, KeyType key, ValueType value)
{
    if(ht->size == HashMaxSize)
    {
        // 哈希表已经满了
        return ;
    }
    int offset = func(key);
    ValueType val;
    if(HashFind(ht, key, &val) == 1)
      return ;
    if(ht->data[offset].stat != valid)
    {
        ht->data[offset].key = key;
        ht->data[offset].value = value;
        ht->data[offset].stat = valid;
        ++ht->size;
    }
    else
    {
        while(1)
        {
            offset++;
            if(offset == HashMaxSize)
            {
                offset = 0;
            }
            if(ht->data[offset].stat != valid)
              break;
        }
        ht->data[offset].key = key;
        ht->data[offset].value = value;
        ht->data[offset].stat = valid;
        ++ht->size;
    }
}
// 查找
int HashFind(HashTable* ht, KeyType key, int* to_find)
{
    if(ht->size == 0)
    {
        // 哈希表为空
        return 0;
    }
    int offset = func(key);
    if(ht->data[offset].key == key)
    {
        *to_find = offset;
        return 1;
    }
    else
    {
        while(ht->data[offset].stat != Empty)
        {
            ++offset;
            if(offset == HashMaxSize)
            {
                offset = 0;
            }
            if(ht->data[offset].key == key && ht->data[offset].stat == valid)
            {
                *to_find = offset;
                return 1;
            }
        }
        return 0;
    }
}
// 删除
void HashRemove(HashTable* ht, KeyType key)
{
    if(ht->size == 0)
    {
        // 哈希表为空
        return ;
    }
    int offset = 0;
    int ret = HashFind(ht, key, &offset);
    if(ret == 0)
    {
        // 元素不存在
        return ;
    }
    // 如果元素存在, 则把它的状态改为已删除
    ht->data[offset].stat = deleted;
    --ht->size;
}
// 销毁
void HashDestroy(HashTable* ht)
{
    ht->size = 0;
    ht->func = NULL;
    for(int i = 0; i<HashMaxSize; i++)
    {
        ht->data[i].stat = Empty;
    }
}

////////////////////////////////////
// 测试函数
////////////////////////////////////

void HashPrint(HashTable* ht, char* msg)
{
    printf("[ %s ]\n", msg);
    for(int i=0; i<HashMaxSize; i++)
    {
        if(ht->data[i].stat == valid)
        {
            printf("[%d| %d:%d]\n", i, ht->data[i].key, ht->data[i].value);
        }
    }
    printf("\n");
}

void TestInit()
{
    TEST_HEAD;
    HashTable ht;
    HashInit(&ht, func);
    HashPrint(&ht, "初始化哈希表");
}
void TestInsert()
{
    TEST_HEAD;
    HashTable ht;
    HashInit(&ht, func);
    HashInsert(&ht, 1, 10);
    HashInsert(&ht, 1001, 12);
    HashInsert(&ht, 2, 10);
    HashInsert(&ht, 2, 15);
    HashInsert(&ht, 1002, 10);
    HashPrint(&ht, "插入 5 个元素, 其中 2 插入两次");
}
void TestFind()
{
    TEST_HEAD;
    HashTable ht;
    HashInit(&ht, func);
    HashInsert(&ht, 1, 10);
    HashInsert(&ht, 1001, 12);
    HashInsert(&ht, 2, 10);
    HashInsert(&ht, 2, 15);
    HashInsert(&ht, 1002, 10);

    int offset = 0;
    int ret = 0;

    HashPrint(&ht, "查找元素 1001");
    ret = HashFind(&ht, 1001, &offset);
    printf("ret expect 1, actual %d\n", ret);
    printf("offset expect 2, actual %d\n", offset);
    printf("\n");
    HashPrint(&ht, "查找元素 1003");
    ret = HashFind(&ht, 1003, &offset);
    printf("ret expect 0, actual %d\n", ret);
}
void TestRemove()
{
    TEST_HEAD;
    HashTable ht;
    HashInit(&ht, func);
    HashInsert(&ht, 1, 10);
    HashInsert(&ht, 1001, 12);
    HashInsert(&ht, 2, 10);
    HashInsert(&ht, 2, 15);
    HashInsert(&ht, 1002, 10);

    HashRemove(&ht, 1001);
    HashPrint(&ht, "删除一个元素 1001");
    HashRemove(&ht, 1002);
    HashPrint(&ht, "再删除一个元素 1002");
    HashRemove(&ht, 2);
    HashPrint(&ht, "再删除一个元素 2");
    HashRemove(&ht, 1);
    HashPrint(&ht, "再删除一个元素 1");
    HashRemove(&ht, 2);
    HashPrint(&ht, "再删除一个元素 2");
    HashRemove(&ht, 2);
    HashPrint(&ht, "对空表删除");
    printf("size = %d\n", ht.size);
}
void TestDestroy()
{
    TEST_HEAD;
    HashTable ht;
    HashInit(&ht, func);
    HashInsert(&ht, 1, 10);
    HashInsert(&ht, 1001, 12);
    HashInsert(&ht, 2, 10);
    HashInsert(&ht, 2, 15);
    HashInsert(&ht, 1002, 10);

    HashDestroy(&ht);
    HashPrint(&ht, "销毁哈希表");
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
