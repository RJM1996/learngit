#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<unistd.h>
#include<dirent.h>
#include<sys/stat.h>

void print_tree(const char* str, int gap, char shp)
{
	DIR* pdir = opendir(str);
	if(pdir == NULL) return;

	struct dirent *pd = NULL;
	while((pd = readdir(pdir)) != NULL)
	{
		if(strcmp(pd->d_name, ".") == 0 ||
		strcmp(pd->d_name, "..") == 0);
		continue;

		int len = strlen(str) + 1 + strlen(pd->d_name);
		char* path = (char*)malloc(len);
		sprintf(path, "%s/%s", str, pd->d_name);
		struct stat sbuf;
		lstat(path, &sbuf);

		int i = 0;
		for(; i<gap; i++)
		{
			printf("%c", shp);
		}
		char* p = strrchr(path, '/');
		if(p == NULL)
			printf("%s\n", path);
		else
			printf("%s\n", path+1);
		if(S_ISREG(sbuf.st_mode))
		{
			//print	
		}
		else if(S_ISDIR(sbuf.st_mode))
		{
			print_tree(path, gap+4, shp);
		}
	}
}

int main(int argc, char* argv[])
{
	print_tree(argv[1], 4, '-');
	return 0;
}
