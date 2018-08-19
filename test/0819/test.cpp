#include <iostream>
#include <vector>
#include <list>

using namespace std;

void test01()
{
    list<int> l1;
    list<int>::iterator it;
    for(int i=0; i<10; i++)
    {
        l1.push_back(i);
    }
    it = l1.begin();
    while(it != l1.end())
    {
        if(*it % 2 == 0)
        {
            l1.erase(it);
        }
        ++it;
    }
    for(it = l1.begin(); it != l1.end(); it++)
    {
        cout << *it << " ";
    }
    cout << endl;
}

template<typename container>
void Print(const container& c)
{
    typename container::const_iterator it = c.begin();
    while(it != c.end())
    {
        cout << *it << " ";
        ++it;
    }
    cout << endl;
}

void test02()
{
    vector<int> v1;
    v1.push_back(1);
    v1.push_back(2);
    v1.push_back(4);
    v1.push_back(7);
    v1.push_back(6);
    v1.push_back(8);
    vector<int>::iterator it = v1.begin();

    // while(it != v1.end())
    // {
    //     if(*it % 2 == 0)
    //         it = v1.erase(it);
    //     else
    //         ++it;
    // }
    // it = v1.begin();
    cout << v1.size() << endl;
    cout << v1.capacity() << endl;
    
    while(it != v1.end())
    {
        if(*it % 2 == 0)
            v1.insert(it, 99), it++;
        ++it;
    }
    
    cout << endl;
    Print(v1);
}

double add(double x, double y)
{
    return x + y;
}
double sub(double x, double y)
{
    return x - y;
}
double mul(double x, double y)
{
    return x * y;
}
double div(double x, double y)
{
    return x / y;
}

// 函数指针数组
double (*pfunc[])(double, double) = {
    add, sub, mul, div
};

void test03()
{
    int add = 0;
    int sub = 1;
    int mul = 2;
    int div = 3;
    double ret = pfunc[add](10, 20);
    cout << ret << endl;
    ret = pfunc[sub](10, 20);
    cout << ret << endl;
    ret = pfunc[mul](10, 20);
    cout << ret << endl;
    ret = pfunc[div](10, 20);
    cout << ret << endl;
}

int main()
{
    // test01();
    // test02();
    test03();
}
