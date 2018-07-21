/*================================================================

# File Name: cutout.c
# Author: rjm
# mail: rjm96@foxmail.com
# Created Time: 2018年04月29日 星期日 03时10分32秒

================================================================*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#define ROW 100
#define COL 100

char* cutOut(char str[], const char* delim, char** catalog)
{
    char* result = NULL;
    //char *strtok(char s[], const char *delim);
    result = strtok( str, delim );
    char msg[ROW][COL];
    int i =0;
    for(i=0; result != NULL; i++)
    {
        strcpy(msg[i], result);
        //printf("msg[%d] = %s", i, msg[i]);
        //printf("\n");
        result = strtok( NULL, delim );
    }
    *catalog = msg[i-1];
    //printf("catalog = %s\n", *catalog);
    return *catalog;
}

//用法
void useAge()
{
    char* msg = (char *)malloc(100);
    //char *getcwd(char *buf, size_t size);
    //作用:把当前目录的绝对地址保存到 buf 中,buf 的大小为 size。
    //如果 size 太小无法保存该地址，返回 NULL 并设置 errno 为 ERANGE。
    //可以采取令 buf 为 NULL并使 size 为 0 来使 getcwd 调用 malloc 动态给 buf 分配
    //但是这种情况要特别注意使用后释放缓冲以防止内存泄漏。
    getcwd(msg, 100);
    printf("msg = %s\n", msg);
    char delim[] = "/";
    char* catalog;
    cutOut(msg, delim, &catalog);
    printf("catalog = %s\n", catalog);
    free(msg);
}

int main()
{
    useAge();
}
