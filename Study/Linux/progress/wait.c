
#include<stdio.h>
#include<stdlib.h>

int main()
{
    pid_t id = fork();
    if(id == -1)
    {
        perror("fork");
    }
   
    if(id == 0)
    {
        sleep(20);
        exit(10);
    }
    else
    {
        int status;
        int ret = wait(&status);
        if(ret > 0 && (status & 0x7f) == 0)
        {
            printf("child exit code: %d\n", (status>>8) & 0xff);
        }
        else if(ret > 0)
        {
            printf("sig code: %d\n", status&0x7f);
        }

    }

}


