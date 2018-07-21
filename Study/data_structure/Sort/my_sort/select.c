#include<stdio.h>

void swap(int*a,int*b)
{
	int temp;
	temp=*a;
	*a=*b;
	*b=temp;
}
void select_sort(int A[],int n)
{
	register int i,j,min,m;
	for(i=0;i<n-1;i++)
	{
		min=i;//查找最小值
		for(j=i+1;j<n;j++)
		{
			if(A[min]>A[j])
			{
				min=j;
			}
		}
		if(min!=i)
		{
			swap(&A[min],&A[i]);
		}
		printf("第%d趟排序结果为:\n",i+1);
		for(m=0;m<n;m++)
		{
			printf("%d ",A[m]);
		}
		printf("\n");
	}
}

int main()
{
	int A[] = {1,9,2,4,6,5,3,8,0,7};
	select_sort(A, 10);
	return 0;
}
