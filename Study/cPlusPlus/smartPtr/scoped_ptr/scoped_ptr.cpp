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
        cout << "delete: " << m_ptr << endl;
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
    // 4. 重载 []
    T& operator[] (int index)
    {
        return m_ptr[index];
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
    ScopedPtr<int> sp2(new int);
    // 不允许拷贝和赋值
    // ScopedPtr<int> sp3(sp1);
    // sp2 = sp1;
    sp1[0] = 100;
}

int main()
{
    test();
    return 0;
}
