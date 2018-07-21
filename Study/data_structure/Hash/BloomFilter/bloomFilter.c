/*================================================================

# File Name: bloomFilter.c
# Author: rjm
# mail: rjm96@foxmail.com
# Created Time: 2018年05月23日 星期三 08时54分38秒

================================================================*/

#include "bloomFilter.h"
#include <assert.h>

// 哈希函数
// 用来将一个字符串转为整数下标
size_t BKDR_Hash(const char* str)
{
    assert(str);
    size_t hash = 0;
    while(*str++)
    {
        hash = hash * 131 + *str;
    }
    return hash;
}
size_t SDBM_Hash(const char* str)
{
    assert(str);
    size_t hash = 0;
    while(*str++)
    {
        hash = hash * 65599 + *str;
    }
    return hash;
}

// 初始化
void BloomFilterInit(BloomFilter* bf)
{
    if(bf == NULL)
    {
        return ;
    }
    BitmapInit(&(bf->bitmap), BitmapMaxSize);
    bf->hash_func[0] = BKDR_Hash;
    bf->hash_func[1] = SDBM_Hash;
}
// 向布隆过滤器中加入一个字符串
void BloomFilterInsert(BloomFilter *bf, const char *str)
{
    if(bf == NULL)
      return ;
    assert(str);
    for(int i = 0; i < HashFuncMaxSize; i++)
    {
        uint64_t hash = bf->hash_func[i](str) % BitmapMaxSize;
        BitmapSet(&(bf->bitmap), hash);
    }
    return ;
}
// 查看布隆过滤器中是否存在一个字符串
int BloomFilterIsExist(BloomFilter *bf, const char *str)
{
    if(bf == NULL)
      return -1;
    assert(str);
    for(int i = 0; i < HashFuncMaxSize; i++)
    {
        uint64_t hash = bf->hash_func[i](str) % BitmapMaxSize;
        int ret = BitmapTest(&(bf->bitmap), hash);
        if(ret == 1)
        {
            return 1;
        }
    }
    return 0;
}
// 销毁布隆过滤器
void BloomFilterDestroy(BloomFilter *bf)
{
    if(bf == NULL)
      return ;
    for(int i = 0; i < HashFuncMaxSize; i++)
    {
        bf->hash_func[i] = NULL;
    }
    BitmapDestroy(&(bf->bitmap));
}


////////////////////////////////////////////////////
// 测试函数
////////////////////////////////////////////////////

void Test()
{
    BloomFilter bf;
    BloomFilterInit(&bf);
    BloomFilterInsert(&bf, "hello,world");
    BloomFilterInsert(&bf, "hello");
    BloomFilterInsert(&bf, "world");
    int ret = BloomFilterIsExist(&bf, "nihao");
    printf("ret expcted 0, actual %d\n", ret);
    ret = BloomFilterIsExist(&bf, "hello");
    printf("ret expcted 1, actual %d\n", ret);
    BloomFilterDestroy(&bf);
}

int main()
{
    Test();
    printf("\n\n\n");
    return 0;
}
