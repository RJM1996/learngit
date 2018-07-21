#include "myshell.h"

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
