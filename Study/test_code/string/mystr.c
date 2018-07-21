
#include<stdio.h>
#include<assert.h>

//mystrcpy
char* mystrcpy(char* dst, char* src)
{
    assert(src);
    assert(dst);

    char* ret = dst;
    while(*dst++ == *src++);
    return ret;
}

//mystrstr
//strstr: 若str2 为str1 的子串, 则返回str2 在str1 第一次出现的地址
//        否则返回 NULL
char* mystrstr(const char* str1, const char* str2)
{
    char*cp = (char*)str1;
    char*s1,*s2;

    if(!*str2)
      return((char*)str1);

    while(*cp)
    {
        s1 = cp;
        s2 = (char*)str2;

        while(*s1&&*s2&&!(*s1-*s2))
          s1++,s2++;

        if(!*s2)
          return(cp);

        cp++;
    }
    return NULL;
}

int main()
{
    char* str1 = "zxc123y";
    char* str2 = "c12";
    char* str3 = "abc";

    char* ret1 = mystrstr(str1,str2);
    char* ret2 = mystrstr(str1,str3);
    if(ret1 != NULL)
    {
        printf("ret1: %s\n", ret1);
    }

    printf("ret2: %s\n", ret2);
    return 0;
}

//int main()
//{
//    char str[] = "hello,world";
//    char buf[256] = {0};
//    mystrcpy(buf, str);
//    printf("%s\n", buf);
//    return 0;
//}
