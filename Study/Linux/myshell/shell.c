#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <fcntl.h>


int main()
{
    while(1)
    {
        printf("[myshell]$ ");
        fflush(stdout);
        char buf[1024];
        ssize_t ret = read(0, buf, (sizeof(buf)) - 1);
        if(ret > 0)
        {
            buf[ret - 1] = 0;
        }

        char *_argv[32];
        char *start = buf;
        char *file = NULL;
        int pipe_flag = 0;// 管道标识符
        int  add_redirect_flag = 0; //追加重定向标识符
        int  redirect_flag = 0; //输出重定向标识符
        _argv[0] = buf;
        int i = 1;
        while(*start)
        {
            if(*start == ' ')
            {
                *start = 0;
                start++;

                ////管道实现：当检测到有管道符存在时将命令分为两个数组，管道符以前为一个数组，管道符以后为一个数组
                ////然后将管道符处赋值为NULL，开辟子进程，让子进程执行前边的命令，将执行结果写入/tmp/myshell文件中
                ////然后父进程等待子进程结束，父进程时打开/tmp/myshell文件
                ////将文件符复制为标准输入，然后执行后面命令。
                //if(*start == '|')
                //{
                //    char* pipe_ch = start;
                //    start++;
                //    pipe_flag = 1;
                //    if(*start == ' ')
                //    {
                //        *start = 0;
                //        start++;
                //    }
                //}

                if(*start == '>')
                {
                    start++;

                    if(*start == ' ')
                    {
                        *start = 0;
                        start++;
                    }

                    if(*start == '>')
                    {
                        add_redirect_flag = 1;//表示有一个追加重定向
                        start++;
                        if(*start == ' ')
                        {
                            *start = 0;
                            start++;
                        }
                    }
                    file = start;
                    redirect_flag = 1; //表示有一个输出重定向
                    break;
                }
                else
                {
                    _argv[i++] = start;
                }
            }
            else
            {
                start++;
            }
        }
        _argv[i] = NULL;
        pid_t id = fork();
        if(id == 0)
        {
            //子进程
            if(redirect_flag)
            {
                //有重定向, 关闭标准输出
                close(1);
                if(add_redirect_flag)// 追加重定向
                {
                    int ret = open(file, O_WRONLY | O_CREAT | O_APPEND, 0644);
                    execvp(_argv[0], _argv);
                    close(ret);
                }
                else
                {
                    //输出重定向
                    int ret = open(file, O_WRONLY | O_CREAT, 0644);
                    ftruncate(ret, 0); //此函数把ret标识的文件大小置为0, 即先清空文件, 再写入
                    execvp(_argv[0], _argv);
                    close(ret);
                }
            }
            else
            {
                execvp(_argv[0], _argv);
            }
        }

        else
        {
            pid_t ret = wait(NULL);
            if(ret < 0)
            {
                perror("wait");
                return -1;
            }

        }

        if(strcmp(buf, "exit") == 0)
        {
            break;
        }
    }
    return 0;
}
