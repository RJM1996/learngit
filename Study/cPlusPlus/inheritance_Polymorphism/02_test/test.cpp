#include <iostream>
#include <string>

using namespace std;

class Person
{
public:
    // 1. 构造函数
    Person(int t_a, const string& t_name, int t_age = 18)
        :m_a(t_a)
        ,m_name(t_name)
        ,m_age(t_age)
    {}

    void display()
    {
        cout << m_a << endl;
        cout << m_name << endl;
        cout << m_age << endl;
    }
public:
    int m_a;
protected:
    string m_name;
private:
    int m_age;
} ;

class Student : public Person
// class Student : protected Person
// class Student : private Person
{
public:
    Student(int p_t_a, const string& t_name, int t_age, int t_number, int t_a)
        :Person(p_t_a, t_name, t_age)
        ,m_number(t_number)
        ,m_a(t_a)
    {}

    void display()
    {
        cout << Person::m_a << endl; // 同名成员需要这样访问
        cout << m_a << endl;
        cout << m_name << endl;
        cout << m_number << endl; // 在子类中可以直接访问父类的 protected 成员
        // cout << m_age << endl; // 不能访问父类的 private 成员
    }

public:
    int m_number;

protected:
    int m_a; // 与父类成员同名的成员
} ;

void Test01()
{
    string name = "tom";
    Person p1(20, name); // p1 父类对象
    p1.m_a = 100;
    p1.display();
    int number = 2018;
    Student s1(88, name, 20, number, 99); // s1 子类对象
    // s1.m_a = 999;
    s1.display();
    // 1. 子类对象可以赋值给父类对象
    p1 = s1;
    // 2. 父类对象不能赋值给子类对象
    // s1 = p1;
    
    // 3. 父类指针/引用可以指向子类对象
    // Person* p_ptr = &s1;
    // Person& p_ref = s1;
    // // 4. 子类指针/引用不能指向父类对象
    // // Student* s_ptr = &p1;
    // // Student& s_ref = p1;
    // // 5. 但是可以通过强制类型转换实现
    // Student* s_ptr = (Student*)&p1;
    // Student& s_ref = (Student&)p1;

    // s_ptr->m_number = 10;
    // s_ptr->display();
    // s_ref.m_number = 20;
    // s_ptr->display();
}

int main()
{
    Test01();

    return 0;
}
