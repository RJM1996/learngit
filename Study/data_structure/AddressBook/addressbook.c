#include"addressbook.h"
//动态内存开辟版本
//初始化通讯录
void AddressBookInit(linkman* Plink)
{
	assert(Plink);
	Plink->pcon = (peo*)malloc(DEFAULT_SZ*sizeof(peo));//申请peo类型大小乘以3的空间
	if(Plink->pcon == NULL)//申请失败
	{
		perror("malloc error\n");
		exit(EXIT_FAILURE);//退出 错误信息
	}
	memset(Plink->pcon, 0, DEFAULT_SZ*sizeof(peo));//内存初始化为全0
	Plink->size = 0;//通讯录置空
	Plink->capacity = DEFAULT_SZ;//初始容量为3
}

//扩容函数 检查容量并扩容
void Dilatation(linkman* Plink)
{
	peo* ptr = NULL;//定义peo*类型的指针ptr 赋空
	if(Plink->size == Plink->capacity)//如果当前已经存储的大小等于通讯录的当前总容量 则需要扩容
	{
		ptr = (peo*)realloc(Plink->pcon, (Plink->size + DEFAULT_INC)*sizeof(peo));//多申请5*peo类型大小的空间

		if(ptr == NULL)
		{
			perror("realloc error\n");
			return;
		}
		else
		{
			Plink->pcon = ptr;//新申请的空间地址给pcon
			Plink->capacity = Plink->capacity + DEFAULT_INC;//容量加5
		}
	}
}

//添加联系人信息
void AddInformation(linkman* Plink)
{
	assert(Plink);
	printf("=====%s=====\n", __FUNCTION__);
	Dilatation(Plink);//添加之前 先判断是否需要扩容

	printf("\n请输入联系人信息=>\n");
	printf("姓名：");
	scanf("%s", Plink->pcon[Plink->size].name);
	printf("性别：");
	scanf("%s", Plink->pcon[Plink->size].sex);
	printf("年龄：");
	scanf("%d", &Plink->pcon[Plink->size].age);
	printf("电话：");
	scanf("%s", Plink->pcon[Plink->size].tel);
	printf("地址：");
	scanf("%s", Plink->pcon[Plink->size].address);
	Plink->size++;
	//printf("size = %d\n", Plink->size);
}
//删除指定联系人信息
void DeleteInformation(linkman* Plink)
{
	printf("=====%s=====\n", __FUNCTION__);
	//printf("size = %d\n", Plink->size);
	assert(Plink);
	char name[20];
	printf("请输入要删除的联系人姓名=>");
	scanf("%s", &name);

	int ret = Find(Plink, name);
	if(ret >= 0)
	{
		char flag1;
		printf("确认要删除吗？[y/n] => ");
		scanf("%s", &flag1);
		if(flag1 == 'y')
		{
			if(Plink->size == 1)
			{
				Plink->size--;
			}
			else
			{
				for(size_t j=ret; j<Plink->size-1; j++)
				{
					//printf("j = %d, size = %d\n", j, Plink->size);
					Plink->pcon[j] = Plink->pcon[j+1];
				}
				Plink->size--;
			}
			printf("删除成功\n");
			//printf("%zd\n", Plink->size);
		}
		else
		  printf("没有删除\n");
	}
}
//查找指定联系人信息 
int Find(linkman* Plink, char* name)
{
	printf("=====%s=====\n", __FUNCTION__);
	assert(Plink);
	size_t k = 0;
	for(; k<=Plink->size; k++)
	{
		if(strcmp(Plink->pcon[k].name, name) == 0)
		{
			printf("姓名：%s\n", Plink->pcon[k].name);
			printf("性别：%s\n", Plink->pcon[k].sex);
			printf("年龄：%d\n", &Plink->pcon[k].age);
			printf("电话：%s\n", Plink->pcon[k].tel);
			printf("地址：%s\n", Plink->pcon[k].address);
			return k;
		}
	}
	printf("此人不存在\n");
	return -1;
}


void FindInformation(linkman* Plink)
{
	printf("=====%s=====\n", __FUNCTION__);
	assert(Plink);
	char name[20];
	printf("请输入要查找的联系人姓名=>");
	scanf("%s", &name);
	size_t k = 0;
	int flag22 = 0;
	for(; k<=Plink->size; k++)
	{
		if(strcmp(Plink->pcon[k].name, name) == 0)
		{
			flag22 = 1;
			printf("姓名：%s\n", Plink->pcon[k].name);
			printf("性别：%s\n", Plink->pcon[k].sex);
			printf("年龄：%d\n", &Plink->pcon[k].age);
			printf("电话：%s\n", Plink->pcon[k].tel);
			printf("地址：%s\n", Plink->pcon[k].address);
		}
	}
	if(flag22 != 1)
	{
		printf("此人不存在\n");
	}
}
//修改指定联系人信息 
void AmendInformation(linkman* Plink)
{
	printf("=====%s=====\n", __FUNCTION__);
	assert(Plink);
	if(Plink->size == 0)
	{
		printf("联系人列表为空\n");
		return;
	}
	char name[20];
	printf("请输入要修改的联系人姓名=>");
	scanf("%s", &name);
	int l = Find(Plink, name);
	printf("请修改=>\n");
	printf("姓名：");
	scanf("%s", Plink->pcon[l].name);
	printf("性别：");
	scanf("%s", Plink->pcon[l].sex);
	printf("年龄：");
	scanf("%d", &Plink->pcon[l].age);
	printf("电话：");
	scanf("%s", Plink->pcon[l].tel);
	printf("地址：");
	scanf("%s", Plink->pcon[l].address);
	printf("修改成功\n");
}
//显示所有联系人信息 
void ShowInformation(linkman* Plink)
{
	printf("=====%s=====\n", __FUNCTION__);
	assert(Plink);
	//printf("%d\n" , Plink->size);
	if(Plink->size == 0)
	{
		printf("联系人列表为空\n");
		return;
	}
	printf("姓名   性别   年龄   电话   地址\n");
	for(size_t m=0; m<Plink->size; m++)
	{
		printf("%-6s ",Plink->pcon[m].name);
		printf("%-6s ",Plink->pcon[m].sex);
		printf("%-6d ",Plink->pcon[m].age);
		printf("%-6s ",Plink->pcon[m].tel);
		printf("%-6s ",Plink->pcon[m].address);
		printf("\n");
	}
}
//清空所有联系人
void EmptyInformation(linkman* Plink)
{
	printf("=====%s=====\n", __FUNCTION__);
	if(Plink->size == 0)
	{
		printf("联系人列表已经为空\n");
		return;
	}
	else
	{
		Plink->size = 0;
	}
	if(Plink->pcon != NULL)
	{
		free(Plink->pcon);
		Plink->pcon = NULL;
		printf("清空成功\n");
	}
	else
	  printf("已经为空\n");
}

//排序规则
//01.以姓名排序
int NameSort(char* n1, char* n2)
{
	return (n1 > n2) ? 1 : 0;
}

//02.以年龄升序
int AgeSortAsc(int* a1, int* a2)
{
	printf("=====%s=====\n", __FUNCTION__);
	if(*a1 > *a2)
		return 1;
	else
		return 0;
}
//02.以年龄降序
int AgeSortDes(int* a1, int* a2)
{
	printf("=====%s=====\n", __FUNCTION__);
	if(*a1 < *a2)
		return 1;
	else
		return 0;
}

//调用回调函数
//排序所有联系人
void AddressBookSortAsc(linkman* Plink, int(*cmp)())
{
	printf("=====%s=====\n", __FUNCTION__);
	assert(Plink);
	if(Plink->size == 0)
	{
		printf("联系人列表为空\n");
		return;
	}
	for(size_t n=0; n<Plink->size; n++)
	{
		for(size_t o=0; o<Plink->size-n-1; o++)
		{
			//printf("return = %d\n", cmp(&Plink->pcon[o].age, &Plink->pcon[o+1].age));
			if(cmp(&Plink->pcon[o].age, &Plink->pcon[o+1].age))
			{
				struct people tmp = Plink->pcon[o];
				Plink->pcon[o] = Plink->pcon[o+1];
				Plink->pcon[o+1] = tmp;
			}
		}
	}
	printf("排序完成\n");
	ShowInformation(Plink);
}
