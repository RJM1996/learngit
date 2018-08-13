#pragma once
#include <fstream>
#include <string>
#include "huffmanTree.h"
using namespace std;

typedef long long LongType;
struct CharInfo
{
    char _ch;
    LongType _count;
    string _code;

    CharInfo operator+(const CharInfo& info)
    {
        CharInfo ret;
        ret._count = _count + info._count;
        return ret;
    }

    bool operator>(const CharInfo& info)
    {
        return _count > info._count;
    }
};

class FileCompress
{
public:
    FileCompress()
    {
        for(size_t i=0; i<256; i++)
        {
            _infos[i]._ch = i;
            _infos[i]._count = 0;
        }

    }
    void Compress(const char* file)
    {
        // 1. 统计字符出现的次数
        ifstream ifs( file );
        char ch;
        // while( ifs.get(ch) )
        while( ifs >> ch )
        {
            _infos[ch]._count++; // 统计次数
        }
        // 2. 构建哈夫曼数
        HuffmanTree<CharInfo> t(_infos, 256);
        

        
    }
    void Uncompress(const char* file);
private:
    CharInfo _infos[256];


};
