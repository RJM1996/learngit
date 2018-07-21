
#include<stdio.h>
#include<stdlib.h>

int main()
{
	//void* malloc(size_t size)
	int num = 0;
	printf("please input\n");
	scanf("%d", &num);
	//int arr[num] = {0}; 
	int *ptr = NULL;
	ptr = (int*)malloc(num*sizeof(int));
	for(int i=0; i<num; i++)
	{
		*(ptr+i) = 0;
		printf("%d ", arr[i]);
	}
	printf("\n");
	free(ptr);
	ptr = NULL;
	return 0;
}
