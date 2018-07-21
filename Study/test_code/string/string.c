
#include<stdio.h>
#include<string.h>
#include<assert.h>

#define Test_Head printf("=====%s=====\n", __FUNCTION__);

//strcpy
char* mystrcpy(char* dst, char* src)
{
    assert(src != NULL);
    assert(dst != NULL);

    char* ret = dst;
    while(*src != 0)
    {
        *dst = *src; 
        dst++, src++;
    }
    return ret;
}

//strlen
size_t mystrlen(const char* str)
{
    assert(str != NULL);

    const char* p = str;
    size_t count = 0;
    while(*p != 0)
    {
        p++;
        count++;
    }
    return count;
}

//strcat
char* mystrcat(char* dst, const char* src)
{
    assert(dst != NULL);
    assert(src != NULL);

    char* ret = dst;
    while(*dst != 0)
    {
        dst++;
        if(*dst == 0)
        {
            while(*src != 0)
            {
                *dst = *src;
                dst++, src++;
            }
        }
    }
    return ret;
}

//strstr
char* mystrstr(char* str1, const char* str2)
{
    assert(str1 != NULL);
    assert(str2 != NULL);

    if(*str2 == 0)
      return str1;
    char *bp;
    const char* sp;
    while (*str1 != 0)
    {
        bp = str1;
        sp = str2;
        do
        {
            if(*sp == 0)
              return str1;

        } while (*bp++ == *sp++);
        str1++;
    }
    return NULL;

}

//strchr
char* mystrchr(char* str, char c)
{
    assert(str != NULL);

    while(*str != 0)
    {
        if(*str == c)
        {
            return str;
        }
        str++;
    }
    return NULL;
}

//strcmp
int mystrcmp(char* str1, char* str2)
{
    assert(str1 != NULL);
    assert(str2 != NULL);

    while(*str1 != 0 && *str2!= 0)
    {
        if(*str1 > *str2)
          return 1;
        if(*str1 < *str2)
          return -1;
        str1++, str2++;
    }
    return 0;
}

//memcpy
void* mymemcpy(void* dst, void* src, size_t n)
{
    assert(dst != NULL);
    assert(src != NULL);

    void* ret = dst;
    while(n--)
    {
        *(char*)dst = *(char*)src;
        (char*)dst++, (char*)src++;
    }
    return ret;
}

//memmove用于从src拷贝count个字节到dest
//如果目标区域和源区域有重叠的话，memmove能够保证源串在被覆盖之前将重叠区域的字节拷贝到目标区域中
//但复制后src内容会被更改。但是当目标区域与源区域没有重叠则和memcpy函数功能相同
void* mymemmove(void* dst, void* src, size_t n)
{
    assert(dst != NULL);
    assert(src != NULL);

    char* p_dst = (char*)dst;
    char* p_src = (char*)src;

    if(p_dst <= p_src && p_dst >= p_src+n)//内存没有重叠时
    {
        while(n--)
        {
            *p_dst = *p_src;
            p_dst++, p_src++;
        }
    }
    else//内存有重叠时
    {
        while(n--)
        {
            *(p_dst+n) = *(p_src+n);
        }
    }
    return dst;
}
/////////////////////////////////////////
//测试函数
/////////////////////////////////////////

void TestMemmove()
{
    Test_Head;
    char str1[] = "hello, world";
    char str2[128] = {0};
    char* ret = mymemmove(str2, str1, strlen(str1)+1);
    printf("str2 = %s\n", ret);
}

void TestMemcpy()
{
    Test_Head;
    char src[] = "hello,world";
    char dst[40];
     
    char* ret = mymemcpy(dst, src, 6);
    printf("ret = %s\n", ret);
}
void TestStrcmp()
{
    Test_Head;
    char str1[] = "hello";
    char str2[] = "hello";

    int ret = mystrcmp(str1, str2);
    if(ret > 0)
    {
        printf("str1 > str2\n");
    }
    else if(ret < 0)
    {
        printf("str1 < str2\n");
    }
    else
    {
        printf("str1 = str2\n");
    }
}
void TestStrchr()
{
    Test_Head;
    char str[] = "hello,world";
    char c = 'o';
    char* ret = mystrchr(str, c);
    printf("ret = %s\n", ret);
}

void TestStrstr()
{
    Test_Head;
    char str1[] = "hello,world";
    char str2[] = "lo";
    char* ret = mystrstr(str1, str2);
    printf("ret = %s\n", ret);
}

void TestStrcat()
{
    Test_Head;
    char str1[128] = "hello,";
    char str2[] = "world";
    mystrcat(str1, str2);
    printf("str1 = %s\n", str1);
}
void TestStrlen()
{
    Test_Head;
    char str[] = "hello,world";
    size_t len = mystrlen(str);
    printf("str len = %d\n", len);
}
void TestStrcpy()
{
    Test_Head;
    char str1[] = "hello,world";
    char str2[256];
    mystrcpy(str2, str1);
    printf("str2 = %s\n", str2);
}

int main()
{
    TestStrcpy();
    TestStrlen();
    TestStrcat();
    TestStrstr();
    TestStrchr();
    TestStrcmp();
    TestMemcpy();
    TestMemmove();
    printf("\n\n");
    printf("\n\n");
    printf("\n\n");
    printf("\n\n");
    printf("\n\n");
    printf("\n\n");
    return 0;
}
