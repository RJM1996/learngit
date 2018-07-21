/*================================================================

# File Name: test.c
# Author: rjm
# mail: rjm96@foxmail.com
# Created Time: 2018年04月26日 星期四 11时07分23秒

================================================================*/



#include <stdio.h>

#define TEST_HEAD printf("\n=====%s=====\n", __FUNCTION__);

//交换两个整型变量的值
void swap_withTmp(int* a, int* b)
{
    //TEST_HEAD;
    int tmp = *a;
    *a = *b;
    *b = tmp;
}

void swap_NoTmp(int *a, int *b)
{
    TEST_HEAD;
    *a = *a + *b;
    *b = *a - *b;
    *a = *a - *b;
}

//求10个整数中的最大值
int findMax(int* arr, int size)
{
    TEST_HEAD;
    int max = 0;
    for(int i = 0; i < size; i++)
    {
        if(arr[i] > max)
        {
            max = arr[i];
        }
    }
    return max;
}

//将三个数从大到小输出
void descPrint(int* arr, int size)
{
    for(int i=0; i<size; i++)
    {
        for(int j=0; j < size-i-1; j++)
        {
            if(arr[j] < arr[j+1])
              swap_withTmp(&arr[j], &arr[j+1]);
        }
    }
}

//求两个数的最大公约数, 最小公倍数
void gcd_lcm(int* gcd, int* lcm, int m, int n) 
{
    TEST_HEAD;
    int r = m%n;
    int product = m*n;
    while(r != 0)
    {
        r = m%n;
        m = n;
        n = r;
    }
    *gcd = m;
    *lcm = product / *gcd;
}

int main()
{
    int m = 10;
    int n = 20;
    int arr[10] = {1, 2, 4, 7, 12, 36, 98, 20, 29, 67};
    int size = sizeof(arr)/sizeof(arr[0]);
    //printf("size = %d\n",size);

    printf("m = %d n = %d\n", m, n);
    swap_withTmp(&m, &n);
    printf("m = %d n = %d\n", m, n);
    swap_NoTmp(&m, &n);
    printf("m = %d n = %d\n", m, n);

    int max = findMax(arr, size);
    printf("max = %d\n", max);

    printf("\n");

    descPrint(arr, size);
    for(int i=0; i<size; i++)
    {
        printf("%d ", arr[i]);
    }
    printf("\n");
    printf("\n");

    int gcd = 0;
    int lcm = 0;
    gcd_lcm(&gcd, &lcm, 70, 80);
    printf("gcd = %d lcm = %d\n", gcd, lcm);

    printf("\n");
    return 0;
}
