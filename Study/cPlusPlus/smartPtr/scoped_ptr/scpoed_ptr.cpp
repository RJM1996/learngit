#include <iostream>
using namespace std;


template<class T>
class ScopedPtr
{
public:
    // 1. 构造
    ScopedPtr(T* t_ptr)
        :m_ptr(t_ptr)
    {}
    // 2. 析构
    ~ScopedPtr()
    {
        delete m_ptr;
    }
    // 3. 重载 * ->
    T& operator* ()
    {
        return *m_ptr;
    }
    T* operator-> ()
    {
        return m_ptr;
    }
private:
    // 防止拷贝
    // 只声明拷贝构造和赋值, 不实现
    ScopedPtr(ScopedPtr<T>& sp);
    ScopedPtr<T>& operator= (ScopedPtr<T>& sp);

private:
    T* m_ptr;
};

void test()
{
    ScopedPtr<int> sp1(new int);
    *sp1 = 10;
    cout << *sp1 << endl;
}
