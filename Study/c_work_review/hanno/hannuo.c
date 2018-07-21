#include<stdio.h>
#include<math.h>
#include"hannuo.h"

void hannuo(int n, char A, char B, char C)
{
	int count = 0;
	if (n == 1)
	{
		printf("%c => %c\n", A, C);
	}
	else
	{
		hannuo(n-1, A,C,B);
		printf("%c => %c\n", A, C);
		hannuo(n-1, B,A,C);
	}
}
