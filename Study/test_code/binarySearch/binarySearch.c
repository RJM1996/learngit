
#include <stdio.h>
#include <assert.h>
#include <string.h>

int binarySearch(int* arr, int size, int num)
{
    assert(arr);

    int left = 0;
    int right = size - 1;
    int mid = (left + right)/2;

    while(left <= right)
    {
        if(num == arr[mid])
        {
            return mid;
        }
        if(num > arr[mid])
        {
            left = mid + 1;
            mid = (left + right)/2;
        }
        if(num < arr[mid])
        {
            right = mid - 1;
            mid = (left + right)/2;
        }
    }
    return -1;
}

int main()
{
    int num = 5;
    int arr[] = {1,2,3,4,5,6,7};
    int size = sizeof(arr)/sizeof(arr[0]);
    int ret = binarySearch(arr, size, num);

    if(ret == -1)
      printf("没有这个元素\n");
    else
      printf("%d 的元素下标: %d\n", num, ret);

    return 0;
}
