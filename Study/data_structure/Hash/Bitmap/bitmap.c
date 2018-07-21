/*================================================================

# File Name: bitmap.c
# Author: rjm
# mail: rjm96@foxmail.com
# Created Time: 2018年05月22日 星期二 16时30分48秒

================================================================*/


#include "bitmap.h"

uint64_t DataSize(uint64_t capacity)
{
    return capacity / (sizeof(BitmapType)*8) + 1;
}

// 初始化
void BitmapInit(Bitmap* bm, uint64_t bits)
{
    if(bm == NULL)
      return ;
    bm->capacity = bits;
    uint64_t size = DataSize(bm->capacity);
    bm->data = (BitmapType*)malloc(sizeof(BitmapType)*size);
    memset(bm->data, 0x0, sizeof(BitmapType)*size);
}
// 给某一位设置为 1
void BitmapSet(Bitmap* bm, uint64_t bits)
{
    if(bm == NULL)
      return ;
    // 例如设置第 50 位为 1, 那么元素下标为 index
    // index = 50/64 = 0
    // 即要设置的位在第一个元素上
    // 所以就是把第一个元素的第50位 置为1
    uint64_t index = bits / (sizeof(BitmapType)*8);
    // 如果元素下标超过了capacity, 直接返回
    if(index >= bm->capacity)
      return ;
    uint64_t offset = bits % (sizeof(BitmapType)*8);
    bm->data[index] |= (0x1ul << offset);
}
// 给所有位设置为 1
void BitmapAllSet(Bitmap* bm)
{
    if(bm == NULL)
      return ;
    uint64_t size = DataSize(bm->capacity);
    memset(bm->data, 0xff, sizeof(BitmapType)*size);
}
// 给某一位设置为 0
void BitmapUnset(Bitmap* bm, uint64_t bits)
{
    if(bm == NULL)
      return ;
    // 例如设置第 50 位为 1, 那么元素下标为 index
    // index = 50/64 = 0
    // 即要设置的位在第一个元素上
    // 所以就是把第一个元素的第50位 置为1
    uint64_t index = bits / (sizeof(BitmapType)*8);
    // 如果元素下标超过了capacity, 直接返回
    if(index >= bm->capacity)
      return ;
    uint64_t offset = bits % (sizeof(BitmapType)*8);
    bm->data[index] &= ~(0x1ul << offset);
}
// 给所有位设置为 0
void BitmapAllUnset(Bitmap* bm)
{
    if(bm == NULL)
      return ;
    uint64_t size = DataSize(bm->capacity);
    memset(bm->data, 0x0, sizeof(BitmapType)*size);
}
// 测试某一位是否为 1
uint64_t BitmapTest(Bitmap* bm, uint64_t bits)
{
    if(bm == NULL)
      return 0;
    uint64_t index = bits / (sizeof(BitmapType)*8);
    if(index >= bm->capacity)
      return 0;
    uint64_t offset = bits % (sizeof(BitmapType)*8);
    uint64_t ret = bm->data[index] & (0x1ul << offset);
    return ret != 0 ? 1 : 0;
}
// 销毁
void BitmapDestroy(Bitmap* bm)
{
    if(bm == NULL)
      return ;
    bm->capacity = 0;
    free(bm->data);
    bm->data = NULL;
}



////////////////////////////////////
// 测试函数
////////////////////////////////////

void TestInit()
{
    TEST_HEAD;
    Bitmap bm;
    BitmapInit(&bm, 100);
}
void TestSet()
{
    TEST_HEAD;
    Bitmap bm;
    BitmapSet(&bm, 50);
    uint64_t ret = BitmapTest(&bm, 50);
    printf("ret exptcted 1, actual %llu\n", ret);
}
void TestUnset()
{
    TEST_HEAD;
    Bitmap bm;
    BitmapUnset(&bm, 50);
    uint64_t ret = BitmapTest(&bm, 50);
    printf("ret exptcted 0, actual %llu\n", ret);
}
void TestAllSet()
{
    TEST_HEAD;
    Bitmap bm;
    BitmapAllSet(&bm);
    uint64_t ret = BitmapTest(&bm, 0);
    printf("ret exptcted 1, actual %llu\n", ret);
    ret = BitmapTest(&bm, 99);
    printf("ret exptcted 1, actual %llu\n", ret);
}
void TestAllUnset()
{
    TEST_HEAD;
    Bitmap bm;
    BitmapAllUnset(&bm);
    uint64_t ret = BitmapTest(&bm, 0);
    printf("ret exptcted 0, actual %llu\n", ret);
    ret = BitmapTest(&bm, 99);
    printf("ret exptcted 0, actual %llu\n", ret);
}
void TestDestroy()
{
    TEST_HEAD;
    Bitmap bm;
    BitmapAllSet(&bm);
    uint64_t ret = BitmapTest(&bm, 0);
    printf("ret exptcted 1, actual %llu\n", ret);
    ret = BitmapTest(&bm, 99);
    printf("ret exptcted 1, actual %llu\n", ret);
    BitmapDestroy(&bm);
    printf("\n销毁位图\n");
    ret = BitmapTest(&bm, 99);
    printf("ret exptcted 0, actual %llu\n", ret);
}

int main()
{
    TestInit();
    TestSet();
    TestUnset();
    TestAllSet();
    TestAllUnset();
    TestDestroy();
    printf("\n");
    printf("\n");
    printf("\n");
    printf("\n");
    return 0;
}
