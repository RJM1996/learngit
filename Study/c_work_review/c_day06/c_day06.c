/*================================================================

# File Name: c_day06.c
# Author: rjm
# mail: rjm96@foxmail.com
# Created Time: 2018年04月28日 星期六 15时05分34秒

================================================================*/


#include <stdio.h>

//1.写一个函数返回参数二进制中 1 的个数 
//比如： 15 0000 1111 4 个 1 
//程序原型： 
//int count_one_bits(unsigned int value) 
//{ 
//// 返回 1的位数 
//} 

int count_one_bits(unsigned int value)
{
    int count = 0;
    int i = 32;
    unsigned bit = 1;
    while(i--)
    {
        if((value & bit) == 1)//和 1 进行按位与操作,如果等于1,证明value的最后一位是1
          count++;
        value = value >> 1;//将value右移一位,然后再和1与操作,证明第二位也是1,以此类推
    }
    return count;
}

//2.获取一个数二进制序列中所有的偶数位和奇数位，分别输出二进制序列。 
void odd_even_bit(unsigned int num)
{
    int odd_arr[16] = {0}; //定义两个数组, 一个存奇数位, 一个存偶数位
    int even_arr[16] = {0};
    int k = 1;
    int renum = num;
    for(int i=0; i<32; i++)
    {
        num = renum; //每次循环开始前先把num复原
        num = num >> i;
        if(( num & 1 ) == 1)
        {
            if(i%2 == 0)
            {
                odd_arr[i/2] = 1;
            }
            else
            {
                even_arr[i-k] = 1;
                k++;
            }
        }

        if(( num & 1 ) == 0)
        {
            if(i%2 == 0)
            {
                odd_arr[i/2] = 0;
            }
            else
            {
                even_arr[i-k] = 0;
                k++;
            }
        }
    }
    printf("奇数位\n");
    for(int i = 0; i<16; i++)
    {
        printf("%d ", odd_arr[i]);
    }
    printf("\n");
    printf("偶数位\n");
    for(int i = 0; i<16; i++)
    {
        printf("%d ", even_arr[i]);
    }
}

//3.输出一个整数的每一位。 
void _eachEvery(int num, int each)
{
    if(num == 0)
      return ;
    each = num%10;
    num = (num-each)/10;
    _eachEvery(num, each);
    printf("%d ", each);
}
void eachEvery(int num)
{
    int each = 0;
    _eachEvery(num, each);
}


//4.编程实现： 
//两个int（32位）整数m和n的二进制表达中，有多少个位(bit)不同？ 
//输入例子: 
//1999 2299 
//011111001111
//100011111011
//输出例子:7
int compareTwoInt(int m, int n)
{
    int i = 32;
    int count = 0;
    while(i--)
    {
        if((m & 1) != (n & 1))
          count++;
        m = m >> 1;
        n = n >> 1;
    }
    return count;
}


int main()
{
    printf("\n\n");
    int count = count_one_bits(4294967295);
    printf("count expected 32, actual %d\n", count);

    printf("\n\n");
    eachEvery(9527);

    printf("\n\n");
    odd_even_bit(99);

    printf("\n\n");
    int count1 = compareTwoInt(1999, 2299);
    printf("count1 expected 7, actual %d\n", count1);

    printf("\n\n\n");
    printf("\n\n\n");
    printf("\n\n\n");
    return 0;
}

