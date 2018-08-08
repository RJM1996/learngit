#include <iostream>
using namespace std;

template<class T>
class SharedPtr
{
public:
    // 1. 构造
    SharedPtr(T* t_ptr)
        :m_ptr(t_ptr)
    {
        m_pcount = new int(1);
    }
    // 2. 拷贝构造
    SharedPtr(const SharedPtr<T>& sp)
        :m_ptr(sp.m_ptr), m_pcount(sp.m_pcount)
    {
        ++(*m_pcount);
    }
    // 3. 赋值操作符重载
    // sp2 = sp1
    // A->m_next = B;
    SharedPtr<T>& operator= (SharedPtr<T>& sp)
    {
        if(m_ptr != sp.m_ptr)
        {
            if(--(*m_pcount) == 0)
            {
                cout<< "delete: " << m_ptr << " - " <<  m_pcount << endl;
                delete m_ptr;
                delete m_pcount;
            }
            m_ptr = sp.m_ptr;
            m_pcount = sp.m_pcount;
            ++(*m_pcount);
        }
        return *this;
    }
    // 4. 析构
    ~SharedPtr()
    {
        if(--(*m_pcount) == 0)
        {
            cout<< "delete: " << m_ptr << " - " <<  m_pcount << endl;
            delete m_ptr;
            delete m_pcount;
        }
        else
        {
            cout << "空间并未释放" << endl;
        }
    }
    // 5. 像指针一样操作
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
    int* m_pcount;
};

void Test01()
{
    SharedPtr<int> sp1(new int);
    SharedPtr<int> sp2(new int);
    sp2 = sp1;
    *sp2 = 100;
    cout << *sp1 << endl;
    cout << *sp2 << endl;
    SharedPtr<int> sp3(sp1);
    *sp3 = 200;
    cout << *sp3 << endl;
    cout << *sp2 << endl;
    cout << *sp1 << endl;
}

// 循环引用问题
struct ListNode
{
public:
    ListNode(int t_val)
        :val(t_val), m_next(NULL), m_prev(NULL)
    {}

    ~ListNode()
    {
        cout << "delete ListNode" << endl;
    }

public:
    int val;
    SharedPtr<ListNode> m_next;
    SharedPtr<ListNode> m_prev;
};

void Test02()
{
    // ListNode* node1 = new ListNode(1);
    // ListNode* node2 = new ListNode(1);
    // node1->m_next = node2;
    // node2->m_prev = node1;
    
    SharedPtr<ListNode> A(new ListNode(1));
    SharedPtr<ListNode> B(new ListNode(1));

    A->m_next = B; // B的引用计数+1, 变为2
    B->m_prev = A; // A的引用计数+1, 变为2

    // B 出作用域, 先析构, 引用计数-1, 变为1, 空间并未释放
    // A 出作用域, 后析构, 引用计数-1, 变为1, 空间也没释放

    SharedPtr<ListNode> C(NULL);
    A->m_next = C;
    B->m_prev = C;
}

#include <boost/shared_ptr.hpp>
void test_shared_ptr()
{
    boost::shared_ptr<int> shp1(new int(10));
    boost::shared_ptr<int> shp2(shp1);
    cout << *shp1 << endl;
    *shp1 = 100;
    cout << *shp2 << endl;
//     auto_ptr<int> ap1(new int(100));
//     unique_ptr<int> up1(new int(10));
    cout << shp1.use_count() << endl;
}

int main()
{
    // Test01();
    // Test02();
    test_shared_ptr();
    return 0;
}
