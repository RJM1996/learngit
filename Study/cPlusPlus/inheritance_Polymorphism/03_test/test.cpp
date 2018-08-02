#include <iostream>
#include <string>

using namespace std;

class Person
{
public:
    // 1. 构造函数
    Person()
    {
         cout << "Person(...)" << endl;
    }
    // Person(const string& t_name, int t_age)
    //     :m_name(t_name)
    //     ,m_age(t_age)
    // {
    //     cout << "Person(...)" << endl;
    // }
    // 2. 拷贝构造函数
    Person(const Person& p)
    {
        cout << "Person(const Person& p)" << endl;
        m_name = p.m_name;
        m_age = p.m_age;
    }
    // 3. 赋值操作符重载
    Person& operator= (const Person& p)
    {
        cout << "Person operator= (const Person& p)" << endl;
        if(this != &p)
        {
            m_name = p.m_name;
            m_age = p.m_age;
        }
        return *this;
    }
    // 4. 析构函数
    ~Person()
    {
        cout << "~Person ()" << endl;
    }

    void display()
    {
        cout << m_name << endl;
        cout << m_age << endl;
    }
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
    // Student(const string& t_name, int t_age, int t_number)
    //     :Person(t_name, t_age)
    //     ,m_number(t_number)
    // {
    //     cout << "Student(...) " << endl;
    // }



    void display()
    {
        cout << m_name << endl;
        cout << m_number << endl; // 在子类中可以直接访问父类的 protected 成员
        // cout << m_age << endl; // 不能访问父类的 private 成员
    }

protected:
    int m_number;
} ;

void Test01()
{
    // string name = "tom";
    // Student s1(name, 18, 2018);
    // s1.display();
    // Student s2 = s1;
    // s2.display();
    // s2 = s1;
}

void Test02()
{
    Student s1;
    Student s2 = s1;
    s1 = s2;
}

int main()
{
    // Test01();
    Test02();

    return 0;
}
