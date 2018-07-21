
#include <stdio.h>


// m 级阶梯 , 一次可以走 1 步 或者 2 步 , 求有几种不同走法
// m <= 40
int main()
{
    int s[41] = {0};
    s[1] = 0;
    s[2] = 1;
    s[3] = 2;
    s[4] = 3;
    int i = 0;
    int m = 0;
    int n = 0;
    for(i=4; i<41; i++)
    {
        s[i] = s[i-1] + s[i-2];
    }
    scanf("%d", &n);
    while(n--)
    {
        scanf("%d", &m);
        printf("%d\n", s[m]);
    }
}
