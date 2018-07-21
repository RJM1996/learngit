
#include<stdio.h>
#include<stdlib.h>
#include<string.h>

void getmemory(char** p)
{
	*p = (char*)malloc(100);
}

int main()
{
	char* str = NULL;
	getmemory(&str);
	strcpy(str, "hello");
	printf(str);
	printf("\n");
	free(str);
	return 0;
}
