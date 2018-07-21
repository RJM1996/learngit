
#include<stdio.h>
#include<stdlib.h>

int main()
{
	int* ptr = malloc(10);
	if(ptr != NULL)
	{
		for(int i=0; i<10; i++)
		{
			printf("%d ",ptr[i]);
		}
	}
	else
	{
		exit(EXIT_FAILURE);
	}
	ptr = realloc(ptr, 100);
	int* p = NULL;
	p = (int*)realloc(ptr, 100);
	if(p != NULL)
	{
		ptr = p;
	}
	free(ptr);
	printf("\n");
	return 0;
}
