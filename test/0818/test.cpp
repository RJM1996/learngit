#include <iostream>
#include <stdio.h>
#include <string>

using namespace std;

class Demo
{
private:
    int i;
public:
    int GetI()
    {
        return i;
    }
    static void SetI(Demo& d, int tmp)
    {
        d.i = tmp;
    }
    static void Print(const char* str)
    {
        cout << str << endl;
    }
};

void Test01()
{
    Demo::Print("start ...");
    Demo d1;
    d1.SetI(d1, 10);
    cout << "d1.i: " << d1.GetI() << endl;
    Demo::SetI(d1, 20);
    cout << "d1.i: " << d1.GetI() << endl;
    Demo::Print("end ...");
}

class Test
{
private:
    static int _count;
public:
    Test()
    {
        _count++;
    }
    ~Test()
    {
        _count--;
    }
    static int GetCount()
    {
        return _count;
    }
};

int Test::_count = 0;

void Test02()
{
    printf("count = %d\n", Test::GetCount()); // 0

    Test t1;
    Test t2;

    printf("count = %d\n", t1.GetCount()); // 2
    printf("count = %d\n", t2.GetCount()); // 2

    Test* pt = new Test();

    printf("count = %d\n", pt->GetCount()); // 3

    delete pt;

    printf("count = %d\n", Test::GetCount()); // 2

}

int main()
{
    // Test01();
    Test02();
}
