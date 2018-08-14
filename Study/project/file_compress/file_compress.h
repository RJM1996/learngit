#pragma once
#include <fstream>
#include <string>
#include <algorithm>
#include <assert.h>
#include "huffmanTree.h"

using namespace std;

typedef long long LongType;

struct CharInfo
{
    char _ch;        // 字符
    LongType _count; // 字符出现的次数
    string _code;    // 字符的编码

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

    bool operator!= (const CharInfo& info)
    {
        return _count != info._count;
    }
};

class FileCompress
{
    typedef HuffmanTreeNode<CharInfo> Node;
public:
    FileCompress()
    {
        for(size_t i=0; i<256; i++)
        {
            _infos[i]._ch = i;
            _infos[i]._count = 0;
        }
    }

    // 压缩
    void Compress(const char* file)
    {
        // 1. 统计字符出现的次数
        ifstream ifs( file ); // 打开文件
        char ch;
        // while( ifs.get(ch) )
        while( ifs >> ch )
        {
            _infos[(unsigned char)ch]._count++; // 统计次数
        }
        // 2. 构建哈夫曼数
        CharInfo invaild;
        invaild._count = 0;
        HuffmanTree<CharInfo> t(_infos, 256, invaild); // 根据字符信息构建哈弗曼树

        // 3. 生成哈夫曼编码
        //    编码存到 infos
        GetHuffmanCode(t.getRoot());

        // 4. 压缩(将源文件的内容替换为编码后的内容)
        string CompressFile = file;
        CompressFile += ".huffman";
        ofstream ofs(CompressFile.c_str());

        ifs.clear();
        ifs.seekg(0); // 把文件指针移到最开始
        char value = 0;
        int pos = 0;
        while(ifs >> ch)
        {
            string& code = _infos[(unsigned char)ch]._code;
            for(size_t i = 0; i < code.size(); i++, ++pos)
            {
                if(code[i] == '1')
                {
                    value |= (1 << pos);
                }
                else if(code[i] == '0')
                {
                    value &= ~(1 << pos);
                }
                else
                {
                    assert(false);
                }

                if(pos == 8)
                {
                    ofs << value;
                    pos = 0;
                    value = 0;
                }
            } // 一个字节处理完
        } // 源文件读结束
    } // 函数结束


    // 获取哈夫曼编码
    void GetHuffmanCode(Node* root)
    {
        if(root == NULL)
            return ;
        if(root->_left == NULL &&
           root->_right == NULL) // 此时 root 为叶子节点
        {
            string& code = _infos[(unsigned char)root->_w._ch]._code;
            Node* cur = root;
            Node* parent = cur->_parent;
            while(parent != NULL)
            {
                if(cur == parent->_left) // 哈夫曼编码, 左 0 右 1
                {
                    code += '0';
                }
                else
                {
                    code += '1';
                }
                cur = parent;
                parent = parent->_parent;
            }
            reverse(code.begin(), code.end());
            return ;
        }
        GetHuffmanCode(root->_left);
        GetHuffmanCode(root->_right);
    }

    void Uncompress(const char* file);
private:
    CharInfo _infos[256];
};

void TestCompress()
{
    FileCompress fc;
    fc.Compress("input.txt");
}
