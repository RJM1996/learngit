#include<stdio.h>
#include<stdlib.h>
//递归求第n个斐波那契数
int fib(int n)
{
	if(n < 3)
	  return 1;
	return fib(n-1) + fib(n-2);
}

int main(int argc, char* argv[])//可变参数
{
	if(argc != 2)
	  return -1;
	else
	  printf("%d\n", fib(atoi(argv[1])));
	return 0;  
}
