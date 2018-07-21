#define _CRT_SECURE_NO_WARNINGS 1
#include <stdio.h>
#include <sys/types.h>
#include <dirent.h>
#include <sys/stat.h>
#include <pwd.h>
#include <grp.h>
#include <string.h>
#include <time.h>

void do_ls(char []);
void do_stat(char *);
void mode_to_letters(int , char []);
char* uid_to_username(uid_t);
char* gid_to_groupname(gid_t);

main(int argc, char *argv[])
{
	if(argc == 1 )
	{
		do_ls(".");   //未指定目录名，显示当前目录
	}
	else
	{
		//指定了目录名，按序显示各个目录下的文件
		while(--argc)
		{
			printf("%s:\n", *++argv);
			do_ls(*argv);
		}
	}

}

//打开目录，逐条读取目录项，并做相应处理
void do_ls(char dirname[])
{
	DIR *dir_ptr;  //指向目录文件流的指针
	struct dirent *dir;		//指向一个目录项的指针
	//struct dirent的定义：
	//struct dirent 
	//{
	//   ino_t          d_ino;       /* inode number */
	//   off_t          d_off;       /* offset to the next dirent */
	//   unsigned short d_reclen;    /* length of this record */
	//   unsigned char  d_type;      /* type of file; not supported
	//                                  by all file system types */
	//   char           d_name[256]; /* filename */
	//};

	//opendir(dirname),根据目录名dirname打开一个目录流，返回值是个指向该流的指针
	if( (dir_ptr = opendir(dirname)) == NULL )
	{
		//打开目录失败，显示错误信息到标准输出
		fprintf(stderr, "ls1: cannot open %s\n", dirname);
	}
	else
	{
		//struct dirent *readdir(DIR *dirp),返回指向directory entry（目录项）结构体的指针
		while( (dir = readdir(dir_ptr)) != NULL )
		{
			do_stat(dir->d_name);
		}
		closedir(dir_ptr);
	}
}

//根据文件名，获得文件的详细信息并显示
void do_stat(char *filename)
{
	struct stat stat_info;
	char modestr[11];
	char *username;
	char *groupname;
	// struct stat结构体的定义：
	//	struct stat 
	// {
	//        dev_t     st_dev;     /* ID of device containing file */
	//        ino_t     st_ino;     /* inode number */
	//        mode_t    st_mode;    /* protection */  /* mode_t 无符号的整数类型 unsigned int */
	//        nlink_t   st_nlink;   /* number of hard links */
	//        uid_t     st_uid;     /* user ID of owner */
	//        gid_t     st_gid;     /* group ID of owner */
	//        dev_t     st_rdev;     device ID (if special file) 
	//        off_t     st_size;    /* total size, in bytes */
	//        blksize_t st_blksize; /* blocksize for file system I/O */
	//        blkcnt_t  st_blocks;  /* number of 512B blocks allocated */
	//        time_t    st_atime;   /* time of last access */
	//        time_t    st_mtime;   /* time of last modification */
	//        time_t    st_ctime;   /* time of last status change */
	// };

	if( stat(filename, &stat_info) != 0 )
	{
		//文件详细信息获取失败
		perror(filename);
	}
	else
	{
		//文件详细信息获取成功

		//读写权限转换

		mode_to_letters(stat_info.st_mode ,modestr);

		//用户id转用户名
		username = uid_to_username(stat_info.st_uid);

		//组id转组名
		groupname = gid_to_groupname(stat_info.st_gid);

		//最后一次修改时间转换
		char *time = ctime(&stat_info.st_mtime);

		//输出结果
		printf("%s %4d %10s %10s %8ld %.12s  %-s\n",
			modestr, stat_info.st_nlink, username, groupname, (long)stat_info.st_size, time+4, filename);
	}

}

void mode_to_letters(int mode, char st_mode[])
{
	strcpy(st_mode, "----------") ;

	//以下使用/usr/include/linux/stat.h中定义的宏，利用掩码技术来逐个判断权限进行转换
	if( S_ISDIR(mode))
		st_mode[0] = 'd';
	if( S_ISCHR(mode))
		st_mode[0] = 'c';
	if( S_ISBLK(mode) )
		st_mode[0] = 'b';

	if( mode & S_IRUSR )
		st_mode[1] = 'r';
	if( mode & S_IWUSR )
		st_mode[2] = 'w';
	if( mode & S_IXUSR )
		st_mode[3] = 'x';

	if( mode & S_IRGRP )
		st_mode[4] = 'r';
	if( mode & S_IWGRP )
		st_mode[5] = 'w';
	if( mode & S_IXGRP )
		st_mode[6] = 'x';

	if( mode & S_IROTH )
		st_mode[7] = 'r';
	if( mode & S_IWOTH )
		st_mode[8] = 'w';
	if( mode & S_IXOTH )
		st_mode[9] = 'x';

}

char * uid_to_username(uid_t uid)
{
	//struct passwd *getpwuid(uid_t uid);根据用户id返回此用户信息的结构体
	struct passwd *passinfo;
	// struct passwd
	// {
	//   char *pw_name;		/* Username.  */
	//   char *pw_passwd;		/* Password.  */
	//   __uid_t pw_uid;		/* User ID.  */
	//   __gid_t pw_gid;		/* Group ID.  */
	//   char *pw_gecos;		/* Real name.  */
	//   char *pw_dir;			/* Home directory.  */
	//   char *pw_shell;		/* Shell program.  */
	// };

	if( (passinfo = getpwuid(uid)) == NULL)
	{
		return "errorName";
	}
	return passinfo->pw_name;
}
char * gid_to_groupname(gid_t gid)
{
	struct group *groupinfo;
	//struct group *getgrgid(gid_t gid);
	// struct group 
	// {
	//    char   *gr_name;       /* group name */
	//    char   *gr_passwd;      group password 
	//    gid_t   gr_gid;        /* group ID */
	//    char  **gr_mem;        /* group members */
	// };

	if( (groupinfo = getgrgid(gid)) == NULL )
	{
		return "errorName";
	}
	return groupinfo->gr_name;
}
