
#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <unistd.h>
#include<sys/types.h>
#include<sys/wait.h>



void handler(int sig)
{
    pid_t id;
    while( (id = waitpid(-1, NULL, WNOHANG)) > 0 )
    {
        printf("wait child success: %d\n", id);
    }
    printf("child is quit! %d\n", getpid());

}
int main()
{
    signal(SIGCHLD, handler);
    pid_t cid;
    if((cid = fork()) == 0)
    {
        //child
        printf("child : %d\n", getpid());
        sleep(3);
        exit(1);
    }
    while(1)
    {
        printf("father proc is doing some thing!\n");
        sleep(1);
    }
    return 0;
}

//////////////////////////////
//实现mysleep
//////////////////////////////

//void sig_alrm(int signo)
//{
//    ;//do nothing
//}
//
//unsigned int mysleep(unsigned int nsecs)
//{
//    struct sigaction new, old;//定义两个sigaction结构体
//    unsigned int unslept = 0;
//    sigset_t newmask, oldmask, suspmask;
//
//    new.sa_handler = sig_alrm;//信号处理函数为 sig_alrm
//    sigemptyset(&new.sa_mask);//sa_mask 为 sigset_t 类型, 所以要这样初始化
//    new.sa_flags = 0;
//    sigaction(SIGALRM, &new, &old);//注册信号处理函数
//
//    sigemptyset(&newmask);
//    sigaddset(&newmask, SIGALRM);
//    sigprocmask(SIG_BLOCK, &newmask, &oldmask);
//
//    alarm(nsecs);//设置闹钟
//
//    suspmask = oldmask;
//    sigdelset(&suspmask, SIGALRM);
//    sigsuspend(&suspmask);
//
//    unslept = alarm(0);//清空闹钟
//    sigaction(SIGALRM, &old, NULL);//恢复默认处理动作
//
//    sigprocmask(SIG_SETMASK, &oldmask, NULL);
//    return unslept; 
//}
//
//int main()
//{
//    while(1)
//    {
//        mysleep(2);
//        printf("sleep 2 s\n");
//    }
//    return 0;
//}
//
/////////////////////////////////////////
//测试pending
/////////////////////////////////////////
//void print_sigset(sigset_t* set)
//{
//    for(int i=1; i<=31; i++)
//    {
//        if(i%8 == 0)
//          printf("  ");
//        //int sigismember(const sigset_t *set,int signum);
//        //如果信号集里已有signum信号则返回1，否则返回0。如果有错误则返回-1
//        if(sigismember(set, i) == 1)
//        {
//            putchar('1');
//        }
//        else
//        {
//            putchar('0');
//        }
//    }
//    puts(" ");
//}
//
//int main()
//{
//    //定义信号集对象, 清空并初始化
//    sigset_t s, p;
//    //sigemptyset()用来将参数set信号集初始化并清空。
//    sigemptyset(&s);
//    //sigaddset()用来将参数signum 代表的信号加入至参数set 信号集里。
//    sigaddset(&s, SIGINT);//将2号信号SIGINT加入s信号集
//    //int sigprocmask(int how, const sigset_t *restrict set, sigset_t *restrict oldset);
//    //用来检测或改变目前的信号屏蔽字，其操作依参数how来决定
//    //参数how的取值不同，带来的操作行为也不同，该参数可选值如下：
//    //1．SIG_BLOCK:该值代表的功能是将newset所指向的信号集中所包含的信号加到当前的信号掩码中，作为新的信号屏蔽字。
//    //2．SIG_UNBLOCK:将参数newset所指向的信号集中的信号从当前的信号掩码中移除。
//    //3．SIG_SETMASK:设置当前信号掩码为参数newset所指向的信号集中所包含的信号。
//    sigprocmask(SIG_BLOCK, &s, NULL); //设置阻塞信号集, 阻塞s里的SIGINT信号
//
//    while(1)
//    {
//        //sigpending函数返回在送往进程的时候被阻塞挂起的信号集合。这个信号集合通过参数set返回
//        sigpending(&p); //获取未决信号集
//        print_sigset(&p);
//        sleep(1);
//    }
//    return 0;
//}
//

/////////////////////////////////////////
//测试闹钟函数
/////////////////////////////////////////
//int main()
//{
//    int count = 0;
//    size_t ret = alarm(1);
//    while(1)
//    {
//        count++;
//        printf("count = %d\n", count);
//        printf("ret = %d\n", ret);
//    }
//    return 0;
//}
