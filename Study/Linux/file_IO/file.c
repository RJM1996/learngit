
#include<stdio.h>

int main()
{
	FILE* p_file;
	p_file = fopen("myfile.txt", "w");
	if(p_file != NULL)
	{
		//fputs("fopen example", p_file);
		fprintf(p_file, "example fclose");
		fclose(p_file);
	}
	return 0;
}
