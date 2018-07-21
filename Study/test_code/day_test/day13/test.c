/*================================================================

# File Name: test.c
# Author: rjm
# mail: rjm96@foxmail.com
# Created Time: 2018年06月07日 星期四 13时44分48秒

================================================================*/


// 剑指offer -- 66, 构建乘积数组

#include <stdio.h>

void one(int A[], int size)
{
    int B[size];
    int i = 0;
    for(i = 0; i < size; i++)
    {
        int temp = A[i];
        A[i] = 1;
        B[i] = 1;
        int j = 0;
        for(j = 0; j < size; j++)
        {
            //printf("A[%d] = %d\n", j, A[j]);
            B[i] = B[i] * A[j];
        }
        A[i] = temp;
        printf("B[%d] = %d\n", i, B[i]);
    }
}


void two(const int A[], int size)
{
    int B[size];
    int i;

    B[0] = 1;
    for(i=1; i<size; i++)
    {
        B[i] = B[i-1]*A[i-1];
    }

    int temp = 1;
    for(i=size-2; i>=0; i--)
    {
        temp *= A[i+1];
        B[i] *= temp;
    }

    for(i=0; i<size; i++)
    {
        printf("B[%d] = %d\n", i, B[i]);
    }
}

int main()
{
    int A[] = {4, 7, 2, 5, 9};
    int size = sizeof(A)/sizeof(A[0]);
    one(A, size);
    printf("===============================\n");
    two(A, size);
    return 0;
}
