#include <stdio.h>
#include <signal.h>
#include <unistd.h>
#include <stdlib.h>
#include <fcntl.h>
#include <sys/stat.h>

void mydaemon(void)
{
    int i;
    int fd0;
    pid_t pid;
    struct sigaction sa;
    umask(0); //1. ����umask���ļ�ģʽ��������������Ϊ0.

    //2. ����fork, �������˳���exit), ��֤�ӽ��̲���һ����������鳤���̡�
    //	 ������ػ���������Ϊһ���򵥵�shell����������
    //	 ��ô��������ֹʹ��shell��Ϊ�������Ѿ�ִ�����

    if( (pid = fork()) < 0 )
    {
        perror("fork");
    }
    else if (pid > 0)
    {
        exit(0);
        //��ֹ������
    }
    setsid(); //3. ����setsid����һ���»Ự
    sa.sa_handler = SIG_IGN;//4. ����SIGCHLD�ź�
    sigemptyset(&sa.sa_mask);
    sa.sa_flags = 0;
    if( sigaction(SIGCHLD, &sa, NULL ) < 0 )  // ע���ӽ����˳������ź�
    {
        return;
    }



    //ע�⣡�ٴ�fork����ֹ�����̣������ӽ��̲��ǻ��׽��̣��Ӷ���֤���������ٺ������ն˹�����
    //�ⲿ�ֲ��Ǳ����
    if( (pid = fork() ) < 0)
    {
        printf("fork error!\n");
        return;
    }
    else if( pid != 0)
    {
        exit(0);
    }
    //5.����ǰ����Ŀ¼����Ϊ��Ŀ¼��
    if( chdir("/") < 0 )
        printf("child dir error\n");
    return;

    //�رղ���Ҫ���ļ�������,�����ض��� /dev/null
    close(0);
    fd0 = open("/dev/null", O_RDWR);
    dup2(fd0, 1);
    dup2(fd0, 2);
}

int main()
{
    mydaemon();
    while(1)
    {
        sleep(1);
    }
}
