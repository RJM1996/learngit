
#include<stdio.h>
#include<stdlib.h>

int main()
{
	//void* calloc(size_t num, size_t size)
	//开辟内存并初始化为全0
	int *ptr = (int*)calloc(10, sizeof(int));
	for(int i=0; i<10; i++)
	{
		printf("%d ", ptr[i]);
	}
	printf("\n");
	free(ptr);
	ptr = NULL;
	return 0;
}
