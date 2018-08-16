#include <iostream>
using namespace std;



int (*func)(int, int);

int Fun(int x, int y)
{
    return x + y;
}

int Fun01()
{
    return 100;
}

void Test01()
{
    int ret = 0;
    func = Fun;
    ret = (*func)(10, 20);
    cout << ret << endl;
}

int main()
{
    Test01();
}
