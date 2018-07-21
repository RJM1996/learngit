#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<string.h>
#include<sys/types.h>
#include<sys/wait.h>
#include<sys/stat.h>
#include<fcntl.h>
#include<dirent.h>

#define normal 0   		//一般的命令
#define out_readirect 1   //输出重定向
#define out_add_readirect 4   //输出追加重定向
#define in_readdirect 2     //输入重定向
#define have_pipe 3   	//命令中有管道

void print_prompt();   		//打印提示符
void get_input(char *);     //得到输入的命令
void explain_input(char *, int *, char (*)[256]);  //对输入的命令进行解析
void do_cmd(int, char (*)[256]);  //执行命令
int find_exeProgram_In_command(char *);  //查找命令中的可执行程序
char* msg;  //用于myshell提示信息的输出
