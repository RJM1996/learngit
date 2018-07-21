/*================================================================

# File Name: heap.h
# Author: rjm
# mail: rjm96@foxmail.com
# Created Time: 2018年05月12日 星期六 14时43分40秒

================================================================*/


#pragma once
// 1. 堆是一个完全二叉树
// 2. 堆有两种, 一种叫小堆(小根堆, 最小堆),
//    一种叫大堆(大根堆, 最大堆).
// 3. 以小堆为例, 这个树的根节点是这个树中的最小的元素
//    对于任意一个子树来说, 子树的根节点, 小于左右孩子节点的值.
// 4. 以大堆为例, 这个树的根节点是这个树中的最大的元素
//    对于任意一个子树来说, 子树的根节点, 大于左右孩子节点的值.

#include <stdio.h>

#define TEST_HEAD printf("\n===============%s=================\n", __FUNCTION__)
#define HeapMaxSize 1000

typedef int HeapType;
typedef int (*Compare)(HeapType a, HeapType b); 

typedef struct Heap
{
    HeapType data[HeapMaxSize];
    size_t size;
    Compare cmp;
} Heap;

//初始化堆
void HeapInit(Heap *heap, Compare cmp);
//插入元素
void HeapInsert(Heap *heap, HeapType value, Compare cmp);
// 取堆顶元素
int HeapTop(Heap *heap, HeapType *value);
// 删除堆顶元素
void HeapErase(Heap *heap, Compare cmp);
//清空堆
int HeapEmpty(Heap *heap);
//求堆的大小
size_t HeapSize(Heap *heap);
//销毁堆
void HeapDestroy(Heap *heap);
//向下调整
void AdjustDown();
//打印堆
void printHeap();

// 在我们不想开辟额外的空间, 或者消耗额外的时间的前提下,
// 如果我们想进行从小到大排序, 就需要一个大堆
// 如果我们想进行从大到小排序, 就需要一个小堆
void HeapSort(HeapType array[], size_t size, Compare cmp);

