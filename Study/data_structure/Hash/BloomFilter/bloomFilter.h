/*================================================================

# File Name: bloomFilter.h
# Author: rjm
# mail: rjm96@foxmail.com
# Created Time: 2018年05月23日 星期三 08时54分52秒

================================================================*/


// 布隆过滤器
#pragma once
#include <stdio.h>
#include "bitmap.h"

#define HashFuncMaxSize 2
#define BitmapMaxSize 1000

typedef size_t (*HashFunc)(const char *);

typedef struct BloomFilter {
    Bitmap bitmap;
    HashFunc hash_func[HashFuncMaxSize];
} BloomFilter;

void BloomFilterInit(BloomFilter *bf);

void BloomFilterInsert(BloomFilter *bf, const char *str);

int BloomFilterIsExist(BloomFilter *bf, const char *str);

void BloomFilterDestroy(BloomFilter *bf);

// 按照当前的设计, 是不允许删除的.
