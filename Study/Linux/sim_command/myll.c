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
		do_ls(".");   //δָ��Ŀ¼������ʾ��ǰĿ¼
	}
	else
	{
		//ָ����Ŀ¼����������ʾ����Ŀ¼�µ��ļ�
		while(--argc)
		{
			printf("%s:\n", *++argv);
			do_ls(*argv);
		}
	}

}

//��Ŀ¼��������ȡĿ¼�������Ӧ����
void do_ls(char dirname[])
{
	DIR *dir_ptr;  //ָ��Ŀ¼�ļ�����ָ��
	struct dirent *dir;		//ָ��һ��Ŀ¼���ָ��
	//struct dirent�Ķ��壺
	//struct dirent 
	//{
	//   ino_t          d_ino;       /* inode number */
	//   off_t          d_off;       /* offset to the next dirent */
	//   unsigned short d_reclen;    /* length of this record */
	//   unsigned char  d_type;      /* type of file; not supported
	//                                  by all file system types */
	//   char           d_name[256]; /* filename */
	//};

	//opendir(dirname),����Ŀ¼��dirname��һ��Ŀ¼��������ֵ�Ǹ�ָ�������ָ��
	if( (dir_ptr = opendir(dirname)) == NULL )
	{
		//��Ŀ¼ʧ�ܣ���ʾ������Ϣ����׼���
		fprintf(stderr, "ls1: cannot open %s\n", dirname);
	}
	else
	{
		//struct dirent *readdir(DIR *dirp),����ָ��directory entry��Ŀ¼��ṹ���ָ��
		while( (dir = readdir(dir_ptr)) != NULL )
		{
			do_stat(dir->d_name);
		}
		closedir(dir_ptr);
	}
}

//�����ļ���������ļ�����ϸ��Ϣ����ʾ
void do_stat(char *filename)
{
	struct stat stat_info;
	char modestr[11];
	char *username;
	char *groupname;
	// struct stat�ṹ��Ķ��壺
	//	struct stat 
	// {
	//        dev_t     st_dev;     /* ID of device containing file */
	//        ino_t     st_ino;     /* inode number */
	//        mode_t    st_mode;    /* protection */  /* mode_t �޷��ŵ��������� unsigned int */
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
		//�ļ���ϸ��Ϣ��ȡʧ��
		perror(filename);
	}
	else
	{
		//�ļ���ϸ��Ϣ��ȡ�ɹ�

		//��дȨ��ת��

		mode_to_letters(stat_info.st_mode ,modestr);

		//�û�idת�û���
		username = uid_to_username(stat_info.st_uid);

		//��idת����
		groupname = gid_to_groupname(stat_info.st_gid);

		//���һ���޸�ʱ��ת��
		char *time = ctime(&stat_info.st_mtime);

		//������
		printf("%s %4d %10s %10s %8ld %.12s  %-s\n",
			modestr, stat_info.st_nlink, username, groupname, (long)stat_info.st_size, time+4, filename);
	}

}

void mode_to_letters(int mode, char st_mode[])
{
	strcpy(st_mode, "----------") ;

	//����ʹ��/usr/include/linux/stat.h�ж���ĺ꣬�������뼼��������ж�Ȩ�޽���ת��
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
	//struct passwd *getpwuid(uid_t uid);�����û�id���ش��û���Ϣ�Ľṹ��
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
