
#include<stdio.h>
#include<string.h>
#include<stdlib.h>

#define TEST_HEAD printf("=====%s=====\n", __FUNCTION__);

//冒泡排序
void bubble_sort(int *arr, int len)
{
	TEST_HEAD 
	int i = 0;
	for(i=0; i<len-1; i++)
	{
		int j = 0;
		for(j=0; j<len-1-i; j++)
		{
			if(arr[j]>arr[j+1])
			{
				int tmp = 0;
				tmp = arr[j];
				arr[j] = arr[j+1];
				arr[j+1] = tmp;
			}
		}
		printf("第%d趟排序结果=>\n", i+1);
		for(int m=0; m<len; m++)
		{
			printf("%d ", arr[m]);
		}
		printf("\n");
	}
}

//选择排序
void select_sort(int* arr, int len)
{
	TEST_HEAD 
	int min = 0;
	int tmp = 0;
	for(int i=0; i<len-1; i++)
	{
		min = i;
		for(int j=i+1; j<len; j++)
		{
			if(arr[j]<arr[min])
			{
				min = j;
			}
		}
		tmp = arr[i];
		arr[i] = arr[min];
		arr[min] = tmp;

		printf("第%d趟排序结果=>\n", i+1);
		for(int m=0; m<len; m++)
		{
			printf("%d ", arr[m]);
		}
		printf("\n");
	}

}

void swap(int* a, int* b)
{
	int tmp = *a;
	*a = *b;
	*b = tmp;
}

//快速排序
void quick_sort(int* arr, int left, int right)
{
	if(left >= right)
	  return;
	int i = left;
	int j = right;
	int k = arr[left];
	while(i<j && k<=arr[j])
	  j--;
	arr[i] = arr[j];

	while(i<j && k>=arr[i])
	  i++;
	arr[j] = arr[i];
	
	k = arr[i];
	quick_sort(arr, left, i-1);
	quick_sort(arr, i+1, right);

}

void sort(int *arr, int len, void(*my_sort)())
{
	my_sort(arr, len);
	printf("\n");
}

int qsort_int_cmp(const int* a, const int* b)
{
	return *a>*b ? 1 : 0;
}

int main()
{
	int arr[] = {1,9,2,8,7,4,3,6,5,0};
	int len = sizeof(arr)/sizeof(arr[0]);
	sort(arr, len, bubble_sort);//冒泡排序

	int arr1[] = {1,9,2,8,7,4,3,6,5,0};
	int len1 = sizeof(arr1)/sizeof(arr1[0]);
	sort(arr1, len1, select_sort);//选择排序

	int arr2[] = {1,9,2,8,7,4,3,6,5,0};
	int len2 = sizeof(arr2)/sizeof(arr2[0]);
	int k = 0;
	printf("=====qsort=====\n");
    //void qsort(void*base,size_t num,size_t width,int(__cdecl*compare)(const void*,const void*));
	qsort(arr2, len2, sizeof(arr2[0]), (void*)qsort_int_cmp);//c库qsort函数
	for(k=0; k<len; k++)
	{
		printf("%d ", arr2[k]);
	}

	int arr3[] = {1,9,2,8,7,4,3,6,5,0};
	int len3 = sizeof(arr3)/sizeof(arr3[0]);

	printf("\n=====quick=====\n");
	quick_sort(arr, 0, 9);
	for(int s=0; s<10; s++)
	{
		printf("%d ", arr[s]);
	}
	printf("\n");

	printf("\n");
	return 0;
}
