/*================================================================

# File Name: hash.h
# Author: rjm
# mail: rjm96@foxmail.com
# Created Time: 2018年05月20日 星期日 13时06分57秒

================================================================*/

// 哈希桶
// 数组的每个元素都是一张链表的头指针
#pragma once

#include <stdio.h>

#define TEST_HEAD printf("\n=================%s================\n", __FUNCTION__)
#define BucketMaxSize 1000 // 桶的个数为1000

typedef int KeyType;
typedef int ValType;
typedef int (*HashFunc)(KeyType key);

typedef struct HashElem {
    KeyType key;
    ValType value;
    struct HashElem* next;
} HashElem;

typedef struct HashBucket {
    HashElem* data[BucketMaxSize];
    size_t size; // 当前元素的个数
    HashFunc func;
} HashBucket;

// 初始化
void HashInit(HashBucket* hb, HashFunc func);

// 插入元素
void HashInsert(HashBucket* hb, KeyType key, ValType value);

// 查找元素
HashElem* HashFind(HashBucket* hb, KeyType key, ValType* value);

// 删除元素
void HashRemove(HashBucket* hb, KeyType key);

// 销毁
void HashDestroy(HashBucket* hb);
