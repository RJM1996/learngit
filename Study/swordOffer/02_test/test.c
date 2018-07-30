
#include<stdio.h>

// 不用加减乘除做加法

int a = 0;
int b = 0;
int c = 0;

int add(int x, int y)
{
    a = x;
    b = y;
    __asm__ __volatile__
        (
        "movl      a,    %eax\n\t"
        "addl      b,    %eax\n\t"
        "movl   %eax,    c"
        );
    return c;
}

int main()
{
    int ret = add(10, 20);
    printf("%d\n", ret);
    return 0;
}
