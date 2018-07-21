//shell.c

#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<string.h>
#include<sys/types.h>
#include<sys/wait.h>
#include<sys/stat.h>
#include<fcntl.h>
#include<dirent.h>

#define normal  0   		//一般的命令
#define out_readirect   1   //输出重定向
#define in_readdirect 2     //输入重定向
#define have_pipe   3   	//命令中有管道

void print_prompt();   		//打印提示符
void get_input(char *);     //得到输入的命令
void explain_input(char *, int *, char (*)[256]);  //对输入的命令进行解析
void do_cmd(int, char (*)[256]);  //执行命令
int find_exeProgram_In_command(char *);  //查找命令中的可执行程序
char* msg;  //用于myshell提示信息的输出

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


//获取用户输入
void get_input(char* buf)
{
    int len = 0;
    int ch;

    ch = getchar();
    while(len < 256 && ch != '\n')
    {
		//用getchar获取字符,以'\n'结束
        buf[len++] = ch;
        ch = getchar();
    }

    if(len == 256)
    {
		//输入的命令不能超过256个字符
        printf("command is too long\n");
        exit(-1);
    }
    buf[len] = '\n';
    len++;
    buf[len] = '\0';
}



//解析buf中的命令，将结果存入arglist中，命令以回车符号\n结束
void explain_input(char* buf, int* argcount, char (*arglist)[256])
{
    char *p = buf;
    char *q = buf;
    int number = 0;
    int i;
    while(1)
    {
        if(p[0] == '\n')
        {
			//如果buf第一个字符就是'\n', 就退出
            break;
        }

        if(p[0] == ' ')
        {
			//如果第一个字符是空格, 指针往后+1
            p++;
        }
        else
        {
            q = p;
            number = 0;
            while((q[0] != ' ') && (q[0] != '\n'))
            {
                if(q[0] == 92)  //反斜杠
                {
                    q[0] = ' ';
                    q[1] = q[2];
                    for(i = 2; ; i++)
                    {
                        q[i] = q[i + 1];
                        if((q[i] == ' ') || (q[i] == '\n'))
                            break;
                    }
                }
                number++;
                q++;
            }
            strncpy(arglist[*argcount], p, number + 1);//将解析完的命令拷贝到arglist
            arglist[*argcount][number] = '\0';
            *argcount = *argcount + 1;
            p = q;
        }
    }
}

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
    pid_t pid;
    char* file;
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


//查找命令中的可执行程序
int find_exeProgram_In_command(char *command)
{
    DIR* dp;
    struct dirent* dirp;
    char* path[] = {"./", "/bin", "/usr/bin", NULL};

    //使当前目录下的程序可以运行，如命令“./fork”可以被正确解释和执行
    if( strncmp(command, "./", 2) == 0 )
    {
        command = command + 2;
    }

    //分别在当前目录，/bin和/usr/bin目录查找要执行的程序
    int i = 0;
    while(path[i] != NULL)
    {
        if( (dp = opendir(path[i])) == NULL )
        {
            printf("can not open /bin \n");
        }
        while( (dirp = readdir(dp)) != NULL )
        {
            if(strcmp(dirp->d_name, command) == 0)
            {
                closedir(dp);
                return 1;
            }
        }
        closedir(dp);
        i++;
    }
    return 0;
}


int main(int argc, char** argv)
{
    int i;
    int argcount = 0;
    char arglist[100][256];
    char** arg = NULL;
    char* buf = NULL;

    buf = (char*)malloc(256);
    if(buf == NULL)
    {
		//内存开辟失败
        perror("malloc failed");
        exit(-1);
    }

    while(1)
    {
        memset(buf, 0, 256);    //将buf所指的空间清零
        print_prompt(); //打印导航栏
        get_input(buf); //获取输入
        if( strcmp(buf, "exit\n") == 0 || strcmp(buf, "logout\n") == 0)
        {
			//如果输入 exit 或者 logout 就退出
            break;
        }
        for(i = 0; i < 100; i++)
        {
            arglist[i][0] = '\0'; //每个命令后面都加一个'\0'作为结束标志
        }
        argcount = 0;
        explain_input(buf, &argcount, arglist); //解析命令
        do_cmd(argcount, arglist); //执行命令
    }

    if(buf != NULL)
    {
        free(buf); //释放 buf 内存空间
        buf = NULL;
    }
    //exit(0);
	return 0;
}
