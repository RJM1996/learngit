
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <strings.h>

// cgi 程序
// 计算器
void my_cal(char* arg)
{
    printf("hello, cgi !\n");
    int num1 = 0;
    int num2 = 0;
    // int sscanf(const char *str, const char *format, ...);
    sscanf(arg, "firstname=%d&lastname=%d", &num1, &num2);
    printf("%d + %d = %d\n", num1, num2, num1 + num2);
    printf("%d - %d = %d\n", num1, num2, num1 - num2);
    printf("%d * %d = %d\n", num1, num2, num1 * num2);
    if(num2 == 0)
    {
        printf("%d / %d = -1\n", num1, num2);
        printf("%d %% %d = -1\n", num1, num2);
        printf("The divisor cannot be 0 !\n");
    }
    else
    {
        printf("%d / %d = %d\n", num1, num2, num1 / num2);
        printf("%d %% %d = %d\n", num1, num2, num1 % num2);
    }
}

