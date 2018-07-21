/*================================================================

# File Name: test.c
# Author: rjm
# mail: rjm96@foxmail.com
# Created Time: 2018年05月31日 星期四 21时29分30秒

================================================================*/



#include <stdio.h>

//在数组中的两个数字，如果前面一个数字大于后面的数字，则这两个数字组成一个逆序对。
//输入一个数组,求出这个数组中的逆序对的总数P。
//并将P对1000000007取模的结果输出。即输出P%1000000007
int main()
{
    int arr[] = {1, 2, 3, 4, 5, 7, 0};
    // 对每个数字找他后面有几个小于他的数
    int size = sizeof(arr)/sizeof(arr[0]);
    int i = 0;
    int count = 0;
    for(; i<size; i++)
    {
        int j = i+1;
        printf("i = %d, j = %d\n", i, j);
        if(j >= size)
          break;
        for(; j<size-i; j++)
        {
            if(arr[j] < arr[i])
              count++;
        }
    }
    printf("== %d\n" , count % 1000000007);
    return 0;
}
