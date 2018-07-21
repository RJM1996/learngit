
#include<stdio.h>
#include<malloc.h>
#include<string.h>

int main()
{
    char str[256];
    char* ret = NULL;
    int max = 0;
    int count = 0;
    while(scanf("%s", str) != EOF)
    {
        char* cur = str;
        while(*cur != '\0')
        {
            // cur 不指向数字就往后走
            while((*cur) < 48 || (*cur) > 57)
            {
                cur++;
            }
            // 走到这 , 说明 cur 指向数字
            // *cur = '\0';
            char* ptr = cur;
            // 从这开始 将这个数字字符串先保存起来
            char* poss = ptr;

            count = 0; // 用来记录数字字符串的长度
            while((*ptr) >= 48 && (*ptr) <= 57)
            {
                count++;
                ptr++;
            }
            if(count > max)
            {
                max  = count;
                ret = poss;
            }
            // 到这里说明 ptr 指向非数字
            cur = ptr; // 又从这里开始找数字字符串
        }
        // printf("max = %d\n", max);
        char* res = (char*)malloc(max + 1);
        strncpy(res, ret, max);
        res[max+1] = '\0';
        printf("%s\n", res);
        free(res);
        res = NULL;
    }
}
