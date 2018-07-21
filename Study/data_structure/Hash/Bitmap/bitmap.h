/*================================================================

# File Name: bitmap.h
# Author: rjm
# mail: rjm96@foxmail.com
# Created Time: 2018年05月22日 星期二 16时30分58秒

================================================================*/

#pragma once


#include <stdio.h>
#include <stdlib.h>
#include <inttypes.h>
#include <string.h>

#define TEST_HEAD printf("\n=======================%s==================\n", __FUNCTION__)


typedef uint64_t BitmapType;

typedef struct Bitmap {
    BitmapType* data; // 数组
    uint64_t capacity; // 需要表示的位数
                       // 例如:要表示100位
                       // 需要的数组元素个数为 
                       // (100 / (sizeof(uint64_t)*8)) + 1
                       // 即为 2 个元素
} Bitmap;

// 初始化
void BitmapInit(Bitmap* bm, uint64_t bits);

// 给某一位设置为 1
void BitmapSet(Bitmap* bm, uint64_t bits);

// 给某一位设置为 1
void BitmapUnset(Bitmap* bm, uint64_t bits);

// 给所有位设置为 1
void BitmapAllSet(Bitmap* bm);

// 给所有位设置为 0
void BitmapAllUnset(Bitmap* bm);

// 测试某一位是否为 1
uint64_t BitmapTest(Bitmap* bm, uint64_t bits);

// 销毁
void BitmapDestroy(Bitmap* bm);
