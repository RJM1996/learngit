
#include<stdio.h>
#include<stdlib.h>

int main()
{
	//创建僵尸进程
	pid_t id = fork();
	if(id < 0)
	{
		perror("fork");
		return -1;
	}
//	else if(id > 0)
//	{
//		printf("father is sleeping... %d\n", getpid());
//		sleep(30);
//	}
//	else
//	{
//		printf("children is sleeping... %d\n", getpid());
//		sleep(5);
//		exit(EXIT_SUCCESS);
//	}
	else if(id == 0)
	{
		printf("I am child %d \n", getpid());
		sleep(30);
	}
	else
	{
		printf("I am father %d \n", getpid());
		sleep(10);
		exit(0);
	}
	return 0;
}
