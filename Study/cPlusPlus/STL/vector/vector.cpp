
#include <iostream>
#include <vector>
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

// 四个构造函数
// 1. explicit vector (const allocator_type& alloc = allocator_type());
// 2. explicit vector (size_type n, const value_type& val = value_type(),
//                     const allocator_type& alloc = allocator_type());
// 3. template <class InputIterator>
//    vector (InputIterator first, InputIterator last,
//            const allocator_type& alloc = allocator_type());
// 4. vector (const vector& x);
void TestVector()
{
    vector<int> first;
    vector<int> second (4, 100);
    vector<int> third (second.begin(), second.end());
    vector<int> fourth (third);
    printContainer(fourth);

    // template <class InputIterator>
    // void assign (InputIterator first, InputIterator last);
    //
    // void assign (size_type n, const value_type& val);
    first.assign(7, 99);
    printContainer(first);
    fourth.assign(4, 88);
    printContainer(fourth);
    int arr[] = {1, 5, 9};
    third.assign(arr, arr+3);
    printContainer(third);

    // reference at (size_type n);
    // const_reference at (size_type n) const;
    for(size_t i=0; i<fourth.size(); i++)
    {
        fourth.at(i) = i;
    }
    // fourth.at(10) = 100; // 会检查越界
    // fourth[10] = 100;    // 不会检查越界
    printContainer(fourth);
    int ret = fourth.back() - fourth.front(); // back:3 - front:0 = 3
    cout << ret << endl;

    cout << fourth.size() << endl;
    cout << fourth.capacity() << endl;
    
    // void resize (size_type n, value_type val = value_type());
    fourth.resize(10, 66);
    printContainer(fourth);

    // void reserve (size_type n);
    fourth.reserve(100);
    cout << fourth.size() << endl;
    cout << fourth.capacity() << endl;

    // 迭代器失效
    second.clear();
    second.push_back(9);
    second.push_back(5);
    second.push_back(2);
    second.push_back(6);
    second.push_back(7);
    vector<int>::iterator it = second.begin();
    while(it != second.end())
    {
        if(*it % 2 == 0)
        {
            second.erase(it);
        }
        ++it; // 6 会被跳过
    }
    printContainer(second);
    second.clear();
    second.push_back(9);
    second.push_back(5);
    second.push_back(2);
    second.push_back(6);
    second.push_back(7);
    it = second.begin();
    while(it != second.end())
    {
        if(*it % 2 == 0)
        {
            it = second.erase(it); // erase 有返回值, 指向被删除元素的下一个元素
            // cout << *it << endl;
        }
        else 
        {
            ++it; // 解决方案
        }
    }
    printContainer(second);
}



int main()
{
    TestVector();
    return 0;
}
