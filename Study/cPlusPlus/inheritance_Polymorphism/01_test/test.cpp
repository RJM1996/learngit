#include <iostream>
#include <string>

using namespace std;

// 继承和多态
// 人 类
class Person 
{
public:
    // 构造
    Person(string t_name = "", int t_id = 1234, int t_age = 18)
        :m_name(t_name), m_id(t_id),  m_age(t_age)
    {
        cout << "Person(...)" << endl;
    }

    // 拷贝构造
    Person(const Person& p)
        :m_name(p.m_name)
        ,m_id(p.m_id)
        ,m_age(p.m_age)
    {
        cout << "Person( const Person& p )" << endl;
    }

    // 赋值操作符重载
    Person& operator= (const Person& p)
    {
        cout << "operator= ( const Person& p )" << endl;
        if(&p != this)
        {
            m_name = p.m_name;
            m_id = p.m_id;
            m_age = p.m_age;
        }
        return *this;
    }

    // 析构
    ~Person()
    {
        cout << "~Person() " << endl;
    }
    

    void Display()
    {
        cout << m_name << endl;
    }

protected:
    string m_name;
    int m_id;

private:
    int m_age;
} ;

// 学生类 
class Student : public Person
// class Student : protected Person
// class Student : private Person
{
public:
    // 构造

    void DisplayNum()
    {
        // 如果父类和子类有同名成员, 子类成员将屏蔽对父类同名成员的访问
        // 但是可以通过作用域限定符来访问
        // 但是在实际应用中, 最后不要定义同名成员
        cout << "姓名: " << m_name << endl;
        cout << "身份证号: " << Person::m_id << endl;
        cout << "学号: " << Student::m_id << endl;
    }

    int m_num;
} ;

void test01()
{
    // Person p;
    // p.Display();
    // Student s("tom", 20, 9527, 123);
    Student s;
    // s.DisplayNum();

    // // 子类对象可以给父类对象赋值
    // p = s;
    // // 父类对象不可以给子类对象赋值
    // // s = p;
    // 
    // // 父类的指针和引用可以指向子类对象
    // Person* p1 = &s;
    // Person& p2 = s; 

    // // 子类的指针和引用不能指向父类对象
    // // 但是可以通过强制类型转换完成
    // Student* s1 = (Student*)&p;
    // Student& s2 = (Student&)p;

    // s1->m_id = 10;
    // s2.m_id = 20;
}

int main()
{
    test01();
    return 0;
}
