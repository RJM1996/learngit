
#pragma once

#include <iostream>
#include <algorithm>
#include <stdio.h>

using namespace std;

typedef int DataType;

class Vector
{
public:
    // 1.构造
    Vector(size_t n = 3) // 初始给 3 个元素的容量
        :_first(new DataType(n)), 
         _finish(_first),
         _endofstorage(_first + n)
    {}
    // 2.拷贝构造
    Vector(const Vector &v)
    {
        if(v._finish - v._first > _finish - _first)
        {
            delete[] _first;
            _first = new DataType[v._finish - v._first];
            _finish = _first;
        }
        for(DataType* tmp = v. _first; tmp != v._finish; tmp++) // 从 v 的first遍历到finish
        {
            *_finish = *tmp;
            _finish++;
        }
        _endofstorage = _finish;
    }

    // 3.赋值操作符的重载
    Vector& operator= (Vector& v)
    {
        if(this != &v)
        {
            swap(_first, v._first);
            swap(_finish, v._finish);
            swap(_endofstorage, v._endofstorage);
        }
        return *this;
    }

    // 4.析构
    ~Vector()
    {
        if(_first)
        {
            delete[] _first;
        }
        _first = NULL;
        _finish = NULL;
        _endofstorage = NULL;
    }
    // 5.随机访问 [] 重载
    DataType operator[] (size_t i)
    {
        return _first[i];
    }
    size_t Size();
    size_t Capacity();
    DataType* begin();
    DataType* end();
    void PushBack(DataType x);
    void PopBack();
    void Reserve(size_t n);
    void Insert(DataType* pos, const DataType& val);
    void Erase(DataType* pos);
    size_t Find(DataType x);
    bool Empty();
private:
    void checkCapacity(); // 检查容量, 扩容

    DataType* _first; // 数据存放开始的位置
    DataType* _finish; // 数据存放结束的位置 + 1
    DataType* _endofstorage; // 容量的最后一个位置
};
