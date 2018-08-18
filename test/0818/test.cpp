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

template<class T>
class A
{
private:
    static T _count;
public:
    void GetAddr()
    {
        cout << &_count << endl;
    }
};
template<>
int A<int>::_count = 0;
template<>
float A<float>::_count = 0.0;
template<>
string A<string>::_count = " ";

void Test03()
{
    A<int> a;
    a.GetAddr();
    A<int> b;
    b.GetAddr();

    A<float> c;
    c.GetAddr();
    A<float> d;
    d.GetAddr();

    A<string> e;
    e.GetAddr();
}

void Test04()
{
    // int arr[] = {1, 2, 3, 4, 5};
    // cout << sizeof(arr) << endl;
    // cout << sizeof(&arr[0]) << endl;
    // cout << sizeof(int*) << endl;

    int n = 0;
    int m = 0;
    cin >> n >> m ;
    int arr01[n][m];
    for(int i=1; i<=n; i++)
    {
        for(int j=1; j<=m; j++)
        {
            arr01[i][j] = i*j;
            printf("%2d ", arr01[i][j]);
        }
        cout << endl;
    }
    cout << endl;
}

void Test05()
{
    int arr[10] = {1, 2, 3};
    for(int i=0; i<10; i++)
    {
        cout << arr[i] << " ";
    }
    cout << endl;
    cout << arr[11] << endl;
    arr[11] = 100;
    cout << arr[11] << endl;
    cout << endl;
}




int main()
{
    // Test01();
    // Test02();
    // Test03();
    // Test04();
    Test05();

    return 0;
}
