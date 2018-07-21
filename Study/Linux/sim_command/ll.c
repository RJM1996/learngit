#include<stdio.h>
#include<grp.h>
#include<time.h>
#include<pwd.h>
#include<dirent.h>
#include<sys/stat.h>
#include<stdlib.h>
#include<unistd.h>


void file_type(mode_t md)
{
	
	char mode[11] = "?---------";
	//文件属性
	if((md & S_IFMT) == S_IFREG) mode[0] = '-';
	if((md & S_IFMT) == S_IFDIR) mode[0] = 'd';
	if((md & S_IFMT) == S_IFIFO) mode[0] = 'p';
	if((md & S_IFMT) == S_IFSOCK) mode[0] = 's';
	if((md & S_IFMT) == S_IFBLK) mode[0] = 'b';
	if((md & S_IFMT) == S_IFCHR) mode[0] = 'c';
	if((md & S_IFMT) == S_IFLNK) mode[0] = 'l';
	//文件权限
	if((md & S_IRUSR)) mode[1] = 'r';
	if((md & S_IWUSR)) mode[2] = 'w';
	if((md & S_IXUSR)) mode[3] = 'x';
	if((md & S_IRGRP)) mode[4] = 'r';
	if((md & S_IWGRP)) mode[5] = 'w';
	if((md & S_IXGRP)) mode[6] = 'x';
	if((md & S_IROTH)) mode[7] = 'r';
	if((md & S_IWOTH)) mode[8] = 'w';
	if((md & S_IXOTH)) mode[9] = 'x';

	printf("%s. ", mode);
}
int main(int argc, char* argv[])
{
	if(argc != 2)
	{
		fprintf(stderr, "usage: %s filename\n");
		exit(1);
	}
	struct stat sbuf;
	lstat(argv[1], &sbuf);

    //打印文件类型 文件权限信息
	file_type(sbuf.st_mode);

	//硬链接个数
	printf("%d ",sbuf.st_nlink);

	//文件拥有者；所在组
	uid_t my_uid;
	gid_t my_gid;
	struct passwd *myname;
	struct group *mygrp;
	myname = getpwuid(getuid());
	mygrp = getgrgid(getgid());
	printf("%2s ", myname->pw_name);
	printf("%2s ", mygrp->gr_name);
	
	//文件大小
	printf("%d ", sbuf.st_size);
	
	//文件更新时间
	struct tm *block;
	block = localtime(&sbuf.st_mtime);
	printf("%4d-%02d-%02d %02d:%02d ", 
			block->tm_year+1900, block->tm_mon+1, block->tm_mday,
			block->tm_hour, block->tm_min);

	//文件名
	printf("%s ",argv[1]);
	char buf[256] = {};
	if(S_ISLNK(sbuf.st_mode))
	{
		printf("-> ");
		readlink(argv[1], buf, 256);
		printf("%s", &buf);
		// ssize_t readlink(const char *path, char *buf, size_t bufsiz);
	}

	//显示目录
	/*
	DIR* pdir = opendir(".");
	if(pdir == NULL)
	{
		fprintf(stderr, "open dir error\n");
		return -1;
	}

	struct dirent *pd = NULL;
	while((pd = readdir(pdir)) != NULL)
	{
		if(pd->d_name[0] == '.')
			continue;
		printf(" %s\n", pd->d_name);

	}
	closedir(pdir);
	*/

	printf("\n");
	return 0;
}
