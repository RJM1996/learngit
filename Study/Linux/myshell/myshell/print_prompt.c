

#include "myshell.h"

char* cutOut(char str[], const char* delim, char** catalog)
{
    char* result = NULL;
    //char *strtok(char s[], const char *delim);
    result = strtok( str, delim );
    char msg[100][30] = {};
    int i =0;
    for(i=0; result != NULL; i++)
    {
        strcpy(msg[i], result);
        //printf("%s", msg[i]);
        //printf("\n");
        result = strtok( NULL, delim );
    }
    *catalog = msg[i-1];
    return *catalog;
}

void print_prompt()
{
    msg = (char *)malloc(100);
    //char *getcwd(char *buf, size_t size);
    //作用:把当前目录的绝对地址保存到 buf 中,buf 的大小为 size。
    //如果 size 太小无法保存该地址，返回 NULL 并设置 errno 为 ERANGE。
    //可以采取令 buf 为 NULL并使 size 为 0 来使 getcwd 调用 malloc 动态给 buf 分配
    //但是这种情况要特别注意使用后释放缓冲以防止内存泄漏。
    getcwd(msg, 100);
    char delim[] = "/";
    char* catalog;
    cutOut(msg, delim, &catalog);
    printf("[rjm_clone@localhost %s]$ ", catalog);
    free(msg);
}
