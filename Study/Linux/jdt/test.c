#include<stdio.h>
#include<unistd.h>

// 带颜色的进度条
int main()
{
	int i = 0;
	char buf[52] = "=";
	char sym[] = "|/~\\";
	for(; i<=50; i++)
	{
		buf[i] = '=';
		printf("\033[36m [%-50s]\033[0m \033[34m[%d%%] \033[35m[%c] \033[0m\r", buf, i*2, sym[i%4]);
		fflush(stdout);
		usleep(100000);
	}
	printf("\n");
	return 0;
}
