#include<stdio.h>
#include<stdlib.h>
#include<assert.h>
//循环实现斐波那契数列
long fib(int n)
{
	assert(n>0);
	long first = 0;
	long second = 1;
	long ret = 0;
	for(int i=2; i<=n; i++)
	{
		ret = first + second;
		first = second;
		second = ret;
	}
	return ret;
}

int main()
{
	printf("%d\n", fib(9));
	return 0;
}
