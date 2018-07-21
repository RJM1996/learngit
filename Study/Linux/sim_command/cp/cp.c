#include<stdio.h>
#include<stdlib.h>
#include<sys/stat.h>
#include<dirent.h>
#include<unistd.h>
#include<string.h>

int main(int argc, char* argv[])
{
	if(argc != 3)
	{
		printf("usage:./cp src dst\n");
		exit(1);
	}
	struct stat sbuf_src;//创建一个结构体接收src文件信息
	if(lstat(argv[1], &sbuf_src) == -1)//获取src信息失败
	{
		printf("%s 不存在\n", argv[1]);
		exit(1);
	}

	if(S_ISREG(sbuf_src.st_mode))//如果src是一个普通文件
	{
		struct stat sbuf_dst;//定义一个结构体接收dst文件信息
		if(lstat(argv[2], &sbuf_dst) == 0)
		{
			FILE *fp_src = fopen(argv[1], "r");//检查对src是否有读权限
			FILE *fp_dst = fopen(argv[2], "w");//检查对dst是否有写权限
			if(fp_src == NULL || fp_dst == NULL)//若两个权限任意缺一，则无法复制
			{
				printf("没有权限，复制失败\n");
				return -1;
			}
			chmod(argv[2], sbuf_src.st_mode);//将dst权限与src统一

			char buf[10] = {};//定义一个字符数组
			int r = 0;
			int w_ren = 0; 
			while(r = fread(buf, 1, sizeof(buf), fp_src))
			{
				w_ren = fwrite(buf, 1, r, fp_dst);
				if(w_ren < 0)
				{
					printf("复制失败\n");
				}
			}
			fclose(fp_src);
			fclose(fp_dst);
			printf("复制成功\n");
		}
	}
	return 0;
}
