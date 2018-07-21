/*================================================================

# File Name: 01_test.c
# Author: rjm
# mail: rjm96@foxmail.com
# Created Time: 2018年05月07日 星期一 11时37分41秒

================================================================*/

#include <stdio.h>
#include <math.h>
#include <string.h>

//判断一个数是不是回文数
int IsPalindromicNumber(int num)
{
    if(num < 10)
      return 1;

    int reverse = 0;
    int src = num;
    do
    {
        reverse = reverse*10 + num%10;
        num = num/10;
    }while(num > 0);

    if(reverse == src)
      return 1;
    else
      return 0;
}

//一个二叉树，如果每个节点与他的子节点距离是1，那么编程求出二叉树最远距离
//int BiTreeHeight(BiTree tree)
//{
//    if(tree == NULL)
//    {
//        //空树
//        return 0;
//    }
//    int left = BiTreeHeight(tree->lchild);
//    int  right = BiTreeHeight(tree->rchild);
//    return 1 + (left > right ? 
//                BiTreeHeight(tree->lchild) : BiTreeHeight(tree->rchild));
//}

// 给定一个整数,获得它的逆序数,如整数87231，逆序后为13278
int ReverseNum(int num)
{
    if(num < 10)
      return num;
    int count = 1;
    int reverse = 0;
    int tmp = num;
    while(tmp/10)
    {
        count++;
        tmp /= 10;
    }
    while(num > 0)
    {
        reverse = (num%10)*pow(10, count-1) + reverse;
        num = num/10;
        count--;
    }
    return reverse;
}

//计算费波那契数列F_n=F_{n-1}+F_{n-2}，用递归和不用递归两种方法
int Fibonacci(int n)
{
    if(n <= 0)
      return 0;
    if(n <= 2)
      return 1;
    return Fibonacci(n-1) + Fibonacci(n-2);
}
int FibonacciByLoop(int n)
{
    if(n <= 0)
      return 0;
    if(n <= 2)
      return 1;
    int i = 0;
    int first = 1;
    int second = 1;
    int next = 0;
    for(i=3; i<=n; i++)
    {
        next = first + second;
        first = second;
        second = next;
    }
    return next;
}

//一个母兔第四个年头生一个母兔，问第n年有多少母兔？（要求用递归）
int RabbitNum(int nYear)
{
    if(nYear < 4)
      return 1;
    if(nYear < 8)
      return 2;
    return 2*RabbitNum(nYear-4);
}

void reverse(char* start, char* end)
{
    if(start == NULL || end == NULL)
      return ;
    while(start < end)
    {
        char tmp = *start;
        *start = *end;
        *end = tmp;
        start++, end--;
    }
}
//将一个句子的单词反过来（单词原样），比如"i am cheating"变成"cheating am i"
char* ReverseString(char* str)
{
    if(str == NULL)
      return NULL;

    char* start = str;
    char* end = str + strlen(str) - 1;
    reverse(start, end);
//    while(start < end)
//    {
//        char tmp = *start;
//        *start = *end;
//        *end = tmp;
//        start++, end--;
//    }
    //此时整个字符串已经逆置
    //再将单个单词逆置
    start = str;
    end = start;
    while(*start != '\0')
    {
        if(*start == ' ')
        {
            start++, end++;
            continue;
        }
        if(*end == ' ' || *end == '\0')
        {
            reverse(start, --end);
            start = ++end;
        }
        else
        {
            end++;
        }
    }
    return str;
}

int main()
{
    int num = 123454321;
    if(IsPalindromicNumber(num))
      printf("%d 是回文数\n", num);
    else
      printf("%d 不是回文数\n", num);

    printf("ReverseNum = %d\n", ReverseNum(87231));
    printf("ReverseNum = %d\n", ReverseNum(10000));
    printf("ReverseNum = %d\n", ReverseNum(1100));
    printf("ReverseNum = %d\n", ReverseNum(0));

    //1、1、2、3、5、8、13、21、34
    printf("\n===========递归求斐波那契==============\n");
    printf("fibo = %d\n", Fibonacci(3));
    printf("fibo = %d\n", Fibonacci(4));
    printf("fibo = %d\n", Fibonacci(5));
    printf("fibo = %d\n", Fibonacci(6));

    printf("\n===========非递归求斐波那契==============\n");
    printf("fibo = %d\n", FibonacciByLoop(3));
    printf("fibo = %d\n", FibonacciByLoop(4));
    printf("fibo = %d\n", FibonacciByLoop(5));
    printf("fibo = %d\n", FibonacciByLoop(6));

    printf("RabbitNum = %d\n", RabbitNum(1));
    printf("RabbitNum = %d\n", RabbitNum(4));
    printf("RabbitNum = %d\n", RabbitNum(8));
    printf("RabbitNum = %d\n", RabbitNum(12));
    printf("RabbitNum = %d\n", RabbitNum(16));

    char str[] = "i am student";
    printf("\n%s\n", ReverseString(str));

    return 0;
}
