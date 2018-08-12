#include <iostream>
#include <map>

using namespace std;

// map 打印函数
    template<class container>
void printContainer(container& s)
{
    typename container::const_iterator it = s.begin();
    // typename container::reverse_iterator it = s.rbegin();
    // while(it != s.end())
    while(it != s.rend())
    {
        cout << it->first << " => " << it->second << endl;
        ++it;
    }
    cout << endl;
}

// C++11 cbegin cend
    template<class container>
void print(container& s)
{
    for(auto it = s.cbegin(); it != s.cend(); it++)
    {
        cout << it->first << " => " << it->second << endl;
    }
}

void TestMap01()
{
    // map 的构造
    // 1. 默认构造
    map<int, char> first;
    first[0] = 'a';
    first[1] = 'b';
    first[2] = 'c';
    first[3] = 'd';

    // 2, 拷贝构造
    map<int, char> second(first);

    // 3. 迭代器构造
    map<int, char> third(first.begin(), first.end());

    // 打印 map
    // printContainer(first);
    print(second);
}

int main1()
{
    TestMap01();
    return 0;
}




#include <iostream>
#include <map>

int main ()
{
    std::map<char,int> mymap;

    mymap['b'] = 100;
    mymap['a'] = 200;
    mymap['c'] = 300;

    // print content:
    std::cout << "mymap contains:";
    for (auto it = mymap.cbegin(); it != mymap.cend(); ++it)
        std::cout << " [" << (*it).first << ':' << (*it).second << ']';
    std::cout << '\n';

    return 0;
}
