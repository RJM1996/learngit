
#pragma once

#include <iostream>

using namespace std;

typedef int DataType;

class Vector
{
public:
    // 1.无参的构造
    Vector()
    {

    }
    // 2.拷贝构造
    Vector(const Vector &v)
    {

    }
    // 3.赋值操作符的重载
    Vector &operator= (const Vector &v)
    {

    }
    // 4. 析构
    ~Vector()
    {

    }
    size_t Size();
    size_t Capacity();
    void Expand(size_t n);
    void PushBack(DataType x);
    void Reserve(size_t n);
    void PopBack();
    void Insert(size_t pos, DataType x);
    void Erase(size_t pos);
    size_t Find(DataType x);
private:
    DataType *_first;
    DataType *_finish;
    DataType *_endofstorage;
};
