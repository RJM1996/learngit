#include "myshell.h"

void do_cmd(int argcount, char (*arglist)[256])
{
    int flag = 0;
    int how = 0;    //用于标识命令中是否含有输出重定向> ,输入重定向< , 管道 |
    int background = 0;    //标识命令中是否有后台运行的标示符
    int status;
    int i;
    int fd;
    char* arg[argcount + 1];
    char* argnext[argcount + 1];
    char* file;
    pid_t pid;

    //将命令取出
    for(i = 0; i < argcount; i++)
    {
        arg[i] = (char *)arglist[i];
    }
    arg[argcount] = NULL;

    //查看命令行是否有后台运行符
    for(i = 0; i < argcount; i++)
    {
        if(strncmp(arg[i], "&", 1) == 0)
        {
            if(i == argcount - 1)
            {
                background = 1;
                arg[argcount - 1] = NULL;
                break;
            }
            else
            {
                printf("wrong command\n");
                return ;
            }
        }
    }

	//检查是否有输出重定向符>, 输入重定向符<, 管道符 |
    for(i = 0; arg[i] != NULL; i++)
    {
        if(strcmp(arg[i], ">") == 0)
        {
            flag++;
            how = out_readirect;
                if(arg[i + 1] == NULL)
                {
                    flag++;
                }
        }

        if(strcmp(arg[i], ">>") == 0)
        {
            flag++;
            how = out_add_readirect;
                if(arg[i + 1] == NULL)
                {
                    flag++;
                }
        }

        if(strcmp(arg[i], "<") == 0)
        {
            flag++;
            how = in_readdirect;
            if(i == 0)
            {
                flag++;
            }
        }

        if(strcmp(arg[i], "|") == 0)
        {
            flag++;
            how = have_pipe;
            if(arg[i + 1] == NULL)
            {
                flag++;
            }
            if(i == 0)
            {
                flag++;
            }
        }
    }

	
    //flag大于1,说明命令中含有多个> < |符号，本程序不支持这样的命令，或者命令格式不对
    if(flag > 1)
    {
        printf("sorry, this command is not supported\n");
        return ;
    }

    if(how == out_readirect)
    {
        //命令只含有一个输出重定向符号
        for(i = 0; arg[i] != NULL; i++)
        {
            if(strcmp(arg[i], ">") == 0)
            {
                file = arg[i + 1];
                arg[i] = NULL;
            }
        }
    }

    if(how == out_add_readirect)
    {
        //命令含有输出追加重定向符号
        for(i = 0; arg[i] != NULL; i++)
        {
            if(strcmp(arg[i], ">>") == 0)
            {
                    file = arg[i + 1];
                    arg[i] = NULL;
            }
        }
    }

    if(how == in_readdirect)
    {
        //命令只含有一个输入重定向
        for(i = 0; arg[i] != NULL; i++)
        {
            if(strcmp(arg[i], "<") == 0)
            {
                file = arg[i + 1];
                arg[i] = NULL;
            }
        }
    }

    if(how == have_pipe)
    {
        //命令只有一个管道符号，把管道符后面的部分存入argnext中，管道后面的部分是一个可执行的shell命令
        for(i = 0; arg[i] != NULL; i++)
        {
            if(strcmp(arg[i], "|") == 0)
            {
                arg[i] = NULL;
                int j;
				//把管道符后面的部分存入argnext中
                for(j = i + 1; arg[j] != NULL; j++)
                {
                    argnext[j - i - 1] = arg[j];
                }
                argnext[j - i - 1] = arg[j];
                break;
            }
        }
    }

	//处理cd命令
    if((arg[0] != NULL) && (strcmp(arg[0], "cd") == 0))
    {
        if(arg[1] == NULL)
        {
            return ;
        }
        if(strcmp(arg[1], "~") == 0)
        {
			// "~" 替换为家目录
            strcpy(arg[1], "/home/rjm/");
        }
		//int chdir(const char *path);
		//改变当前工作目录
        if(chdir(arg[1]) ==  -1)
        {
            perror("cd");
        }
        return ;
    }

    if((pid = fork()) < 0)
    {
        printf("fork error\n");
        return ;
    }

    switch(how)
    {
    case 0:
        //pid为0说明是子进程，在子进程中执行输入的命令
        //输入的命令中不含> < |
        if(pid == 0)
        {
            if(!(find_exeProgram_In_command(arg[0])))
            {
                printf("%s : command not found\n", arg[0]);
                exit(0);
            }
			//调用execvp执行命令
            execvp(arg[0], arg);
            exit(0);
        }
        break;

    case 1:
        //输入的命令中含有输出重定向符>
        if(pid == 0)
        {
            if( !(find_exeProgram_In_command(arg[0])) )
            {
                printf("%s : command not found\n", arg[0]);
                exit(0);
            }
            fd = open(file, O_RDWR | O_CREAT | O_TRUNC, 0644);
			//功能： 复制文件描述符
			//用法： int dup2(int oldfd,int newfd);
			//就是把标准输入获得的内容写到了fd指向的file文件里
            dup2(fd, 1);
            execvp(arg[0], arg);
            exit(0);
        }
        break;

    case 2:
        //输入的命令中含有输入重定向<
        if(pid == 0)
        {
            if( !(find_exeProgram_In_command (arg[0])) )
            {
                printf("%s : command not found\n", arg[0]);
                exit(0);
            }
            fd = open(file, O_RDONLY);
            dup2(fd, 0);
            execvp(arg[0], arg);
            exit(0);
        }
        break;

    case 3:
        //输入的命令中含有管道符|
        if(pid == 0)
        {
            int pid2;
            int status2;
            int fd2;
			
			//子进程再fork, 再创建一个子进程
            if( (pid2 = fork()) < 0 )
            {
                printf("fork error\n");
                return ;
            }
            else if(pid2 == 0)
            {
                if( !(find_exeProgram_In_command(arg[0])) )
                {
                    printf("%s : command not found\n", arg[0]);
                    exit(0);
                }
                fd2 = open("/tmp/myshell", O_WRONLY | O_CREAT | O_TRUNC, 0644);
                dup2(fd2, 1);
                execvp(arg[0], arg);
                exit(0);
            }
            if(waitpid(pid2, &status2, 0) == -1)
            {
                printf("wait for child process error\n");
            }
            if( !(find_exeProgram_In_command(argnext[0])) )
            {
                printf("%s : command not found\n", argnext[0]);
                exit(0);
            }
            fd2 = open("/tmp/myshell", O_RDONLY);
            dup2(fd2, 0);
            execvp (argnext[0], argnext);

			// 删除一个文件, 如果它的filename参数是一个目录的话，其作用就相当于rmdir函数
			// int remove(const char *filename);
			//如果删除成功，remove返回0，否则返回EOF（-1）。
            // if( remove("/tmp/myshell") == -1 )
            {
                printf("remove error\n");
            }
            exit(0);
        }
        break;
    case 4:
        //输入的命令中含有输出追加重定向符>>
        if(pid == 0)
        {
            if( !(find_exeProgram_In_command(arg[0])) )
            {
                printf("%s : command not found\n", arg[0]);
                exit(0);
            }
            close(1);
            fd = open(file, O_WRONLY | O_CREAT | O_APPEND, 0644);
			//功能： 复制文件描述符
			//用法： int dup2(int oldfd,int newfd);
			//就是把标准输入获得的内容写到了fd指向的file文件里
            execvp(arg[0], arg);
            close(fd);
            exit(0);
        }
        break;

    default:
        break;
    }

    //若命令中有&，表示后台执行，父进程直接返回，不等待子进程结束
    if(background == 1)
    {
        printf("process id %d \n", pid);
        return ;
    }

    //父进程等待子进程结束
    if(waitpid(pid, &status, 0) == -1)
    {
        printf("wait for child process error\n");
    }
}
