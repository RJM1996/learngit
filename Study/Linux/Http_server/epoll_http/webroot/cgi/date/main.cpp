#include "date.h"

void TestDate_01()
{
    Date d1(2018, 7, 6);
    Date d2 = d1 + 100;
    d2.Display();
    d1.Display();
    d1 += 1000;
    d1.Display();
    return ;
}

void TestDate_02()
{
    Date d1(2018, 7, 16);
    Date d2 = d1;
    Date d3(2018, 7, 20);
    d2 = d3;
    d1.Display();
    d2.Display();
    cout << &d1 << endl;
    cout << &d2 << endl;
    cout << &d3 << endl;
    if(d1 == d2)
    {
        cout << "d1 == d2" << endl;
    }
    else
    {
        cout << "d1 != d2" << endl;
    }
}


int main()
{
    // TestDate_01();
    TestDate_02();
    return 0;
}
