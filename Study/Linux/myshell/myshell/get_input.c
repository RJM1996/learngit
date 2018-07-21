#include "myshell.h"

//获取用户输入
void get_input(char* buf)
{
    int len = 0;
    int ch;

    ch = getchar();
    while(len < 256 && ch != '\n')
    {
		//用getchar获取字符,以'\n'结束
        buf[len++] = ch;
        ch = getchar();
    }

    if(len == 256)
    {
		//输入的命令不能超过256个字符
        printf("command is too long\n");
        exit(-1);
    }
    buf[len] = '\n';
    len++;
    buf[len] = '\0';
}