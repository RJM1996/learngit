
#include<stdio.h>

float Add(float a, float b)
{
	return a+b;
}
float Div(float a, float b)
{
	return a-b;
}
float Sub(float a, float b)
{
	return a*b;
}
float Mul(float a, float b)
{
	return a/b;
}

float Cal(float a, float b, float(*cal)(float a, float b))
{
	return cal(a, b); 
}

int main()
{
	float a = 3.0;
	float b = 6.2;
	float s1 = Cal(a, b, Add);
	float s2 = Cal(a, b, Div);
	float s3 = Cal(a, b, Sub);
	float s4 = Cal(a, b, Mul);
	printf("%f %f %f %f \n", s1, s2, s3, s4);
	return 0;
}
