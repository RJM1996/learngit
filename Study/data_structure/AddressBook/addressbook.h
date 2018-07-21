#include<stdio.h>
#include<stdlib.h>
#include<memory.h>
#include<assert.h>
#include<string.h>

#define DEFAULT_SZ 3//初始通讯录大小为3 即只能存储3个人的信息
#define DEFAULT_INC 5//每次增容的大小为5 即每次增容后 能多存5个人的信息

typedef struct people
{
	char name[20];//姓名
	char sex[5];//性别
	int age;//年龄
	char tel[11];//电话
	char address[50];//住址
}peo;//即为 struct people 等同于 peo

typedef struct LinkMan
{
	peo *pcon;
	size_t size;//当前通讯录的大小
	size_t capacity;//当前通讯录总的容量
}linkman;//即为struct LinkMan 等同于 linkman

void AddressBookInit(linkman* Plink); //初始化
void AddInformation(linkman* Plink);//添加
void DeleteInformation(linkman* Plink);//删除
void FindInformation(linkman* Plink);//查找
void AmendInformation(linkman* Plink);//修改
void ShowInformation(linkman* Plink);//显示
void EmptyInformation(linkman* Plink);//清空
void AddressBookSort(linkman* Plink);//排序
void Dilatation(linkman* Plink);//检测 扩容
int Find(linkman* Plink, char* name);
void AddressBookSortAsc(linkman* Plink, int(*cmp)(int*, int*));
int AgeSortAsc(int* a1, int* a2);
int AgeSortDes(int* a1, int* a2);
