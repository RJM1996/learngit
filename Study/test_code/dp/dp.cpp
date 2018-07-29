#include <iostream>
#include <map>
#include <vector>
#include <time.h>

using namespace std;

// 10级台阶, 每次走一步或者两步, 共多少种走法
int getClimbingWays(int n)
{
    if(n == 1)
        return 1;
    if(n == 2)
        return 2;
    return getClimbingWays(n-1) + getClimbingWays(n-2);
}
int getClimbingWays_waitMap(int n, map<int, int> m)
{
    if(n == 1)
        return 1;
    if(n == 2)
        return 2;
    map<int, int>::iterator it = m.find(n);
    if(it != m.end())
    {
        return m.at(n);
    }
    else
    {
        int val =  getClimbingWays_waitMap(n-1, m) + getClimbingWays_waitMap(n-2, m);
        m.insert(pair<int,int>(n, val));
        return val;
    }
}
int getClimbingWays_withDp(int n)
{
    if(n < 1)
        return 0;
    if(n == 1)
        return 1;
    if(n == 2)
        return 2;
    int a = 1;
    int b = 2;
    int tmp = 0;
    for(int i=3; i<=n; i++)
    {
        tmp = a + b;
        a = b;
        b = tmp;
    }
    return tmp;
}
void TestGetClimbingWays()
{
    int n = 10;
    map<int, int> m;

    clock_t a1 = clock();
    for(int i=0; i<10000; i++)
    {
        getClimbingWays_waitMap(n, m);
    }
    cout << getClimbingWays_waitMap(n, m) << endl;
    clock_t a2 = clock();
    cout << "哈希:" << a2 - a1 << endl;

    clock_t b1 = clock();
    for(int i=0; i<10000; i++)
    {
        getClimbingWays(n);
    }
    cout << getClimbingWays(n) << endl;
    clock_t b2 = clock();
    cout << "递归: " << b2 - b1 << endl;

    clock_t c1 = clock();
    for(int i=0; i<10000; i++)
    {
        getClimbingWays_withDp(n);
    }
    cout << getClimbingWays_withDp(n) << endl;
    clock_t c2 = clock();
    cout << "dp: " << c2 - c1 << endl;
}

// 10 个工人, 5 座金矿
// 500/5
// 200/3
// 300/4
// 350/3
// 400/5
// 要求得到尽可能多的黄金, 要挖哪几座金矿
vector<int> gold_p_and_c(int n, int m, int arr[][2])
{
    vector<int> ret;
    int max_gold = 0;
    for(int i=0; i<m; i++)
    {
        for(int j=0; j<2; j++)
        {

        }
    }
}

void Test_gold()
{
    int n = 10;
    int m = 5;
    int arr[][2] = {
        {500, 5},
        {200, 3},
        {300, 4},
        {350, 3},
        {400, 5}
    };
    vector<int> ret = gold_p_and_c(n ,m , arr);
}

int main()
{
    TestGetClimbingWays();
    return 0;
}
