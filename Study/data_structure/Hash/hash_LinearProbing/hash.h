/*================================================================

# File Name: hash.h
# Author: rjm
# mail: rjm96@foxmail.com
# Created Time: 2018年05月18日 星期五 18时26分13秒

================================================================*/


// 哈希表
#pragma once

#define TEST_HEAD printf("\n==================%s===============\n", __FUNCTION__)
#define HashMaxSize 1000

typedef int KeyType; // 要插入的值
typedef int ValueType;
// 计算下标的函数
typedef int (*HashFunc)(KeyType key);

typedef enum Stat {
    Empty, // 空状态, 表示这个位置还没有元素插入
    valid, // 有效状态, 表示这个位置已经有元素插入了
    deleted, // 已删除状态, 表示这个位置的元素已经被删除了
} Stat;

// 键值对
typedef struct HashElem {
    KeyType key;
    ValueType value;
    Stat stat; //每个位置的状态
} HashElem;

int func(KeyType key)
{
    return key % HashMaxSize;
}

typedef struct HashTable {
    HashElem data[HashMaxSize]; //哈希表数组, 存的是包含一组键值对的结构体
    size_t size; //哈希表当前有效元素的个数
    HashFunc func; //计算下标的函数
} HashTable;


// 初始化
void HashInit(HashTable* ht, HashFunc hash_func);

// 插入元素
void HashInsert(HashTable* ht, KeyType key, ValueType value);

// 查找
int HashFind(HashTable* ht, KeyType key, int* to_find);

// 删除
void HashRemove(HashTable* ht, KeyType key);

// 销毁
void HashDestroy(HashTable* ht);
