/*================================================================

# File Name: test.c
# Author: rjm
# mail: rjm96@foxmail.com
# Created Time: 2018年05月24日 星期四 17时12分18秒

================================================================*/



#include <stdio.h>
#include <assert.h>

void TurnOutSting(char* str, int len, int pos)
{
    assert(str);
    char* ptr = str;
    for(int i=0; i<=pos; i++)
    {
        ptr++;
    }
    // 例如: abcdefg pos = 4
    // 此时ptr指向f, 就是要将abcde移到fg后面
    char new_str[100];
    int i = 0;
    while(*ptr != '\0')
    {
        new_str[i] = *ptr;
        i++;
        ptr++;
    }
    ptr = str;
    pos += 1;
    while(pos--)
    {
        new_str[i] = *ptr;
        i++, ptr++;
    }
    new_str[i] = 0;
    printf("%s\n", new_str);
}

int main()
{
    char str[10];
    int len = 0;
    int pos = 0;
    scanf("%s", str);
    scanf("%d", &len);
    scanf("%d", &pos);
    TurnOutSting(str, len, pos);
    return 0;
}
