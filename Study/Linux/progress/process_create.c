
//封装fork/wait等操作, 编写函数 process_create(pid_t* pid, void* func, void* arg), func回调函数就是子进程执行的入口函数, arg是传递给func回调函数的参数.
#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>

int process_create(int(*func)(), const char* file, char* argv2[])
{
    int ret = 0;
    pid_t pid = fork();
    if(pid == 0)
    {
        //子进程
        ret = func(file, argv2);
        if(ret == -1)
        {
            printf("调用execvp失败\n");
            perror("func");
            _exit(-1);
        }

    }
    else
    {
        int st;
        pid_t ret = wait(&st);
        if(ret == -1)
        {
            perror("wait");
            exit(-1);
        }
    }
    return 0;
}

int main()
{
    char* argv1[] = {"ls"};
    char* argv2[] = {"ls","-al","/etc/passwd", 0};
    process_create(execvp, *argv1, argv2);
    return 0;
}
