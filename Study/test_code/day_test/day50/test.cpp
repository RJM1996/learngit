#include <iostream>

using namespace std;

// 1. 求 n 的阶乘的末尾 0 的个数
// 先求出 n 的阶乘, 再算 % 10 的次数

long long fact(size_t n)
{
    long long sum = 1;
    for(size_t i=1; i<=n; i++)
    {
        sum *= i;
    }
    return sum;
}

int ZeroNum(size_t n)
{
    // long long num = fact(n); //先求出阶乘
    int count = 0;
    while(n)
    {
        n /= 5;
        count += n;
    }
    return count;
}

// 2. 进制转换
#include<stack>

void Base()
{
    int n = 0; // 待转换的数
    int r = 0; // 进制数
    stack<int> s; // 创建一个栈
    cin >> n >> r;
    while(n)
    {
        s.push(n % r); // 循环取余入栈
        n /= r;
    }
    while(!s.empty())
    {
        // 循环取栈顶 出栈
        switch(s.top())
        {
        case 10:
            cout << 'A';
            break;
        case 11:
            cout << 'B';
            break;
        case 12:
            cout << 'C';
            break;
        case 13:
            cout << 'D';
            break;
        case 14:
            cout << 'E';
            break;
        case 15:
            cout << 'F';
            break; //这些都是为了能转化为十六进制
        default:
            cout << s.top();
            break;
        }
        s.pop();
    }
}


int main1()
{
    // cout << fact(1000) << endl;
    // int n = 0;
    // while(cin >> n)
    // {
    //     cout << ZeroNum(n) << endl;
    // }
    while(1)
    {
        Base();
    }
}

char *itoa(int num, char *str, int radix)
{
    /*索引表*/
    char index[] = "0123456789ABCDEF";
    unsigned unum;/*中间变量*/
    int i = 0, j, k;
    /*确定unum的值*/
    if(radix == 10 && num < 0) /*十进制负数*/
    {
        unum = (unsigned) - num;
        str[i++] = '-';

    }
    else unum = (unsigned)num; /*其他情况*/
    /*转换*/
    do
    {
        str[i++] = index[unum % (unsigned)radix];
        unum /= radix;
    }
    while(unum);
    str[i] = '\0';
    /*逆序*/
    if(str[0] == '-')k = 1; /*十进制负数*/
    else k = 0;
    char temp;
    for(j = k; j <= (i - 1) / 2; j++)
    {
        temp = str[j];
        str[j] = str[i - 1 + k - j];
        str[i - 1 + k - j] = temp;
    }
    return str;
}

#include <stdlib.h>
#include <stdio.h>
int main(void)
{
    int number=0;
    int r = 0;
    // cin >> number >> r ;
    // char string[25];
    // cout << itoa(number,string,r) << endl;
    cout << ZeroNum(10) << endl;
}
