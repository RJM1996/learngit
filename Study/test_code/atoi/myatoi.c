/*================================================================
  Copyright (C) 2018 Sangfor Ltd. All rights reserved.
# File Name: myatoi.c
# Author: rjm
# mail: rjm96@foxmail.com
# Created Time: 2018年04月23日 星期一 14时05分32秒

================================================================*/


#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <ctype.h>

//atoi (表示 ascii to integer)是把字符串转换成整型数的一个函数
//int atoi(const char *nptr) 函数会扫描参数 nptr字符串，跳过前面的空白字符（例如空格，tab缩进）
//可以通过isspace()函数来检测），直到遇上数字或正负符号才开始做转换
//而在遇到非数字或字符串结束符('\0')才结束转换，并将结果返回
//如果 nptr不能转换成 int 或者 nptr为空字符串，那么将返回 0 

int atoi(const char *nptr);

long long myatoi(const char* str)
{
    assert(str);
    int symbol = 1;//设置正负号
    long long ret = 0;//存放结果
    const char* p_str = str;

    //判断是否为空字符
    if(*p_str == '\0')
      return 0;

    //去掉前面的空格
    while(isspace(*p_str))
      p_str++;

    //判断符号
    if(*p_str == '-')
    {
        symbol = -1;
        p_str++;
        if(*p_str > '9' || *p_str < '0')
        {
            return 0;
        }
    }
    else if(*p_str == '+')
    {
        p_str++;
        if(*p_str > '9' || *p_str < '0')
        {
            return 0;
        }
    }
    else if(*p_str > '9' || *p_str < '0')
    {
        return 0;
    }

    //遇到 非数字或者'\0', 结束转换
    while(*p_str != '\0' && *p_str < '9' && *p_str > '0')
    {
        ret = ret*10 + *p_str - '0';
        p_str++;
    }

    ret  = ret*symbol;

    //判断溢出
    if (((ret > 0x7FFFFFFFFFFFFFFF) && (symbol == 1)) ||  
                ((ret < (signed int)0x8000000000000000) && (symbol == -1)))  
    {  
        return 0;  
    }  

    return ret;
}

//int main()
//{
//    printf("value = %lld\n", myatoi("12345"));
//    printf("value = %lld\n", myatoi("abc123"));
//    printf("value = %lld\n", myatoi("-123"));
//    printf("value = %lld\n", myatoi("12b45"));
//    printf("value = %lld\n", myatoi("123456789"));//数字太大 溢出
//    printf("value = %lld\n", myatoi("-922337203685477580"));//数字太大 溢出
//    return 0;
//}


int main()
{
    char str[10];
    gets(str);
    printf("%llu\n", myatoi(str));
    return 0;
}
