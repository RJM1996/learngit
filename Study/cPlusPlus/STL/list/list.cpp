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



int main()
{
    TestList();
    return 0;
}
