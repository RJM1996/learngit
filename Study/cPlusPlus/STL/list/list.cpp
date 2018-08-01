#include <iostream>
#include <list>
#include <algorithm>

using namespace std;

// 容器的公共打印函数
template<class container>
void printContainer(const container& s)
{
    typename container::const_iterator it = s.begin();
    while(it != s.end())
    {
        cout << *it << " ";
        ++it;
    }
    cout << endl;
}
// 反向打印
template<class container>
void printReverse(container& s)
{
    typename container::reverse_iterator re_it = s.rbegin();
    while(re_it != s.rend())
    {
        cout << *re_it << " ";
        ++ re_it;
    }
    cout << endl;
}

template<class T>
struct Less
{
    bool operator() (const T& l, const T& r)
    {
        return l < r;
    }
};
template<class T>
struct Greater
{
    bool operator() (const T& l, const T& r)
    {
        return l > r;
    }
};

void TestList()
{
    list<int> l1;
    l1.push_back(9);
    l1.push_back(5);
    l1.push_back(2);
    l1.push_back(7);
    printContainer(l1);
    // 反向迭代器
    list<int>::reverse_iterator re_it = l1.rbegin();
    while(re_it != l1.rend())
    {
        cout << *re_it << " ";
        re_it++;
    }
    cout << endl;
    list<int>::iterator pos = find(l1.begin(), l1.end(), 7);
    if(pos != l1.end())
    {
        l1.insert(pos, 99);
    }
    printContainer(l1);
    l1.erase(pos);
    printContainer(l1);

    // template <class RandomAccessIterator>
    // void sort (RandomAccessIterator first, RandomAccessIterator last);
    // template <class RandomAccessIterator, class Compare>
    // void sort (RandomAccessIterator first, RandomAccessIterator last, Compare comp);
    l1.sort(); // 默认升序
    printContainer(l1);
    l1.sort(Less<int>());
    printContainer(l1);
    l1.sort(Greater<int>());
    printContainer(l1);
    Less<int> less;
    cout << less(2, 3) << endl;
    cout << less(9, 3) << endl;
    l1.reverse(); // 逆置
    printContainer(l1);

    list<int> l2;
    l2.push_back(1);
    l2.push_back(2);
    l2.push_back(2);
    l2.push_back(2);
    l2.push_back(3);
    l2.push_back(2);
    l2.push_back(5);
    l2.push_back(2);
    l2.push_back(3);
    
    l2.unique(); // 只会去掉连续的重复
    // 先 sort 再 unique 
    l2.sort();
    l2.unique();
    printContainer(l2);

    // erase 导致迭代器失效
    list<int>::iterator it = l2.begin();
    while(it != l2.end())
    {
        if(*it % 2 == 0)
        {
            // l2.erase(it); // 这里 it 已经被释放了
            // 解决方案
            it = l2.erase(it);
        }
        else
        {
            ++it;
        }
        // ++it; // 再对 it 加加就出错了
    }
    printContainer(l2);
}

void TestList01()
{
    list<int> l1;
    list<int> l2(10, 1);
    int arr[] = {1, 2, 3, 4, 5, 6, 7};
    list<int> l3(arr, arr + sizeof(arr)/sizeof(arr[0]));
    list<int> l4(l3);
    cout << l1.size() << endl;
    cout << l2.size() << endl;
    cout << l3.size() << endl;
    cout << l4.size() << endl;
    // 正向打印
    printContainer(l1);
    printContainer(l2);
    printContainer(l3);
    printContainer(l4);
    // 反向打印
    printReverse(l1);
    printReverse(l2);
    printReverse(l3);
    printReverse(l4);
    // 头插 头删
    l1.push_front(9);
    l1.push_front(5);
    l1.push_front(2);
    l1.push_front(7);
    printContainer(l1);
    l1.pop_front();
    printContainer(l1);
    l1.pop_front();
    printContainer(l1);
    l1.pop_front();
    printContainer(l1);
    // 尾插 尾删
    l1.push_back(3);
    l1.push_back(6);
    l1.push_back(8);
    l1.push_back(5);
    printContainer(l1);
    l1.pop_back();
    printContainer(l1);
    l1.pop_back();
    printContainer(l1);
    l1.pop_back();
    printContainer(l1);
    l1.pop_back();
    printContainer(l1);
    // 任意位置插入
    list<int>::iterator pos = find(l1.begin(), l1.end(), 9);
    if(pos != l1.end())
    {
        // 默认是在 pos 之前插入,  返回值为插入元素的位置
        pos = l1.insert(pos, 100);
    }
    cout << *pos << endl;
    printContainer(l1);
    // 任意位置删除
    l1.erase(pos);

    list<int>::iterator pos1 = find(l3.begin(), l3.end(), 3);
    l3.erase(pos1);
    printContainer(l3);

    // 给 list 重新赋值
    l1.assign(10, 99);
    printContainer(l1);
    // 获取链表的第一个, 最后一个位置的元素
    printContainer(l3);
    cout << l3.front() << endl;
    cout << l3.back() << endl;
}

// 仿函数
class is_Odd {
public:
    bool operator() (int val) {
        return val & 0x01; /* 奇数 & 0x01 肯定是 true, 偶数 & 0x01 肯定是 false */
    }
} ;
class is_Even {
public:
    bool operator() (int val) {
        return !(val & 0x01); /* 奇数 & 0x01 肯定是 true, 偶数 & 0x01 肯定是 false */
    }
} ;

class Three {
public:
    bool operator() (int left, int right) {
        return (left + right) % 3 == 0;
    }
} ;

void TestList02()
{
    int arr[] = {1,2,3,4,5,6,7,8,9};
    list<int> l1(arr, arr+sizeof(arr)/sizeof(arr[0]));
    // printContainer(l1);
    // l1.remove(3);
    // printContainer(l1);
    // l1.remove_if(is_Odd());  // 如果是奇数就删除
    // printContainer(l1);
    // l1.remove_if(is_Even()); // 如果是偶数就删除
    // printContainer(l1);
    printContainer(l1);
    l1.unique(Three()); // 如果连续两个数的和是 3 的倍数, 就删除第二个数, 只保留第一个
    printContainer(l1);
}

void TestList03()
{
    list<int> l1;
    l1.push_back(1);
    l1.push_back(3);
    l1.push_back(5);
    l1.push_back(7);
    list<int> l2;
    l2.push_back(2);
    l2.push_back(4);
    l2.push_back(6);
    l2.push_back(8);
    // 将两个有序链表合并, 合并之后仍然有序
    l1.merge(l2); 
    printContainer(l1);
    // 反转链表
    l1.reverse();
    printContainer(l1);
}



int main()
{
    // TestList();
    // TestList01();
    // TestList02();
    TestList03();
    return 0;
}
