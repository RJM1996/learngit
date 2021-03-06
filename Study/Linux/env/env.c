
#include<stdio.h>
#include<stdlib.h>

int main()
{
    //函数名: getenv
    //功 能: 从环境中取字符串,获取环境变量的值
    //头文件: stdlib.h
    //用 法:char *getenv(char *envvar);
    //函数说明:
    //getenv()用来取得参数envvar环境变量的内容。
    //参数envvar为环境变量的名称，如果该变量存在则会返回指向该内容的指针。
    //环境变量的格式为envvar=value。getenv函数的返回值存储在一个全局二维数组里，
    //当你再次使用getenv函数时不用担心会覆盖上次的调用结果。
    //返回值: 执行成功则返回指向该内容的指针，找不到符合的环境变量名称则返回NULL。
    //如果变量存在但无关联值，它将运行成功并返回一个空字符串，即该字符的第一个字节是null。
	char* env = getenv("PATH");
	if(env != NULL)
	{
		printf("%s\n", env);
	}
	return 0;
}
//int main(int argc, char* argv[], char* env[])
//{
//	int i = 0;
//	extern char** environ;
//	for(; environ[i]; i++)
//	{
//		printf("%s\n", environ[i]);
//	}
//	return 0;
//}
