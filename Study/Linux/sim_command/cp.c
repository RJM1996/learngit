//模拟实现cp.c
#include<stdio.h>
#include<stdlib.h>
#include<sys/stat.h>
#include<unistd.h>
#include<string.h>

void copy_file(char* argv[], char* tmp, )//拷贝文件函数
{

}
void cp_dir(char* src, char* dst)//拷贝目录函数
{
	DIR* pdir = opendir(src);
	struct dirent* pd = NULL;

	while((pd = readdir(pdir)) != NULL)
	{
		if((strcmp(pd->d-name, ".")|| strcmp(pd->d_name, "..")) == 0) continue;

		int len = strlen(src)+2+strlen(pd->d_name);
		char* src_name = (char*)malloc(len);
		memset(src_name, 0x00, len);
		sprintf(src_name, "%s/%s", src, pd->d_name);

		len = strlen(dst)+2+strlen(pd->d_name);
		char* dst_name = (char*)malloc(len);
		memset((dst_name, 0x00, len);
		sprintf(dst_name, "%s/%s", dst, pd->d_name);
		
		struct stat sbuf;
		lstat(src_name, &sbuf);
		if(S_ISREG(sbuf.st_mode))//如果是普通文件，直接拷贝
		{
			cp_file(src_name, dst_name, sbuf.st_mode)
		}
		else if(S_ISDIR(sbuf.st_mode))//如果是目录，先创建目录，再拷贝
		{
			mkdir(dst_name, sbuf.st_mode);
			cp_dir(src_name, dst_name);
		}

	}
}

int main(int argc, char* argv[])
{
	if(argc != 3)//如果参数不为3 报错
	{
		fprintf(stderr, "error");
		exit(1);
	}
	//
	struct stat sbuf_src;
	if(lstat(argv[1], &sbuf_src) == -1)
	{
		fprintf(stderr, "%s 不存在\n", argv[1]);
		exit(1);
	}

	mode_t old = umask(0);
	if(S_ISREG(sbuf_src.st_mode))
	{
		struct stat sbuf_dst;
		if(lstat(argv[2], &sbuf_dst) == 1)
		{
			FILE *fp_dst = fopen(argv[2], "w");
			FILE *fp_src = fopen(argv[1], "r");
			if(fp_src == NULL || fp_dst == NULL)
			{
				fprintf(stderr, "open file error\n");
				return -1;
			}

			chmod(argv[2], sbuf_src.st_mode);

			char buf[10] = {};
			int r = 0;
			while((r = fread(buf, 1, sizeof(buf), fp_src)))
			{
				fwrite(buf, 1, r, fp_dst);
			}
			fcolse(fp_src);
			fcolse(fp_dst);
		}
		else if
		{
			printf("目标文件存在，是否覆盖？[y/n]");
			char c = 'n';
			scanf("%[yYnN]", &c);
			//printf("c = [%c]\n", c);
			if(c == 'y' || c == 'Y')
			{
				copy_file(argv[1], argv[2], sbuf_src.st_mode);	
			}
		}
		else if(S_ISDIR(sbuf_dst.st_mode))
		{
			int len = strlen(argv[1]+2+strlen(argv[2]));
			char* tmp = (char*)malloc(len);
			memset(tmp, 0x00, len);
			sprintf(tmp, "%s/%s", argv[2], argv[1]);
			copy_file(argv[1], tmp, sbuf_src.st_mode);
		}
		else if()
		{
			
		}

		else if(S_ISDIR(sbuf_dst.st_mode))
		{
			int len = strlen(argv[1]+2+strlen(argv[2]));
			char* tmp = (char*)malloc(len);
			memset(tmp, 0x00, len);
			sprintf(tmp, "%s/%s", argv[2], argv[1]);
			copy_dir(argv[1], tmp);
		}
	}
	umask(old);
}
