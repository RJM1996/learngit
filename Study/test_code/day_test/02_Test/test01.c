#include "test.h"

// 1. 静态全局变量
static const char* hello = "hello";
// const char* hello = "hello";


void printStr()
{
    printf("%s\n", hello);
}

void test()
{
    int count = 0;
    // 2. 静态局部变量
    static int s_count;
    printf("count = %d, s_count = %d\n", count, s_count);
    count++;
    s_count++;
}

// 3. 静态函数
static void func01()
{
    printf("static func01");
}

void func02()
{
    printf("func02");
}

