/*================================================================

# File Name: hello.c
# Author: rjm
# mail: rjm96@foxmail.com
# Created Time: 2018年05月08日 星期二 12时42分43秒

================================================================*/


// 写一个宏, 将一个数字的奇数位和偶数位交换
#define ODD_EVEN_SWAP(n) ((n&0x55555555)<<1)|((n&0xAAAAAAAA)>>1) 

// 写一个宏, 实现两个数中求较大值
#define MAX(m, n) (m > n ? m : n)

#include <stdio.h>
#include <stdlib.h>

//char *itoa(int num, char *str, int radix)
//{
//    /* 索引表 */
//    char index[] = "0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZ";
//    unsigned unum; /* 中间变量 */
//    int i = 0, j, k;
//    /* 确定unum的值 */
//    if(radix == 10 && num < 0) /* 十进制负数 */
//    {
//        unum = (unsigned) - num;
//        str[i++] = '-';
//    }
//    else unum = (unsigned)num; /* 其它情况 */
//    /* 逆序 */
//    do
//    {
//        str[i++] = index[unum % (unsigned)radix];
//        unum /= radix;
//    }
//    while(unum);
//    str[i] = '\0';
//    /* 转换 */
//    if(str[0] == '-') k = 1; /* 十进制负数 */
//    else k = 0;
//    /* 将原来的“/2”改为“/2.0”，保证当num在16~255之间，radix等于16时，也能得到正确结果 */
//    char temp;
//    for(j = k; j <= (i - k - 1) / 2.0; j++)
//    {
//        temp = str[j];
//        str[j] = str[i - j - 1];
//        str[i - j - 1] = temp;
//    }
//    return str;
//}

int main()
{
    //printf("file:%s line:%d\n", __FILE__, __LINE__);
    //printf("time:%s date:%s\n", __TIME__, __DATE__);
    //printf("STDC:%d", __STDC__);

    int i = 9;
    char s[10];

    itoa(i, s, 2);
    printf("%d\n", i); 
    printf("%s\n", s);

    int ret = ODD_EVEN_SWAP(i);

    itoa(ret, s, 2);
    printf("%d\n", ret); 
    printf("%s\n", s);

    
    int a = 100;
    int b = 120;
    int max = MAX(a, b);
    printf("max = %d\n", max);

    return 0;
}

