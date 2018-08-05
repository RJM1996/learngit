#include <iostream>
using namespace std;

class Student;

// 多态
class Person
{
    friend void display(Person& p, Student& s);
public:
    static int count;
    Person()
    {
        ++count;
    }
    // virtual void BuyTickets()
    void BuyTickets()
    {
        cout << "买票 - 全价" << endl;
    }
protected:
    string m_name;
private:
    int m_age;
} ;

class Student : public Person
{
public:
    //virtual void BuyTickets()
    void BuyTickets()
    {
        cout << "买票 - 半价" << endl;
    }
protected:
    int m_id;
} ;

void display(Person& p, Student& s)
{
    cout << p.m_name << endl;
    cout << p.m_age << endl;
    // cout << s.m_id << endl;
}

void Test(Person& p)
{
    p.BuyTickets();
}
void Test01(Student& s)
{
    s.BuyTickets();
}

int Person::count = 0;

int main()
{
    // Person p;
    // Person p1;
    // Person p2;
    // Student s;
    // Student s1;
    // Student s2;
    // Student s3;
    // cout << Person::count << endl;
    // s3.count = 0;
    // cout << Person::count << endl;

    Student s1;
    Person* p3 = &s1;
    p3->BuyTickets();

    // p.BuyTickets();
    // s.BuyTickets();
    // Test(p);
    // Test(s);
    // Test01((Student&)p);
    // Test01(s);
    // display(p, s);
    return 0;
}
