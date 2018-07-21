/*================================================================
# File Name: heap.c
# Author: rjm
# mail: rjm96@foxmail.com
# Created Time: 2018年05月11日 星期五 14时09分13秒
================================================================*/
#include <stdio.h>
#include <string.h>
#include "heap.h"

//堆: 是一棵完全二叉树
//最大堆: 每个根节点的值都大于左右孩子节点的值
//最小堆: 每个根节点的值都小于左右孩子节点的值


int cmp_max(HeapType a, HeapType b)
{
    return a > b ? 1 : 0;
}
int cmp_min(HeapType a, HeapType b)
{
    return a < b ? 1 : 0;
}
//交换数组元素的函数
void Swap(int a, int b, Heap* heap)
{
    HeapType tmp = heap->data[a];
    heap->data[a] = heap->data[b];
    heap->data[b] = tmp;
}
//初始化堆
void HeapInit(Heap* heap, Compare cmp)
{
    heap->size = 0;
    cmp = NULL;
}
//插入元素
void HeapInsert(Heap* heap, HeapType value, Compare cmp)
{
    if(heap == NULL)
    {
        return ;
    }
    if(heap->size == HeapMaxSize)
    {
        //堆已经满了
        return ;
    }
    //否则, 先将其插入堆的最后, 下标为size
    //再将其上浮, 直到满足堆的规则
    heap->data[heap->size] = value;
    int cur = heap->size;
    int father = (cur-1)/2;
    while(cur > 0 && cmp( heap->data[cur], heap->data[father] ) == 1)
    {
        Swap(cur, father, heap);
        cur = father;
        father = (cur-1)/2;
    }
    ++heap->size;
}
// 取堆顶元素
int HeapTop(Heap *heap, HeapType *value)
{
    if(heap == NULL)
    {
        //堆为空
        return 0;
    }
    *value = heap->data[0];
    return 1;
}
// 删除堆顶元素
void HeapErase(Heap *heap, Compare cmp)
{
    if(heap == NULL)
    {
        return ;
    }
    if(heap->size == 0)
    {
        //空堆
        return ;
    }
    //交换堆顶元素和最后一个元素
    Swap(0, (heap->size)-1, heap);
    //size--, 删除最后一个元素
    --heap->size;
    //然后再进行调整, 使其满足堆的性质
    AdjustDown(heap, 0, cmp);
}

//清空堆
int HeapEmpty(Heap *heap)
{
    if(heap == NULL)
      //空堆
      return 0;
    heap->size = 0;
    return 1;
}
//求堆的大小
size_t HeapSize(Heap *heap)
{
    if(heap == NULL)
      //空堆
      return 0;
    return heap->size;
}
//销毁堆
void HeapDestroy(Heap *heap)
{
    if(heap == NULL)
      return ;
    heap->size = 0;
}
//将一个数组变为一个堆
void Array_to_Heap(Heap* heap, HeapType* arr, int arr_size, Compare cmp)
{
    if(arr == NULL)
      return ;
    for(int i=0; i<arr_size; i++)
    {
        HeapInsert(heap, arr[i], cmp);
    }
    memcpy(arr, heap->data, sizeof(HeapType)*arr_size);
}
// 堆排序
// 在我们不想开辟额外的空间, 或者消耗额外的时间的前提下,
// 如果我们想进行从小到大排序, 就需要一个大堆
// 如果我们想进行从大到小排序, 就需要一个小堆
void HeapSort(HeapType array[], size_t size, Compare cmp)
{
    if(array == NULL)
      return ;
    Heap heap;
    HeapInit(&heap, cmp);
    Array_to_Heap(&heap, array, size, cmp);
    printHeap(&heap, "堆排序");
    HeapType value;
    for(int i=0; i<size; i++)
    {
        HeapTop(&heap, &value);
        HeapErase(&heap, cmp);
        array[i] = value;
    }
}

//向下调整
void AdjustDown(Heap* heap, int index, Compare cmp)
{
    if(index < 0)
      return ;
    int tmp = 0;//用来临时保存最小的值的下标
    int IsNeedAdjust_flag = 0;//判断是否需要调整的标志
    //当前节点有孩子 并且 需要调整时, 进入循环
    while(index*2+1 < heap->size && IsNeedAdjust_flag == 0)
    {
        //如果右子树存在, 先比较左右子树的大小
        if(index*2+2 < heap->size)
        {
            if(cmp(heap->data[index*2+1], heap->data[index*2+2]) == 1)
            {
                tmp = index*2+1;
            }
            else
            {
                tmp = index*2+2;
            }
            if(cmp(heap->data[index], heap->data[tmp]) == 0)
            {
                Swap(index, tmp, heap);
                index = tmp;
            }
            else
                IsNeedAdjust_flag = 1;
        }
        //如果右子树不存在, 就和左子树比较
        else
        {
            if(cmp(heap->data[index], heap->data[index*2+1]) == 0)
            {
                Swap(index, index*2+1, heap);
                index = index*2+1;
            }
            else
              IsNeedAdjust_flag = 1;
        }
    }
}

//打印堆
void printHeap(Heap* heap, char* msg)
{
    printf("\n=====%s=====\n", msg);
    if(heap == NULL)
      return ;
    for(int i=0; i<heap->size; i++)
    {
        printf("[%2d|%2d] ", i, heap->data[i]);
    }
    printf("\n");
}
/*********************************************************
  测试代码
 *********************************************************/
//测试堆的创建
void TestHeapInsert()
{
    TEST_HEAD;
    Heap heap;
    HeapInit(&heap, cmp_min);
    HeapInsert(&heap, 1, cmp_min);
    HeapInsert(&heap, 3, cmp_min);
    HeapInsert(&heap, 0, cmp_min);
    HeapInsert(&heap, 5, cmp_min);
    HeapInsert(&heap, 4, cmp_min);
    HeapInsert(&heap, 7, cmp_min);
    HeapInsert(&heap, 9, cmp_min);
    HeapInsert(&heap, 8, cmp_min);
    HeapInsert(&heap, 6, cmp_min);
    HeapInsert(&heap, 2, cmp_min);
    printHeap(&heap, "往堆中插入4个元素");
}
//测试删除堆顶元素
void TestHeapDeleteTop()
{
    TEST_HEAD;
    Heap heap;
    HeapInit(&heap, cmp_min);
    HeapInsert(&heap, 1, cmp_min);
    HeapInsert(&heap, 2, cmp_min);
    HeapInsert(&heap, 3, cmp_min);
    HeapInsert(&heap, 4, cmp_min);
    HeapErase(&heap, cmp_min);
    printHeap(&heap, "删除一次堆顶元素");
    HeapErase(&heap, cmp_min);
    HeapErase(&heap, cmp_min);
    printHeap(&heap, "再删除两次堆顶元素");
    HeapErase(&heap, cmp_min);
    printHeap(&heap, "再删除一次堆顶元素");
    HeapErase(&heap, cmp_min);
    printHeap(&heap, "对空堆删除");
}
//测试将一个数组变为一个堆
void TestArrToHeap()
{
    TEST_HEAD;
    HeapType arr[] = {9, 1, 8, 2, 7, 3, 6, 4, 0, 5};
    int size = sizeof(arr)/sizeof(arr[0]);
    printf("size = %d\n", size);
    Heap heap;
    HeapInit(&heap, cmp_min);
    Array_to_Heap(&heap, arr, size, cmp_max);
    for(int i=0; i<size; i++)
    {
        printf("[%2d|%2d] ", i, arr[i]);
    }
}

//测试获取堆顶元素
void TestHeapTop()
{
    TEST_HEAD;
    Heap heap;
    HeapInit(&heap, cmp_min);
    HeapInsert(&heap, 1, cmp_min);
    HeapInsert(&heap, 2, cmp_min);
    HeapInsert(&heap, 3, cmp_min);
    HeapInsert(&heap, 4, cmp_min);
    HeapType value;
    HeapTop(&heap, &value);
    printf("expect 1, actual %d\n", value);
}

//测试堆排序
void TestHeapSort_min()
{
    TEST_HEAD;
    HeapType arr[] = {1, 3, 0, 5, 4, 7, 9, 8, 6, 2};
    //HeapType arr[] = {9, 1, 8, 2, 7, 3, 6, 4, 0, 5};
    int size = sizeof(arr)/sizeof(arr[0]);

    HeapSort(arr, size, cmp_min);

    for(int i=0; i<size; i++)
    {
        printf("[%d]", arr[i]);
    }
}
void TestHeapSort_max()
{
    TEST_HEAD;
    HeapType arr[] = {1, 3, 0, 5, 4, 7, 9, 8, 6, 2};
    //HeapType arr[] = {9, 1, 8, 2, 7, 3, 6, 4, 0, 5};
    int size = sizeof(arr)/sizeof(arr[0]);

    HeapSort(arr, size, cmp_max);

    for(int i=0; i<size; i++)
    {
        printf("[%d]", arr[i]);
    }
}
int main()
{
    TestHeapInsert();
    TestHeapDeleteTop();
    TestHeapTop();
    TestArrToHeap();
    TestHeapSort_min();
    TestHeapSort_max();

    printf("\n");
    printf("\n");
    printf("\n");
    return 0;
}
