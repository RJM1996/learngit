/*************************************************************************
# File Name: multiProcess.c
# Author: rjm
# mail: rjm96@foxmail.com
# Created Time: 2018年04月21日 星期六 10时45分41秒
 ************************************************************************/

#include<stdio.h>
#include<unistd.h>
#include<sys/wait.h>
#include<sys/types.h>


int main()
{
    pid_t id = fork();
    if(id < 0)
    {
        perror("fork");
        return -1;
    }
    if(id == 0)
    {
        printf("i am child: %d, my father is: %d \n", getpid(), getppid());
    }
    else
    {
        printf("i am father: %d\n", getpid());
    }

    return 0;
}
