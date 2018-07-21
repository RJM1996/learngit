#include <stdio.h>
#include <assert.h>

int findNumber(int arr[], int size)
{
	if (arr == NULL)
	{
		return 0;
	}
	int num = 0;
	int to_find = 0;
	int count = 0;
	int max_count = 0;
	for (int i = 0; i < size; i++)
	{
		to_find = arr[i];
		count = 0;
		for (int j = 0; j < size; j++)
		{
			if (to_find == arr[j])
			{
				count++;
			}
		}
		if (count > max_count)
		{
			max_count = count;
			num = to_find;
		}
	}
	if (max_count > size / 2)
	{
		return num;
	}
	return 0;
}

char FindFirstCh(char* str)
{
	assert(str);
	// asdfasdfo
	char* ptr = str;  //ptr Ö¸Ïò a
	char* qtr = str;
	int count = 0;
	while (*qtr != '\0')
	{
		if (*ptr == *qtr)
		{
			count++;
			if (count == 2)
			{
				ptr++;
				qtr = str;
				count = 0;
			}
			else
			{
				qtr++;
			}
		}
		else
		{
			qtr++;
		}
	}
	if (count == 1)
	{
		char to_find = *ptr;
		return to_find;
	}
	return -1;		
}

int main()
{
	int arr[] = { 1,2,3,2,2,2,5,4,2 };
	int size = sizeof(arr) / sizeof(arr[0]);
	int ret = findNumber(arr, size);
	printf("%d\n", ret);

//    char str[10];
//    gets(str);
//	//char* str = "asdfasdfo";
//	//char* str1 = "acabb";
//	char ch = FindFirstCh(str);
//	printf("%c\n", ch);
	return 0;
}
