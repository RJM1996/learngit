
#include<stdio.h>
#include<stdlib.h>

int glob = 100;
    
int main()
{
    pid_t id = vfork();
    if(id == -1)
    {
        perror("vfork");
    }
    
    if(id == 0)
    {
        //子进程
        glob = 200;
        printf("child's glob = %d\n", glob);
        exit(0);
    }
    else
    {
        printf("father's glob = %d\n", glob);
    }

    return 0;
}



