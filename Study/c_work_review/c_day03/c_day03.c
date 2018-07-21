/*================================================================

# File Name: c_day03.c
# Author: rjm
# mail: rjm96@foxmail.com
# Created Time: 2018年04月28日 星期六 07时40分56秒

================================================================*/

//1. 将数组A中的内容和数组B中的内容进行交换。（数组一样大） 
//2. 计算1/1-1/2+1/3-1/4+1/5 …… + 1/99 - 1/100 的值
//3. 编写程序数一下 1到 100 的所有整数中出现多少次数字9。 

#include <stdio.h>

#define TEST_HEAD printf("\n=====%s=====\n\n", __FUNCTION__)

void swapArray(int* arr1, int* arr2, int size)
{
    if(arr1 == NULL || arr2 == NULL)
      return ;
    for(int i=0; i<size; i++)
    {
        int tmp = arr1[i];
        arr1[i] = arr2[i];
        arr2[i] = tmp;
    }
}

double figureUp(double denominator) //denominator 表示最大的那个分母
{
    if(denominator == 0)
      //分母为0
      return 0;
    int symbol = 1;
    double result = 0;
    for(int i=1; i<=denominator; i++)
    {
        if(i%2 == 0)
          symbol = -1;
        else
          symbol = 1;
        result += (double)symbol*(1/(double)i);
    }
    return result;
}

int find_9_In_100(int num)
{
    int count = 0;
    int i = 0;
    for(i=1; i<=num; i++)
    {
        if((i-9)%10 == 0)
          count++;
        if(i/10 == 9)
          count++;
    }
    return count;
}

///////////////////////////////////
//测试代码
//////////////////////////////////

void Test_find_9_In_100()
{
    TEST_HEAD;
    printf("count = %d\n", find_9_In_100(100));
}
void Test_figureUp()
{
    TEST_HEAD;
    double result = figureUp(100);
    printf("result = %f\n", result);
}
void Test_swapArray()
{
    TEST_HEAD;
    int arr1[] = {1,3,5,7,9};
    int arr2[] = {2,4,6,8,10};
    int size = sizeof(arr1)/sizeof(arr1[0]);
    printf("=====交换前=====\n");
    for(int i=0; i<size; i++)
    {
        printf("[%d] ", arr1[i]);
    }
    printf("\n");
    for(int i=0; i<size; i++)
    {
        printf("[%d] ", arr2[i]);
    }
    swapArray(arr1, arr2, size);
    printf("\n=====交换后=====\n");
    for(int i=0; i<size; i++)
    {
        printf("[%d] ", arr1[i]);
    }
    printf("\n");
    for(int i=0; i<size; i++)
    {
        printf("[%d] ", arr2[i]);
    }
}

int main()
{
    Test_swapArray();
    Test_figureUp();
    Test_find_9_In_100();

    printf("\n\n\n");
    printf("\n\n\n");
    printf("\n\n\n");
    return 0;
}
