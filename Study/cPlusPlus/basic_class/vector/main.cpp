
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

int main()
{
    printf("\n\n\n");
    printf("\n\n\n");
//    Test01();
    Test02();
    Test03();
    printf("\n\n\n");
    printf("\n\n\n");
    return 0;
}
