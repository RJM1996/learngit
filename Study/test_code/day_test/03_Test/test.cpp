#include <iostream>
#include <malloc.h>
using namespace std;

class A
{
public:
    virtual void Function()
    // Function(int _y)
    {
        // this->x = _y;
        // cout << "I can run, y: " << _y <<  endl;
        cout << "I can run " << endl;
    }
private:
    int x;
};

class Father
{
public:
    Father(int _y)
        :x(_y)
    {}

    virtual void print()
    {
        cout << "I Am Father " << endl;
    }

    virtual void set_x(int _y)
    {
        x = _y;
        cout << "I am Father, set x = " << x << endl;
    }

    virtual ~Father()
    {
        cout << "~Father ()" << endl;
    }

private:
    int x;
};

class Child01 : public Father
{
public:
    virtual void print()
    {
        cout << "I Am Child01 " << endl;
    }
};

class Child02 : public Father
{
public:
    virtual void print()
    {
        cout << "I Am Child02 " << endl;
    }
};

typedef void(*func)(void);

void test()
{
    // Father* ptr01 = new Father();
    // Father* ptr02 = new Child01;
    // Father* ptr03 = new Child02;
    // ptr01->print();
    // ptr02->print();
    // ptr03->print();
    Father f(100);
    int* vptr = (int*)(&f);
    cout << "虚函数指针的地址是: " << vptr << endl;

    func vfunc = (func)*((int*)*(int*)(&f));
    cout << "第一个虚函数的地址为: " << (int*)*(int*)(&f) << endl;
    cout << "通过地址, 调用虚函数: Father::print(): " ;
    vfunc();

    func vfunc01 = (func)* ((int*)*((int*)(&f))+2);
    cout << "第二个虚函数的地址为: " << ((int*)(*((int*)&f)) + 2) << endl;
    cout << "通过地址, 调用虚函数: Father::set_x(): " ;
    vfunc01();

    func vfunc02 = (func)* ((int*)*((int*)(&f))+4);
    cout << "第三个虚函数的地址为: " << ((int*)(*((int*)&f))+4) << endl;
    cout << "通过地址, 调用虚函数: Father::~Father(): " ;
    vfunc02();
}


int main()
{
    // A a;
    // A *pa = &a;
    // // A *pa = NULL;
    // pa->Function(); // 相当于 Function(pa);
    
    test();

    // int x = 0;
    // int* a = &x;
    // cout << sizeof(a) << endl;
    // cout << a << endl;
    // a++;
    // cout << a << endl;
}
