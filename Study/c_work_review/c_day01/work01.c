/*================================================================

# File Name: c_day01.c
# Author: rjm
# mail: rjm96@foxmail.com
# Created Time: 2018年04月26日 星期四 08时55分41秒

================================================================*/


#include<stdio.h>

#define TEST_HEAD printf("\n=====%s=====\n", __FUNCTION__);

//打印素数
void printPrimeNum(int min, int max)
{
    TEST_HEAD;
    int i,j,count;

    if(min%2 == 0)
      min = min+1;

    if(max%2 != 0)
      max = max+1;

    for(i=min; i<max; i+=2)
    {
        count = 0;
        for(j=2; j<i; j++)
        {
            if(i%j == 0)
              count = 1;
        }
        if(count == 0)
          printf("%d ",i);
    }
    printf("\n");
}

//打印9*9乘法表
void printMulTable(int num)
{
    TEST_HEAD;
    for(int i = 1; i<=num; i++)
    {
        for(int j = 1; j<=i; j++)
        {
            printf("%d*%d = %2d ", i, j, i*j);
        }
        printf("\n");
    }
}

//打印1000~2000年的闰年
void printLeapYear(int min, int max)
{
    TEST_HEAD;
    int i = 0;
    for(int year = min; year < max; year++)
    {
        if((year % 4 == 0 && year % 100 != 0) || year % 400 == 0)
        {
            printf("[%d]", year);
            i++;
            if(i%10 == 0)
              printf("\n");
        }
    }
    printf("\n");
}

int main()
{
    printMulTable(9);
    printPrimeNum(100, 200);
    printLeapYear(1000, 2000);
    return 0;
}
