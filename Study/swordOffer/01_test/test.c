/*================================================================

# File Name: test.c
# Author: rjm
# mail: rjm96@foxmail.com
# Created Time: 2018年04月26日 星期四 16时04分37秒

================================================================*/



#include <stdio.h>

int getSize(int* data)
{
    return sizeof(data);
}

// 1. 在杨氏矩阵中查找一个数
// 从右上角那个数开始找, 如果小于num
// 第一行就不可能有 num 了
// 于是除去第一行,继续从右上角找
int findNumInYangTableau(int **arr, int num)
{
    int rows = sizeof(arr) / sizeof(arr[0]);
    int cols = sizeof(arr[0]) / sizeof(arr[0][0]);
    if( rows > 0 && cols > 0)
    {

        int row = 0;
        int col = cols - 1;
        while(row < rows && col > 0)
        {
            if(num == arr[row*cols][col])
            {
                printf("num = (%d, %d)\n", row, col);
                return 1;
            }
            if(num > arr[row*cols][col])
            {
                ++row;
            }
            else
            {
                --col;
            }
        }
    }
    return 0;
}

void subfun(int n, char **subargs)  
{  
    int i;   
    for (i = 0; i < n; i++) 
    {  
        printf("subargs[%d] = %s\n", i, subargs[i]);  
    }  
}  

int main()
{
    int arr[3][3] = {
        {1, 2, 3},
        {2, 3, 4},
        {3, 4, 5},
    };

    //int row = sizeof(arr) / sizeof(arr[0]);
    //int col = sizeof(arr[0]) / sizeof(arr[0][0]);
    //printf("row = %d\ncol = %d\n", row, col);

    int array[][3] = {
        {1, 3, 5},
        {5, 6, 9},
        {7, 9, 10},
    };

    //char* arg[] = {
    //    "abc",
    //    "cde",
    //    "efg",
    //};

    //char* b[3];
    //b[0] = arg[0];
    //b[1] = arg[1];
    //b[2] = arg[2];

    //subfun(3, arg);
    //subfun(3, b);

    //int* a[3];
    //a[0] = array[0];
    //a[1] = array[1];
    //a[2] = array[2];

    //int ret1 = findNumInYangTableau(arr, 3, 3, 4);

    int ret2 = findNumInYangTableau((int**)array, 4);
    //int ret3 = findNumInYangTableau((int*)array, 3, 3, 0);
    //int ret4 = findNumInYangTableau((int*)array, 3, 3, 11);
    //int ret5 = findNumInYangTableau((int*)array, 3, 3, 5);
    //int ret6 = findNumInYangTableau(NULL, 3, 3, 5);

    printf("ret2 expected 0, actual %d\n", ret2);
    //printf("ret3 expected 1, actual %d\n", ret3);
    //printf("ret4 expected 1, actual %d\n", ret4);
    //printf("ret5 expected 1, actual %d\n", ret5);
    //printf("ret6 expected 1, actual %d\n", ret6);

    //int data1[] = {1, 2, 3, 4, 5};
    //int size1 = sizeof(data1);

    //int* data2 = data1;
    //int size2 = sizeof(data2);

    //int size3 = getSize(data1);

    //printf("%d %d %d \n", size1, size2, size3);
}
