
#include "vector.h"

// 计算大小
size_t Vector::Size()
{
    return _finish - _first;
}
// 迭代器
DataType* Vector::begin()
{
    return _first;
}
DataType* Vector::end()
{
    return _finish;
}
// 计算容量
size_t Vector::Capacity()
{
    return _endofstorage - _first;
}
void Expand(size_t n)
{

}
// 尾插
void Vector::PushBack(DataType x)
{
    checkCapacity();
    Insert(end(), x);
}
// 尾删
void Vector::PopBack()
{
    DataType* pos = end();
    Erase(--pos);
}
// 一次开指定大小的空间
void Vector::Reserve(size_t n)
{
    if(n > Capacity())
    {
        DataType* new_first = new DataType[n];
        DataType* new_finish = new_first;
        for(DataType* tmp = begin(); tmp != end(); tmp++)
        {
            *new_first = *tmp;
            new_finish++;
        }
        delete[] _first;
        _first = new_first;
        _finish = new_finish;
        _endofstorage = n + _first;
    }
}
// 插入
void Vector::Insert(DataType* pos, const DataType& val)
{
    checkCapacity();
    for(DataType* tmp = end(); tmp != pos; --tmp)
    {
        *tmp = *(tmp-1);
    }
    *pos = val;
    _finish++;
}
// 删除
void Vector::Erase(DataType* pos)
{
    DataType* end_pos = end();
    for(DataType* tmp = pos; tmp != (--end_pos); tmp++)
    {
        *tmp = *(tmp + 1);
    }
    --_finish;
}
// 查找
size_t Find(DataType x)
{

}
// 检查容量, 扩容
void Vector::checkCapacity()
{
    if(_finish == _endofstorage)
    {
        DataType* new_first = new DataType[Size() * 2]; // 一次扩容至两倍
        DataType* new_finish = new_first;
        for(DataType* i = begin(); i != end(); i++) // 把旧的先拷贝过来
        {
            *new_first = *i;
            new_finish++;
        }
        delete[] _first; // 释放旧的
        _first = new_first;
        _finish = new_finish;
        _endofstorage = _first + Size() * 2;
    }
}

