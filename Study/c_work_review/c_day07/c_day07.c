/*================================================================

# File Name: c_day01.c
# Author: rjm
# mail: rjm96@foxmail.com
# Created Time: 2018年04月26日 星期四 08时55分41秒

================================================================*/


#include<stdio.h>
#include<assert.h>

void Swap();

#define TEST_HEAD printf("\n=====%s=====\n", __FUNCTION__);

//5, 判断素数
void JudgePrimeNum(int num)
{
    TEST_HEAD;
    if(num%2 == 0)
      printf("%d 不是素数\n", num);
    for(int i=1; i<num; i++)
    {
        if(num/i != 0)
        {
            printf("%d 是素数\n", num);
            return ;
        }
    }
}


//4. 
//创建一个数组， 
//实现函数init（）初始化数组、 
//实现empty（）清空数组、 
//实现reverse（）函数完成数组元素的逆置。 
//要求：自己设计函数的参数，返回值。 
void arrInit(int* arr, int size)
{
    assert(arr != NULL);
    for(int i=0; i<size; i++)
    {
        arr[i] = 0;
    }
}
void arrEmpty(int* arr, int size)
{
    if(arr == NULL)
      return ;
    for(int i=0; i<size; i++)
    {
        arr[i] = 0;
    }
}
void arrReverse(int* arr, int size)
{
    assert(arr != NULL);
    int left = 0;
    int right = size-1;
    while(left < right)
    {
        Swap(&arr[left], &arr[right]);
        left++;
        right--;
    }
}

//1. 打印乘法表
void printMulTable()
{
    TEST_HEAD;
    int num = 0;
    printf("请输入一个整数:");
    scanf("%d", &num);
    for(int i = 1; i<=num; i++)
    {
        for(int j = 1; j<=i; j++)
        {
            printf("%d*%d = %2d ", i, j, i*j);
        }
        printf("\n");
    }
}

//2, 交换两个数
void Swap(int* m, int* n)
{
    TEST_HEAD;
    //assert(m!=NULL && n!=NULL);
    int tmp = *m;
    *m = *n;
    *n = tmp;
}

//3, 判断闰年
void JudgeLeapYear(int year)
{
    TEST_HEAD;
    if((year % 4 == 0 && year % 100 != 0) || year % 400 == 0)
    {
        printf("[%d]年是闰年\n", year);
    }
    else
    {
        printf("[%d]年不是闰年\n", year);
    }
}

int main()
{
    printMulTable();
    JudgePrimeNum(3);
    JudgeLeapYear(1990);

    int m = 10;
    int n = 20;
    printf("交换前 %d %d\n", m , n);
    Swap(&m, &n);
    printf("交换后 %d %d\n", m , n);

    int arr[10] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 0};
    int size = sizeof(arr)/sizeof(arr[0]);
    for(int i=0; i<size; i++)
    {
        printf("%d ", arr[i]);
    }
    printf("\n");
    arrReverse(arr, size);
    for(int i=0; i<size; i++)
    {
        printf("%d ", arr[i]);
    }
    printf("\n");
    return 0;
}
