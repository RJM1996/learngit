#include <iostream>
#include <set>

using namespace std;

template<class container>
void printContainer(container& s)
{
    typename container::const_iterator it = s.begin();
    while(it != s.end())
    {
        cout << *it << " ";
        ++it;
    }
    cout << endl;
}

bool funcmp(int l, int r)
{
    return l < r;
}

struct classcomp
{
    bool operator() (const int& l, const int& r) const
    {
        return l < r;
    }
};

void TestSet01()
{
    // 构造
    set<int> first;
    int arr[] = {1, 3, 5, 7, 9};
    set<int> second(arr, arr + sizeof(arr)/sizeof(arr[0])); // 通过数组构造
    set<int> third(second.begin(), second.end());
    set<int> fourth(third);
    printContainer(third);


    // 插入
    first.insert(2);
    first.insert(4);
    first.insert(6);
    first.insert(8);
    printContainer(first);
    cout << "插入相同元素之前的大小: " << first.size() << endl;
    first.insert(6); // set 无法插入相同的 val
    printContainer(first);
    cout << "插入相同元素之后的大小: " << first.size() << endl;
    first.insert(arr, arr+4); // 将 arr[0] ~ arr[3] 的元素插入
    printContainer(first);

    // 查找
    set<int>::iterator it;
    it = first.find(0);
    if(it != first.end())
    {
        cout << *it << endl;
    }
    else
    {
        cout << *it << endl; 
        cout << "不存在" << endl;
    }

    // it = first.lower_bound(10);
    // cout << *it << endl; 
    // it = first.upper_bound(-1);
    // cout << *it << endl; 
    
    typedef set<int, int>::iterator Iter;
    pair<Iter, Iter> ret = first.equal_range(5);
    cout << *ret.first << endl;
    cout << *ret.second << endl;

    // 指定比较规则 
    set<int, classcomp> fifth;

    bool(*fn_pt)(int, int) = funcmp;
    set<int, bool(*)(int, int)> sixth(fn_pt);
    sixth.insert(9);
    sixth.insert(5);
    sixth.insert(2);
    sixth.insert(7);
    printContainer(sixth);
}

void TestSet02()
{
    set<char> myset;
    myset.insert('a');
    myset.insert('b');
    myset.insert('c');
    myset.insert('d');
    set<char>::iterator it = myset.begin();
    while(it != myset.end())
    {
        cout << *it << " " ;
        ++it;
    }
    cout << endl;

    set<char>::reverse_iterator re_it = myset.rbegin();
    while(re_it != myset.rend())
    {
        cout << *re_it << " " ;
        ++re_it;
    }
    cout << endl;

    if(!myset.empty())
    {
        cout << "size: " << myset.size() << endl;
    }
    it = myset.find('a');
    if(it != myset.end())
    {
        myset.erase(it);
    }
    cout << "size: " << myset.size() << endl;

    pair<set<char>::iterator, bool> ret;
    ret = myset.insert('c');
    if(ret.second == false)
    {
        it = ret.first;
    }
    myset.insert(it, 'v');
    myset.insert(it, 'x');
    myset.insert(it, 'z');
    printContainer(myset);

    it = myset.begin();
    ++it;
    myset.erase(it);
    printContainer(myset);

    size_t num = myset.erase('v');
    cout << num << endl;

    it = myset.find('x'); 
    myset.erase(it, myset.end());

    printContainer(myset);

    if(myset.count('b') != 0)
    {
        cout << "b 存在" << endl;
    }
}

// 元素可以重复
void TestMultiSet()
{
    int arr[] = {1, 2, 2, 3, 4, 6, 7, 8, 7};
    multiset<int> mul_set(arr, arr + sizeof(arr)/sizeof(arr[0]));
    printContainer(mul_set);
    cout << "size: " << mul_set.size() << endl;
    cout << "2 的个数: " << mul_set.count(2) << endl;
}

int main()
{
    // TestSet01();
    // TestSet02();
    TestMultiSet();
    return 0;
}

