#include<stdio.h>
#include<stdlib.h>
#include<memory.h>
#include<assert.h>

#define MAX_SIZE 10
typedef int DataType;

//定义一个顺序表
typedef struct SeqList
{
	DataType arr[MAX_SIZE];//拥有十个元素的整型数组
	int size;//顺序表中有效元素的个数
}SeqList;

void SeqListInit(SeqList* seq_p);
void SeqListHeadInsert(SeqList* seq_p, DataType num);
void SeqListPrint(SeqList* seq_p);

//初始化顺序表
void SeqListInit(SeqList* seq_p)
{
	printf("\n========%s========\n", __FUNCTION__);
	printf("初始化顺序表\n");
	if(seq_p == NULL)
	{
		printf("非法输入\n");
		return;
	}
	//assert(seq_p);
	memset(seq_p->arr, 0, MAX_SIZE*sizeof(DataType));//memset函数按字节对内存块进行初始化
	seq_p->size = 0;
	printf("\n");
}

//顺序表尾部插入
void SeqListTailInsert(SeqList* seq_p, DataType num)
{
	printf("\n========%s========\n", __FUNCTION__);
	printf("尾部插入\n");
	if(seq_p == NULL)
	{
		printf("非法输入\n");
		return;
	}
	if(seq_p->size == MAX_SIZE)
	{
		printf("顺序表已满\n");
		return;
	}
	seq_p->arr[seq_p->size] = num;
	++seq_p->size;
	SeqListPrint(seq_p);
}
//尾部删除
void SeqListTailDelete(SeqList* seq_p)
{
	printf("\n========%s========\n", __FUNCTION__);	
	printf("尾部删除\n");
	assert(seq_p);
	if(seq_p->size == 0)
	{
		printf("顺序表已经为空\n");
		return;
	}
	seq_p->size--;
	SeqListPrint(seq_p);
}
//头部插入
void SeqListHeadInsert(SeqList* seq_p, DataType num)
{
	printf("\n========%s========\n", __FUNCTION__);
	printf("头部插入\n");
	assert(seq_p);
	if(seq_p->size == MAX_SIZE)
	{
		printf("顺序表已满\n");
		return;
	}
	int i = seq_p->size++;
	for(; i>0; i--)
	{
		seq_p->arr[i] = seq_p->arr[i-1];//将顺序表中的元素往后移动一位	
	}
	seq_p->arr[0] = num;//第一位插入元素
	SeqListPrint(seq_p);
}
//头部删除
void SeqListHeadDelete(SeqList* seq_p)
{
	printf("\n========%s========\n", __FUNCTION__);
	printf("头部删除\n");
	assert(seq_p);
	if(seq_p->size == 0)
	{
		printf("顺序表已经为空\n");
		return;
	}
	int i = 0;
	for(; i<seq_p->size-1; i++)
	{
		seq_p->arr[i] = seq_p->arr[i+1];
	}
	seq_p->size--;
	SeqListPrint(seq_p);
}

//读任意位置元素
void SeqListReadAnywhere(SeqList* seq_p, DataType pos)
{
	printf("\n========%s========\n", __FUNCTION__);
	printf("读任意位置元素\n");
	assert(seq_p);
	if(seq_p->size == 0)
	{
		printf("顺序表已经为空\n");
		return;
	}
	if(pos >= seq_p->size)
	{
		printf("没有下标为%d的元素\n", pos);
		return;
	}
	printf("下标为%d的元素是[%d]\n", pos, seq_p->arr[pos]);
	printf("\n");
}
//修改任意位置元素
void SeqListAlterAnywhere(SeqList* seq_p, DataType pos, DataType num)
{
	printf("\n========%s========\n", __FUNCTION__);
	printf("修改任意位置元素\n");
	assert(seq_p);
	if(seq_p->size == 0)
	{
		printf("顺序表已经为空\n");
		return;
	}
	if(pos >= seq_p->size)
	{
		printf("没有下标为%d的元素\n", pos);
		return;
	}
	printf("修改下标为%d的元素为%d\n", pos, num);
	seq_p->arr[pos] = num;
	SeqListPrint(seq_p);
}
//查找指定元素的下标
void SeqListFindAnywhere(SeqList* seq_p, DataType num)
{
	printf("\n========%s========\n", __FUNCTION__);
	printf("查找指定元素的下标\n");
	assert(seq_p);
	if(seq_p->size == 0)
	{
		printf("顺序表已经为空\n");
		return;
	}
	int i = seq_p->size-1;
	for(; i>=0; i--)
	{
		if(num == seq_p->arr[i])
		{
			printf("[%d]的下标是%d\n", num, i);
		}
	}
	SeqListPrint(seq_p);
}
//在任意位置插入元素
void SeqListInsertAnywhere(SeqList* seq_p, DataType pos, DataType num)
{
	printf("\n========%s========\n", __FUNCTION__);
	printf("在任意位置插入元素\n");
	printf("在%d下标插入%d\n", pos, num);
	assert(seq_p);
	if(seq_p->size == MAX_SIZE)
	{
		printf("顺序表已满\n");
		return;
	}
	++seq_p->size;
	int i = pos;
	for(i=pos; i<seq_p->size; i++)
	{
		seq_p->arr[i+1] = seq_p->arr[i];
	}
	seq_p->arr[pos] = num;
	SeqListPrint(seq_p);

}
//打印顺序表
void SeqListPrint(SeqList* seq_p)
{
	//printf("\n========%s========\n", __FUNCTION__);
	//printf("打印顺序表\n");
	if(seq_p == NULL)
	{
		printf("非法输入\n");
		return;
	}
	//assert(seq_p);
	int i = 0;
	for(; i<seq_p->size; i++)
	{
		printf("[%d] ", seq_p->arr[i]);
	}
	printf("\n");
	printf("\n");
}

//交换函数
void swap(int* a, int* b)
{
	int tmp = 0;
	tmp = *a;
	*a = *b;
	*b = tmp;
}

//比较函数
int cmp_shengxu(int* a, int* b)
{
	if(*a > *b)
	  return 1;
	else
	  return 0;
}

int cmp_jiangxu(int* a, int* b)
{
	if(*a < *b)
	  return 1;
	else
	  return 0;
}

//冒泡排序元素
void BubbleSort(SeqList* seq_p, int(*cmp)(DataType* a,DataType* b))
{
	printf("\n========%s========\n", __FUNCTION__);
	if(seq_p == NULL)
	{
		printf("非法输入\n");
		return;
	}
	int count = 0;
	for(; count < seq_p->size; count++)
	{
		int ctr = 0;
		for(; ctr<seq_p->size-1-count; ctr++)
		{
			if(cmp(&seq_p->arr[ctr], &seq_p->arr[ctr+1]) == 1)
			{
				swap(&seq_p->arr[ctr], &seq_p->arr[ctr+1]);
			}
		}
	}
	SeqListPrint(seq_p);
}

int main()
{
	SeqList mylist;
	SeqListInit(&mylist);
	SeqListTailInsert(&mylist, 9);
	SeqListTailInsert(&mylist, 6);
	SeqListTailInsert(&mylist, 7);
	SeqListTailInsert(&mylist, 1);
	SeqListTailInsert(&mylist, 4);
	SeqListTailInsert(&mylist, 3);
	//SeqListTailDelete(&mylist);
	//SeqListTailDelete(&mylist);
	//SeqListHeadInsert(&mylist, 2);
	//SeqListHeadInsert(&mylist, 1);
	//SeqListHeadInsert(&mylist, 0);
	//SeqListHeadDelete(&mylist);
	//SeqListHeadDelete(&mylist);
	//SeqListReadAnywhere(&mylist, 1);
	//SeqListAlterAnywhere(&mylist, 1, 7);
	//SeqListFindAnywhere(&mylist, 7);
	//SeqListInsertAnywhere(&mylist, 1, 6);
	BubbleSort(&mylist, cmp_shengxu);
	BubbleSort(&mylist, cmp_jiangxu);
	return 0;
}
