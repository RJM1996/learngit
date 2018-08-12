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
    while(it != s.end())
    {
        cout << it->first << " => " << it->second << endl;
        ++it;
    }
    cout << endl;
}

// // C++11 cbegin cend
// template<class container>
// void print(container& s)
// {
//     for(auto it = s.cbegin(); it != s.cend(); it++)
//     {
//         cout << it->first << " => " << it->second << endl;
//     }
// }

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
    printContainer(first);
    // print(second);

    if(!first.empty())
    {
        cout << first.size() << endl;
    }

    cout << first[0] << endl;
    // cout << first.at(5) << endl; // 会检查 key 的合法性, 抛异常
}

void TestMap02()
{
    // 插入
    map<int, char> mymap;
    mymap.insert(pair<int, char>(1, 'x'));
    mymap.insert(pair<int, char>(2, 'y'));
    mymap.insert(pair<int, char>(3, 'z'));
    printContainer(mymap);
    pair<map<int, char>::iterator, bool> ret;
    ret = mymap.insert(pair<int, char>(3, 'v'));
    if(ret.second == false)
    {
        cout << "3 已经存在, 对应的 val => " << ret.first->second << endl;
    }

    map<int, char>::iterator it = mymap.begin();
    mymap.insert(it, pair<int, char>(4, 'b'));
    mymap.insert(it, pair<int, char>(5, 'n'));
    printContainer(mymap);

    map<int, char> othermap;
    othermap.insert(mymap.begin(), mymap.find(4)); // 从mymap的第一个到 4 的前一个
    printContainer(othermap);

    // 删除
    mymap.erase(2); // 指定 key 删除
    printContainer(mymap);
    it = mymap.find(5);
    mymap.erase(it); // 根据 find 返回的迭代器删除
    printContainer(mymap);
    it = mymap.find(1);
    mymap.erase(it, mymap.end()); // 删除一个区间
    printContainer(mymap);
    cout << "mymap size: " << mymap.size() << endl;
    cout << "othermap size: " << othermap.size() << endl;
    othermap.clear();
    cout << "othermap size: " << othermap.size() << endl;
}

void TestMap03()
{
    // key_compare key_comp() const;
    map<int, char> mymap;
    mymap[0] = 'a';
    mymap[1] = 'b';
    mymap[2] = 'c';
    mymap[3] = 'd';
    map<int, char>::key_compare mycmp = mymap.key_comp();
    
    // int low = mymap.begin()->first;
    int high = mymap.rbegin()->first;

    map<int, char>::iterator it = mymap.begin();
    do 
    {
        cout << it->first << " => " << it->second << endl;
    } while(mycmp((*it++).first, high));
    cout << endl;
}

void TestMap04()
{
    map<int, char> mymap;
    mymap[1] = 'x';
    mymap[2] = 'y';
    mymap[3] = 'z';
    mymap[4] = 'v';
    mymap[5] = 'm';
    mymap[6] = 'n';
    mymap[7] = 'b';
    printContainer(mymap);
    cout << "mymap.find(2)->second: " << mymap.find(2)->second << endl;
    map<int, char>:: iterator it = mymap.find(3);
    if(it != mymap.end())
    {
        mymap.erase(it);
    }
    printContainer(mymap);
    it = mymap.find(9); // 返回 map::end
    // mymap.erase(it); 运行会出错
    
    int n;
    for(n=1; n<10; n++)
    {
        if(mymap.count(n) == 1)
        {
            cout << "key: " << n << endl;
        }
        else
        {
            cout << "key: 不存在 " << endl;
        }
    }

    map<int, char>::iterator itlow, itup;
    // itlow = mymap.lower_bound(2);
    // itup = mymap.lower_bound(6);
    itlow = mymap.upper_bound(2);
    itup = mymap.upper_bound(6);
    mymap.erase(itlow, itup);
    printContainer(mymap);
}

void TestMap_WaterMargin()
{

    map <string, string> mymap;
    mymap.insert(pair<string, string>("宋江", "及时雨"));
    mymap.insert(pair<string, string>("吴用", "智多星"));
    mymap.insert(make_pair("李逵", "黑旋风"));
    mymap.insert(make_pair("武松", "行者"));
    mymap.insert(make_pair("鲁智深", "花和尚"));
    cout << "Map size: " << mymap.size() << endl;
    // 插入 key 存在, val 不同的元素
    mymap.insert(make_pair("李逵", "铁牛"));
    cout << "Map size: " << mymap.size() << endl;
    printContainer(mymap);

    // 通过 key 查找 val
    cout << "武松: " << mymap["武松"] << endl;

    // 修改 key 对应的 val
    cout << "李逵: " << mymap["李逵"] << endl;
    mymap["李逵"] = "铁牛";
    cout << "李逵: " << mymap["李逵"] << endl;

    // 通过 [] 访问 key 对应的 val 时, 如果 key 不存在, 会创建一个默认 val 的键值对
    cout << "武大郎: " << mymap["武大郎"] << endl;
    cout << "Map size: " << mymap.size() << endl;
    cout << "武大郎: " << mymap["武大郎"] << endl; // val 默认为空

    // 删除
    mymap.erase(mymap.find("武大郎"));
    cout << "Map size: " << mymap.size() << endl;

    // 清空
    mymap.clear();
    cout << "Map size: " << mymap.size() << endl;
}

void TestMultiMap()
{
    multimap <string, string> mymap;
    mymap.insert(pair<string, string>("宋江", "及时雨"));
    mymap.insert(pair<string, string>("吴用", "智多星"));
    mymap.insert(make_pair("李逵", "黑旋风"));
    mymap.insert(make_pair("武松", "行者"));
    mymap.insert(make_pair("鲁智深", "花和尚"));
    printContainer(mymap);

    cout << "Map size: " << mymap.size() << endl;
    // 插入 key 存在, val 不同的元素
    mymap.insert(make_pair("李逵", "铁牛"));
    cout << "Map size: " << mymap.size() << endl;
    printContainer(mymap);

    multimap <int, int> m;
    for(int i=0; i<10; i++)
    {
        m.insert(make_pair(i, i));
    }
    m.insert(make_pair(5, 11));
    m.insert(make_pair(5, 12));
    m.insert(make_pair(5, 13));
    m.insert(make_pair(5, 14));

    printContainer(m);
    cout << "key 为 5 的元素个数: " << m.count(5) << endl;

    multimap<int, int>::iterator it;
    it = m.lower_bound(5);
    cout << it->first << " -> " << it->second << endl;
    it = m.upper_bound(5);
    cout << it->first << " -> " << it->second << endl;

    cout << endl;

    typedef multimap<int, int>::iterator Iter;
    pair<Iter, Iter> ret = m.equal_range(5);
    cout << ret.first->first << " -> " << ret.first->second << endl;
    cout << ret.second->first << " -> " << ret.second->second << endl;
}

int main()
{
    // TestMap01();
    // TestMap02();
    // TestMap03();
    // TestMap04();
    // TestMap_WaterMargin();
    TestMultiMap();
    return 0;
}




