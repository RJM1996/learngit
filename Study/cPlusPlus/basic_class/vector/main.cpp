
#include "vector.h"


void Test01()
{
    Vector v;
    int size = v.Size(); // 测试当前大小
    int capacity = v.Capacity(); // 测试容量
    cout << size << endl;
    cout << capacity << endl;
}

void Test02()
{
    Vector v;
    v.PushBack(1);
    v.PushBack(3);
    v.PushBack(7);
    v.PushBack(9);
    for(size_t i=0; i<v.Size(); i++)
    {
        cout << v[i] << endl;
    }
    size_t pos = v.Find(5);
    cout << "size ecpected : 4 , actual : " << v.Size() << endl;
    cout << "capacity ecpected : 6 , actual : " << v.Capacity() << endl;
    v.PopBack();
    cout << "size ecpected : 3 , actual : " << v.Size() << endl;
    cout << "capacity ecpected : 6 , actual : " << v.Capacity() << endl;
}

void Test03()
{
    Vector v1;
    v1.Reserve(100);
    size_t capacity = v1.Capacity();
    cout << "capacity change : " << v1.Capacity() << endl;
    for(int i=0; i<100; i++)
    {
        v1.PushBack(i);
        if(v1.Capacity() != capacity)
            cout << "capacity change : " << v1.Capacity() << endl;
    }
    Vector v2;
    size_t capa = v2.Capacity();
    for(int i=0; i<100; i++)
    {
        v2.PushBack(i);
        if(v2.Capacity() != capa)
          cout << "capacity change : " << v2.Capacity() << endl;
    }
}

void Test04()
{
    Vector vc;
    vc.PushBack(1);
    vc.PushBack(3);
    vc.PushBack(5);
    vc.PushBack(7);
    for(size_t i=0; i<vc.Size(); i++)
    {
        cout << vc[i] << endl;
    }
    size_t pos = vc.Find(5);
    cout << "pos : " << pos << endl;
    Vector vc1;
    vc1.PushBack(2);
    vc1.PushBack(4);
    vc1.PushBack(6);
    vc1.PushBack(8);
    for(size_t i=0; i<vc1.Size(); i++)
    {
        cout << vc1[i] << endl;
    }
    vc1 = vc;
    for(size_t i=0; i<vc1.Size(); i++)
    {
        cout << vc1[i] << endl;
    }
    for(size_t i=0; i<vc.Size(); i++)
    {
        cout << vc[i] << endl;
    }
}

void Test05()
{
    Vector vc;
    vc.PushBack(1);
    vc.PushBack(1);
    vc.PushBack(1);
    vc.PushBack(1);
    vc.PopBack();
    vc.PopBack();
    vc.PopBack();
    vc.PopBack();
    if(vc.Empty())
    {
        cout << "Vector 为空" << endl;
    }
    else
    {
        cout << "Vector 不为空" << endl;
    }
}

int main()
{
    printf("\n\n\n");
    printf("\n\n\n");
//    Test01();
//    Test02();
//    Test03();
//    Test04();
    Test05();
    printf("\n\n\n");
    printf("\n\n\n");
    return 0;
}
