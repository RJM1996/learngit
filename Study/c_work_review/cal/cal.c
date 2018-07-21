#define _CRT_SECURE_NO_WARNINGS 1
//使用main函数的参数，实现一个整数计算器，程序可以接受三个参数
//第一个参数“-a”加法，“-s”减法，“-m”乘法，“-d”除法，后面两个参数为操作数。 
//例如：命令行参数输入：test.exe -a 1 2 
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
//定义加减乘除运算的函数
int my_add(int x, int y)
{
	return x + y;
}
int my_sub(int x, int y)
{
	return x - y;
}
int my_mul(int x, int y)
{
	return x * y;
}
int my_div(int x, int y)
{
	if(y == 0)
	{
		printf("除数为0，错误！\n");
		return -1;
	}
	return x / y;
}
// 01 -(a|s|m|d) x y  共有4个参数
int main(int argc, char* argv[])
{
	if(argc != 4)
	{
		printf("用法：%s -(a|s|m|d) x y\n", argv[0]);
		return 1;
	}
	int op = 0;//op即为argv[]的元素下标0 1 2 3
	int (*mycal_arr[])(int, int) = {my_add, my_sub, my_mul, my_div}; //定义一个函数指针数组
	//将第二个参数的内容与 -(a|s|m|d) 比较，以确定使用哪种运算
	if(strcmp(argv[1], "-a") == 0)
	{
		op = 0;
	}
	else if(strcmp(argv[1], "-s") == 0)
	{
		op = 1;
	}
	else if(strcmp(argv[1], "-m") == 0)
	{
		op = 2;
	}
	else if(strcmp(argv[1], "-d") == 0)
	{
		op = 3;
	}
	else
	{
		printf("输入错误！-- 用法：%s -(a|s|m|d) x y\n", argv[0]);
		return 1;
	}
	int x = atoi(argv[2]); //argv[]是char* 类型 要转成整形 用atoi()函数
	int y = atoi(argv[3]);
	int res = mycal_arr[op](x, y);
	printf("运算结果：%d\n", res);

}
