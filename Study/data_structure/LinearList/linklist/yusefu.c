
#include<stdio.h>

int yuesefu(int n,int m)
{
    if(n == 1)
    {
        return 0; //这里返回下标,从0开始，只有一个元素就是剩余的元素0

    }
    else
    {
        return (yuesefu(n-1,m) + m) % n; //我们传入的n是总共多少个数

    }

}
int main(void)
{
    int a = 0;
    int b = 0;
    printf("请输入人数和数字=> ");
    scanf("%d %d", &a, &b);
    yuesefu(a, b);
    //或者，直接循环迭代，求出来的result如上
    int result = 0;
    for(int i = 2;i <= a;i++)
    {
        result = (result+b) %i;
    }
    printf("survive = %d\n", result+1);
    return 0;
}


