/*================================================================

# File Name: c_day05.c
# Author: rjm
# mail: rjm96@foxmail.com
# Created Time: 2018年04月28日 星期六 14时06分34秒

================================================================*/



#include <stdio.h>
#include <stdlib.h>
#include <time.h>

//1.完成猜数字游戏。 
void guessNumber()
{
    srand((int)time(0));
    int randnum = rand()%100;
    while(1)
    {
        printf("\n====请猜一个数字====\n");
        int num = 0;
        scanf("%d", &num);
        if(num > randnum)
          printf("猜大了\n");
        if(num < randnum)
          printf("猜小了\n");
        if(num == randnum)
        {
            printf("恭喜你! 猜对了!\n");
            break;
        }
    }
}
//
//2.写代码可以在整型有序数组中查找想要的数字，找到了返回下标，找不到返回-1.（折半查找） 
int binaryFind(int* arr, int size, int num)
{
    if(arr == NULL)
      return -1;
    if(size == 0)
      return -1;
    int left = 0;
    int right = size-1;
    int mid = left/2 + right/2;
    for(int i=0; i<size; i++)
    {
        if(num == arr[mid])
          return mid;
        if(num > arr[mid])
        {
            left = mid+1;
            mid = left/2 + right/2;
        }
        if(num < arr[mid])
        {
            right = mid+1;
            mid = left/2 + right/2;
        }
    }
    return -1;
}

void Test_binaryFind()
{
    int arr[] = {1, 3, 5, 7, 9, 13, 15, 18, 32};
    int size = sizeof(arr)/sizeof(arr[0]);
    int index = binaryFind(arr, size, 7);
    printf("expected 3, autual %d\n", index);
}
//
//3.编写代码模拟三次密码输入的场景。 
//最多能输入三次密码，密码正确，提示“登录成功”,密码错误，可以重新输入，最多输入三次。三次均错，则提示退出程序。 
void enterPassword()
{
    int correct = 123456;
    int passwd = 0;
    int i = 3;
    int count = 0;
    while(1)
    {
        printf("\n请输入密码:");
        scanf("%d", &passwd);
        if(passwd == correct)
        {
            printf("登录成功!\n");
            break;
        }
        else
        {
            count++;
            if(count == 3)
            {
                printf("\n连续3次输入错误,您的密码已被锁定!\n");
                break;
            }
            printf("输入错误,请重新输入!\n");
        }
    }
}
//
//4.编写一个程序，可以一直接收键盘字符，如果是小写字符就输出对应的大写字符
//如果接收的是大写字符，就输出对应的小写字符，如果是数字不输出。
void toggleCase()
{
    char ch;
    while(ch != EOF)
    {
        ch = getchar();
        if(ch > 'a' && ch < 'z')
        {
            putchar(ch-32);
        }
        if(ch > 'A' && ch < 'Z')
        {
            putchar(ch+32);
        }
    }
}


int main()
{
    //guessNumber();
    //Test_binaryFind();
    //enterPassword();
    toggleCase();

    printf("\n\n\n");
    printf("\n\n\n");
    printf("\n\n\n");
    return 0;
}

