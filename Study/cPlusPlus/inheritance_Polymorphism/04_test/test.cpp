#include <iostream>
#include <string>

using namespace std;

class Person
{
public:
    string m_name;
} ;

class Student : public Person
{
protected:
    int m_number;
} ;

class Teacher : public Person
{
protected:
    int m_id;
} ;

class Assistant : public Student, public Teacher
{
public:
    void display()
    {
        cout << Student::m_name << endl;
        cout << Teacher::m_name << endl;
    }
protected:
    string m_major_cause;
} ;

void Test01()
{
    Assistant as;
    as.Teacher::m_name = "Tom";
    as.Student::m_name = "Jack";
    // as.m_name = "hehe";
    as.display();
}


int main()
{
    Test01();
    return 0;
}
