/*================================================================

# File Name: Sort.c
# Author: rjm
# mail: rjm96@foxmail.com
# Created Time: 2018年05月25日 星期五 20时16分47秒

================================================================*/

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>

#define TEST_HEAD printf("\n============%s================\n", __FUNCTION__)

void Swap(int* a, int* b)
{
    int tmp = *a;
    *a = *b;
    *b = tmp;
}
///////////////////////////////////////////////
// 1, 冒泡排序
//    时间复杂度: O(n^2)
//    空间复杂度: O(1)
//    稳定的
//////////////////////////////////////////////
void BubbleSort(int arr[], size_t size)
{
    if(size <= 1)
    {
        return ;
    }
    int bound = 0;
    int cur = 0;
    for(; bound < size; ++bound)
    {
        cur = size - 1;
        for(; cur > bound; --cur)
        {
            if(arr[cur] < arr[cur - 1])
            {
                Swap(&arr[cur], &arr[cur - 1]);
            }
        } // 第二重循环
    } // 第一重循环
}

/////////////////////////////////////////////
// 2, 选择排序
//    时间复杂度: O(n^2)
//    空间复杂度: O(1)
//    不稳定
/////////////////////////////////////////////
void SelectSort(int arr[], size_t size)
{
    if(size <= 1)
      return ;
    size_t bound = 0;
    for(; bound<size; ++bound)
    {
        size_t cur = bound + 1;
        for(; cur < size; ++cur)
        {
            if(arr[cur] < arr[bound])
            {
                Swap(&arr[cur], &arr[bound]);
            }
        } // 第二重循环
    } // 第一重循环
}

///////////////////////////////////////////
// 3, 插入排序
//    时间复杂度:O(n^2)
//    空间复杂度:O(1)
//    稳定的
///////////////////////////////////////////
void InsertSort(int arr[], size_t size)
{
    if(size <= 1)
      return ;
    size_t bound = 1;
    for(; bound < size; ++bound)
    {
        // 保存arr[bound] 是为了后面的还原
        int bound_value = arr[bound];
        size_t cur = bound;
        for(; cur > 0; --cur)
        {
            if(arr[cur-1] > bound_value)
            {
                arr[cur] = arr[cur-1];
            }
            else
            {
                break;
            }
        }
        arr[cur] = bound_value;
    }
}
//////////////////////////////////////////////
// 4, 堆排序
//    时间复杂度: O(N*logN)
//    空间复杂度: O(1)
//    不稳定
/////////////////////////////////////////////
// 升序: 建立大堆
// 降序: 建立小堆
// 步骤: 1, 先根据数组建立一个堆
//       2, 依次交换堆顶元素和最后一个元素, 并删除最后一个元素
//       3, 堆为空时, 数组就有序了
// 建堆方法:
//       1, 下沉式调整:
//          a) 从后往前遍历数组, 找到第一个非叶子节点
//          b) 再找到它的父节点
//          c) 和它父节点比较, 是否需要交换
void AdjustDown(int arr[], size_t size, size_t i)
{
    if(size <= 1)
      return ;
    size_t parent = i;
    // 找到它的左孩子节点
    size_t child = 2 * parent + 1;
    while(child < size)
    {
        // 先比较左右孩子节点的大小, 找到较大的
        if(child + 1 < size && arr[child] < arr[child+1])
        {
            child = child+1;
        }
        // 再和父节点比较, 因为要建立大堆, 所以大于父节点就交换
        if(arr[child] > arr[parent])
        {
            Swap(&arr[child], &arr[parent]);
        }
        // 更新父节点, 孩子节点
        parent = child;
        child = 2 * parent + 1;
    }
}
void AdjustUp(int arr[], size_t bound)
{
    size_t child = bound;
    size_t parent = (child - 1) / 2;
    while(child > 0)
    {
        if(arr[parent] < arr[child])
        {
            Swap(&arr[parent], &arr[child]);
        }
        else
        {
            break;
        }
        child = parent;
        parent = (child - 1) / 2;
    }
}
void HeapCreate(int arr[], size_t size)
{
    if(size <= 1)
    {
        return ;
    }
#if 0
    // 1, 下沉式调整
    // 从最后一个非叶子节点开始
    size_t i = (size-1-1)/2;
    for(; i>0; --i)
    {
        AdjustDown(arr, size, i);
    }
    AdjustDown(arr, size, i);
#else
    // 2, 上浮式调整
    size_t bound = 0;
    for(; bound < size; ++bound)
    {
        AdjustUp(arr, bound + 1);
    }
#endif
}
void HeapPop(int arr[], size_t heap_size)
{
    // 当堆只剩下一个元素时, 就已经有序了
    if(heap_size <= 1)
      return ;
    // 将堆顶元素和当前堆的最后一个元素交换
    Swap(&arr[0], &arr[heap_size - 1]);
    AdjustDown(arr, heap_size-1, 0);
}
void HeapSort(int arr[], size_t size)
{
    if(size <= 1)
    {
        return ;
    }
    // 先基于数组根据升序还是降序, 建立一个大堆或小堆
    HeapCreate(arr, size);
    size_t i = 0;
    for(; i < size; i++)
    {
        // 依次交换堆顶元素和最后一个元素
        // 然后"删除"最后一个元素, 重新调整堆
        // 使其重新满足堆的规则
        HeapPop(arr, size-i); // size - i 表示当前堆的大小
    }
}

//////////////////////////////////////////////////
// 5, 希尔排序
//    时间复杂度: O(N ^ 2), 如果gap选择适当, 可以达到O(N ^ 1.3)
//    空间复杂度: O(1)
//    不稳定的
//////////////////////////////////////////////////
// 插入排序的改进版本
// 设置步长 gap
// 根据 gap 分组, 然后对每组分别进行插入排序
// 步长设置采用希尔序列: gap = N/2 N/4 N/8 ... 1
void ShellSort(int arr[], size_t size)
{
    if(size <= 1)
      return ;
    size_t gap = size / 2; //初始步长
    for(; gap > 0; gap /= 2) //步长每次 / 2
    {
        size_t bound = gap;
        for(; bound < size; ++bound)
        {
            int bound_value = arr[bound];
            size_t cur = bound;
            for(; cur >= gap; cur -= gap) //cur -= gap 找到它的前一个元素
            {
                if(arr[cur - gap] > bound_value)
                {
                    Swap(&arr[cur], &arr[cur - gap]);
                }
                else
                {
                    break;
                }
            }
            //arr[cur] = bound_value;
        } // 第二重循环
    } // 第一重循环
}

////////////////////////////////////////////
// 6, 归并排序
//    时间复杂度: O(N*logN)
//    空间复杂度: O(N)
//    稳定的
////////////////////////////////////////////
// 递归版本
void _MergeArray(int arr[], int64_t beg, int64_t mid, int64_t end, int* tmp)
{
    // 两个数组的首元素下标
    int64_t arr1_beg = beg;
    int64_t arr2_beg = mid;
    // tmp数组的下标
    int64_t tmp_index = beg;
    while(arr1_beg < mid && arr2_beg < end)
    {
        // 比较两个数组的首元素, 较小的放入tmp数组
        if(arr[arr1_beg] < arr[arr2_beg])
        {
            tmp[tmp_index++] = arr[arr1_beg++];
        }
        else
        {
            tmp[tmp_index++] = arr[arr2_beg++];
        }
    }
    // 循环结束, 将剩下的数组元素接到tmp后面
    while(arr1_beg < mid)
    {
        tmp[tmp_index++] = arr[arr1_beg++];
    }
    while(arr2_beg < end)
    {
        tmp[tmp_index++] = arr[arr2_beg++];
    }
    // 最后再将tmp的元素拷贝到arr数组
    memcpy(arr+beg, tmp+beg, sizeof(int)*(end - beg));
}
void _MergeSort(int arr[], int64_t beg, int64_t end, int* tmp)
{
    if(end - beg <= 1)
      return ;
    if(beg < end)
    {
        int64_t mid = beg + (end - beg) / 2;
        // 此时有了两个区间 [beg, mid), [mid, end)
        // 将这两个区间分别再递归排序
        _MergeSort(arr, beg, mid, tmp);
        _MergeSort(arr, mid, end, tmp);
        _MergeArray(arr, beg, mid, end, tmp);
    }
}
void MergeSort(int arr[], int64_t size)
{
    if(size <= 1)
      return ;
    // 申请临时空间tmp进行归并
    int* tmp = (int*)malloc(sizeof(int)*size);
    int beg = 0;
    _MergeSort(arr, beg, size, tmp);
    free(tmp);
}
// 非递归版本归并排序
void MergeSortByLoop(int arr[], size_t size)
{
    if(size <= 1)
      return ;
    int* tmp = (int*)malloc(sizeof(int)*size);
    // 设置步长 gap = 1, 2, 4 ...
    size_t gap = 1;

    for(; gap < size; gap *= 2)
    {
        size_t i = 0;
        for(; i < size; i += 2*gap)
        {
            size_t beg = i;
            size_t mid = i + gap;
            size_t end = i + 2*gap;
            if(mid > size)
              mid = size;
            if(end > size)
              end = size;
            _MergeArray(arr, beg, mid, end, tmp);
        }
    } // 第一重循环
}
////////////////////////////////////////////////
// 快速排序
// 时间复杂度: O(N * logN), 最坏情况:O(N^2)
// 空间复杂度: O(N)
// 不稳定
////////////////////////////////////////////////
// 交换法
int64_t partion_swap(int arr[], int64_t beg, int64_t end)
{
    if(end - beg <= 1)
      return beg;
    int64_t left = beg;
    int64_t right = end - 1;
    int key = arr[end - 1]; // 最后一个元素为基准值
    while(left < right)
    {
        // 从左往右找一个比 key 大的数
        while(left < right && arr[left] <= key)
          ++left;
        // 从右往左找一个比 key 小的数
        while(left < right && arr[right] >= key)
          --right;
        if(left < right)
          Swap(&arr[left], &arr[right]);
    }
    // 最后将 left 指向的位置和 key 交换
    Swap(&arr[left], &arr[end - 1]);
    return left;
}
// 挖坑法
int64_t partion_Trenching(int arr[], int64_t beg, int64_t end)
{
    if(end - beg <= 1)
      return beg;
    int64_t left = beg;
    int64_t right = end - 1;
    int key = arr[end - 1];
    while(left < right)
    {
        // 从左往右找一个比 key 大的数
        while(left < right && arr[left] <= key)
          ++left;
        if(left < right)
          arr[right--] = arr[left];
        // 从右往左找一个比 key 小的数
        while(left < right && arr[right] >= key)
          --right;
        if(left < right)
          arr[left++] = arr[right];
    }
    // 退出循环,还剩最后一个坑
    arr[left] = key;
    return left;
}
void _QuickSort(int arr[], int64_t beg, int64_t end)
{
    if(end - beg <= 1)
      return ;
    //int64_t mid = partion_swap(arr, beg, end);
    int64_t mid = partion_Trenching(arr, beg, end);
    _QuickSort(arr, beg, mid);
    _QuickSort(arr, mid+1, end);
}
void QuickSort(int arr[], size_t size)
{
    if(size <= 1)
      return ;
    int64_t beg = 0;
    int64_t end = size;
    _QuickSort(arr, beg, end);
}
////////////////////////////////
// 测试代码
////////////////////////////////
void TestBubbleSort()
{
    TEST_HEAD;
    int arr[] = {2, 0, 2, 1, 1, 0};
    int size = sizeof(arr)/sizeof(arr[0]);
    printf("[排序之前]\n");
    for(int i=0; i<size; i++)
    {
        printf("%d ", arr[i]);
    }
    printf("\n");
    BubbleSort(arr, size);
    printf("[排序之后]\n");
    for(int i=0; i<size; i++)
    {
        printf("%d ", arr[i]);
    }
    printf("\n");
}
void TestSelectSort()
{
    TEST_HEAD;
    int arr[] = {9, 2, 4, 7, 5, 8, 3, 1, 6};
    int size = sizeof(arr)/sizeof(arr[0]);
    printf("[排序之前]\n");
    for(int i=0; i<size; i++)
    {
        printf("%d ", arr[i]);
    }
    printf("\n");
    SelectSort(arr, size);
    printf("[排序之后]\n");
    for(int i=0; i<size; i++)
    {
        printf("%d ", arr[i]);
    }
    printf("\n");
}
void TestInsertSort()
{
    TEST_HEAD;
    int arr[] = {9, 5, 2, 7};
    int size = sizeof(arr)/sizeof(arr[0]);
    printf("[排序之前]\n");
    for(int i=0; i<size; i++)
    {
        printf("%d ", arr[i]);
    }
    printf("\n");
    InsertSort(arr, size);
    printf("[排序之后]\n");
    for(int i=0; i<size; i++)
    {
        printf("%d ", arr[i]);
    }
    printf("\n");
}
void TestHeapSort()
{
    TEST_HEAD;
    int arr[] = {9, 5, 2, 7};
    int size = sizeof(arr)/sizeof(arr[0]);
    printf("[排序之前]\n");
    for(int i=0; i<size; i++)
    {
        printf("%d ", arr[i]);
    }
    printf("\n");
    HeapSort(arr, size);
    printf("[排序之后]\n");
    for(int i=0; i<size; i++)
    {
        printf("%d ", arr[i]);
    }
    printf("\n");
}
void TestShellSort()
{
    TEST_HEAD;
    //int arr[] = {9, 5, 2, 7};
    int arr[] = {9, 2, 4, 7, 5, 8, 3, 1, 6};
    int size = sizeof(arr)/sizeof(arr[0]);
    printf("[排序之前]\n");
    for(int i=0; i<size; i++)
    {
        printf("%d ", arr[i]);
    }
    printf("\n");
    ShellSort(arr, size);
    printf("[排序之后]\n");
    for(int i=0; i<size; i++)
    {
        printf("%d ", arr[i]);
    }
    printf("\n");
}
void TestMergeSort()
{
    TEST_HEAD;
    //int arr[] = {9, 5, 2, 7};
    int arr[] = {9, 2, 4, 7, 5, 8, 3, 1, 6};
    int size = sizeof(arr)/sizeof(arr[0]);
    printf("[排序之前]\n");
    for(int i=0; i<size; i++)
    {
        printf("%d ", arr[i]);
    }
    printf("\n");
    //MergeSort(arr, size);
    MergeSortByLoop(arr, size);
    printf("[排序之后]\n");
    for(int i=0; i<size; i++)
    {
        printf("%d ", arr[i]);
    }
    printf("\n");
}
void TestQuickSort()
{
    TEST_HEAD;
    //int arr[] = {9, 5, 2, 7};
    int arr[] = {9, 2, 4, 7, 5, 8, 3, 1, 6};
    int size = sizeof(arr)/sizeof(arr[0]);
    printf("[排序之前]\n");
    for(int i=0; i<size; i++)
    {
        printf("%d ", arr[i]);
    }
    printf("\n");
    QuickSort(arr, size);
    printf("[排序之后]\n");
    for(int i=0; i<size; i++)
    {
        printf("%d ", arr[i]);
    }
    printf("\n");
}


int main()
{
    TestBubbleSort();
    TestSelectSort();
    TestInsertSort();
    TestHeapSort();
    TestShellSort();
    TestMergeSort();
    TestQuickSort();
    printf("\n");
    printf("\n");
    printf("\n");
    return 0;
}
