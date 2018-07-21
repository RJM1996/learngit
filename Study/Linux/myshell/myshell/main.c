#include "myshell.h"

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
