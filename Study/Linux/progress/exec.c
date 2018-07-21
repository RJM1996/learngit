
#include<sys/types.h>
#include<stdio.h>
#include<unistd.h>
#include<stdlib.h>

int main()
{
    char* argv1[] = {"ls"};
    char* argv2[] = {"ls", "-la","/etc/passwd", 0 };
    int ret = execvp(*argv1, argv2);
    if(ret == -1)
    {
        perror("execvp");
        return -1;
    }
    return 0;
}
       
