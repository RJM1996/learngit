/*================================================================

# File Name: c_day04.c
# Author: rjm
# mail: rjm96@foxmail.com
# Created Time: 2018年04月28日 星期六 08时41分29秒

================================================================*/



#include <stdio.h>
#include <stdlib.h>
#include <math.h>

//1.在屏幕上输出以下图案： 
//* 
//*** 
//***** 
//******* 
//********* 
//*********** 
//************* 
//*********** 
//********* 
//******* 
//***** 
//*** 
//* 
void printTriangle(int max)
{
    for(int i=1; i<=max; i+=2)
    {
        for(int j=1; j<=i; j++)
        {
            printf("*");
        }
        printf("\n");
    }
    for(int i=max-2; i>=1; i-=2)
    {
        for(int j=1; j<=i; j++)
        {
            printf("*");
        }
        printf("\n");
    }
}

//2.求出0～999之间的所有“水仙花数”并输出
void printNarcissisticNumber(int max)
{
    for(int i=0; i<=max; i++)
    {
        int hundreds = i/100;
        int decade =( i - 100*hundreds )/10;
        int unit = i-hundreds*100-decade*10;
        if((unit*unit*unit + decade*decade*decade + hundreds*hundreds*hundreds) == i)
        {
            printf("[%d] ", i);
        }
    }
}
//3.求Sn=a+aa+aaa+aaaa+aaaaa的前5项之和，其中a是一个数字，例如：2+22+222+2222+22222 
double Sum(double num, double n)
{
    double Sn = 0;
    for(double i=1; i<=n; i++)
    {
        for(double j=1; j<=i; j++)
        {
            Sn += num*pow(10, j-1);
        }
    }
    return Sn;
}

//4.编写一个程序，它从标准输入读取C源代码，并验证所有的花括号都正确的成对出现。 
void Pairing()
{
    int flag = 0;
    printf("请输入c源代码=>\n");
    char code;
    while(code != EOF)
    {
        code = getchar();
        if(code == '{')
          flag++;
        if(code == '}' && flag == 0)
        {
            printf("\n不匹配\n");
            return ;
        }
        if(code == '}' && flag != 0)
        {
            flag--;
        }
    }
    if(flag == 0)
      printf("\n匹配\n");
    else
      printf("\n不匹配\n");
}
int main()
{
    printTriangle(13);
    printNarcissisticNumber(999);
    printf("\nSn = %f\n", Sum(2, 5));
    Pairing();

    printf("\n\n\n");
    printf("\n\n\n");
    printf("\n\n\n");
    return 0;
}
