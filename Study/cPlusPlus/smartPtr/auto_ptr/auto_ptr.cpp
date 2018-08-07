#include <iostream>
#include <vector>
using namespace std;

template<class T>
class AutoPtr
{
public:
    // 1. 构造
    AutoPtr(T* t_ptr)
        :m_ptr(t_ptr)
    {}
    // 2. 拷贝构造
    //    管理权转让
    // ap3(ap2)
    AutoPtr(AutoPtr& ap)
        :m_ptr(ap.m_ptr)
    {
        ap.m_ptr = NULL;
    }
    // 3. 赋值操作符重载
    // ap2 = ap1
    // ap2 operator= (ap1)
    AutoPtr& operator= (AutoPtr& ap)
    {
        if(ap.m_ptr != m_ptr)
        {
            if(m_ptr != NULL)
            {
                cout << "delete: " << m_ptr << endl;
                delete m_ptr;
            }
            m_ptr = ap.m_ptr;
            ap.m_ptr = NULL;
        }
        return *this;
    }
    // 4. 析构
    ~AutoPtr()
    {
        if(m_ptr != NULL)
        {
            cout << "delete: " << m_ptr << endl;
            delete m_ptr;
        }
    }

    // 变得像指针一样
    // 重载 * ->
    T& operator* ()
    {
        return *m_ptr;
    }
    T* operator-> ()
    {
        return m_ptr;
    }

private:
    T* m_ptr;
};

struct AA
{
    int _a1;
    int _a2;
};

void Test01()
{
    AutoPtr<int> ap1(new int);
    *ap1 = 10;
    cout << *ap1 << endl;

    AutoPtr<AA> ap2(new AA);
    (*ap2)._a1 = 20;
    ap2->_a2 = 30;
    cout << ap2->_a1 << endl;
    cout << ap2->_a2 << endl;

    vector<int> v;
    try
    {
        v.at(1);
    }
    catch(exception& e)
    {
        cout << "越界了" << endl;
    }
}

void Test02()
{
    // ap1.m_ptr 指向一块 int 大小的空间
    AutoPtr<int> ap1(new int);
    // 用 ap1 拷贝构造 ap2, 相当于把管理权转移给 ap2 了
    // ap1.m_ptr 就指向 NULL 了
    AutoPtr<int> ap2 = ap1;
    // ap2 再把管理权转让给 ap3
    AutoPtr<int> ap3(ap2);

    // 会导致段错误
    // *ap1 = 10;
    // *ap2 = 20;
    // cout << *ap1 << " " << *ap2 << endl;
    *ap3 = 100;
    cout << *ap3 << endl;

    // ap3 把管理权转让给 ap2
    ap2 = ap3;
    *ap2 = 200;
    cout << *ap2 << endl;
    // ap2 把管理权转让给 ap1
    ap1 = ap2;
    *ap1 = 300;
    cout << *ap1 << endl;
}

void Test03()
{
    AutoPtr<int> ap1(new int);
    AutoPtr<int> ap2(new int);
    ap1 = ap2;
}


int main()
{
    // Test01();
    // Test02();
    Test03();
    return 0;
}
