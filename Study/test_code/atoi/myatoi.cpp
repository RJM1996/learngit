
#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <ctype.h>

using namespace std;

//atoi (表示 ascii to integer)是把字符串转换成整型数的一个函数
//int atoi(const char *nptr) 函数会扫描参数 nptr字符串，跳过前面的空白字符（例如空格，tab缩进）
//可以通过isspace()函数来检测），直到遇上数字或正负符号才开始做转换
//而在遇到非数字或字符串结束符('\0')才结束转换，并将结果返回
//如果 nptr不能转换成 int 或者 nptr为空字符串，那么将返回 0 

int str2int(const char* str)
{
    assert(str);
    int symbol = 1;
    int ret = 0;
    const char* ptr = str;
    while(isspace(*ptr)) 
        ptr++;
    if(*ptr == '-')
    {
        symbol = -1;
        ptr++;
        if(*ptr > '9' || *ptr < '0')
            return 0;
    }
    if(*ptr == '+')
    {
        symbol = 1;
        ptr++;
        if(*ptr > '9' || *ptr < '0')
            return 0;
    }
    if(*ptr > '9' || *ptr < '0')
    {
        return 0;
    }
    while(*ptr != '\0' && *ptr > '0' && *ptr < '9')
    {
        ret = ret*10 + (*ptr - '0');
        ptr++;
    }
    ret *= symbol;
    return ret;
}
void TestStr2Int()
{
    const char* str = "123";
    const char* str1 = "-123";
    const char* str2 = "   -123ab45";
    
    cout << str2int(str) << endl;
    cout << str2int(str1) << endl;
    cout << str2int(str2) << endl;
}
void TestAtoI()
{
    const char* str = "2147483647";
    const char* str1 = "2147483648";
    const char* str2 = "2147483649";
    const char* str3 = "-2147483649";
    cout << atoi(str) << " : " << str2int(str) << endl;
    cout << atoi(str1) << " : " << str2int(str1) << endl;
    cout << atoi(str2) << " : " << str2int(str2) << endl;
    cout << atoi(str3) << " : " << str2int(str3) << endl;
}

int main()
{
    // TestStr2Int();
    TestAtoI();
    return 0;
}
