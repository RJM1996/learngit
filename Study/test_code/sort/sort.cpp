#include <iostream>
#include <stdio.h>
using namespace std;

// 排序

// 1. 快速排序
void QuickSort(int arr[], int left, int right)
{
    if(left > right)
        return ;
    int i, j, temp;
    temp = arr[left]; // temp 就是基准值
    i = left;
    j = right;
    while(i != j)
    {
        while(arr[j] >= temp && i < j)
            --j;
        while(arr[i] <= temp && i < j)
            ++i;
        if(i < j)
        {
            swap(arr[i], arr[j]);
        }
    }
    arr[left] = arr[i]; // 基准值归位到中间
    arr[i] = temp;

    QuickSort(arr, left, i-1);
    QuickSort(arr, i+1, right);
}

void TestQuickSort()
{
    int arr[] = {6, 1, 2, 7, 9, 3, 4, 5, 10, 8};
    size_t len = sizeof(arr)/sizeof(arr[0]);
    QuickSort(arr, 0, len-1);
    for(size_t i=0; i<len; i++)
    {
        printf("%d ", arr[i]);
    }
    printf("\n");
}

int main()
{
    TestQuickSort();
    return 0;
}
