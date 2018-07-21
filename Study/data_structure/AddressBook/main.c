#include"addressbook.h"

void SaveFile(linkman* Plink)
{
	FILE* p_file = fopen("addressbook.txt", "a+");
	char s[] = "姓名     性别     年龄     电话     地址";
	if(p_file != NULL)
	{
		fprintf(p_file, "%s\n", &s);
		for(int i=0; i<Plink->size; i++)
		{
			fprintf( p_file, "%-9s ", &Plink->pcon[i].name);
			fprintf( p_file, "%-9s ", &Plink->pcon[i].sex);
			fprintf( p_file, "%-9d ", Plink->pcon[i].age);
			fprintf( p_file, "%-9s ", &Plink->pcon[i].tel);
			fprintf( p_file, "%-9s \n", &Plink->pcon[i].address);
		}
	}
	fclose(p_file);
	p_file = NULL;
}

int main()
{
	linkman MyLinkMan;
	AddressBookInit(&MyLinkMan);
	/*
	AddInformation(&MyLinkMan);
	DeleteInformation(&MyLinkMan);
	FindInformation(&MyLinkMan);
	AmendInformation(&MyLinkMan);
	*/
	while(1)
	{
		int n = 0;
		printf("===================================\n");
		printf("1：添加  2：删除  3：查找  4：修改\n");
		printf("5：显示  8：清空  7：升序  8：降序\n");
		printf("0：保存并退出\n");
		printf("===================================\n");
		printf("请输入=>");
		scanf("%d", &n);
		if(n>=0 && n<=8)
		{
			switch(n)
			{
				case 1:AddInformation(&MyLinkMan);//添加
					   break;
				case 2:DeleteInformation(&MyLinkMan);//删除
					   break;
				case 3:FindInformation(&MyLinkMan);//查找
					   break;
				case 4:AmendInformation(&MyLinkMan);//修改
					   break;
				case 5:ShowInformation(&MyLinkMan);//显示
					   break;
				case 6:EmptyInformation(&MyLinkMan);//清空
					   break;
				case 7:AddressBookSortAsc(&MyLinkMan, AgeSortAsc);//排序 - 年龄升序
					   break;
				case 8:AddressBookSortAsc(&MyLinkMan, AgeSortDes);//排序 - 年龄降序
					   break;
				case 0:printf("再见！\n");
						SaveFile(&MyLinkMan);
						exit(1);
			}
		}
		else
		{
		  printf("输入有误，请重输\n");
		  continue;
		}
	}
	return 0;
}
