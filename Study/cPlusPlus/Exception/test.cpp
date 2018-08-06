#include <iostream>
#include <stdio.h>
#include <string>
using namespace std;

class Exception
{
public:
    Exception(int t_err_id = 0,  const char* t_err_msg = "")
        :m_err_id(t_err_id)
        ,m_err_msg(t_err_msg)
    {}

    void what() const
    {
        cout << "错误码: " << m_err_id <<  endl;
        cout << "错误消息: " << m_err_msg <<  endl;
    }
private:
    int m_err_id;
    string m_err_msg;
};

void test01(bool isThrow)
{
    if(isThrow)
    {
        throw Exception(1, "抛出 Exception 对象");
    }
    printf("test01(%d)\n", isThrow);
}

void test02(bool isThrowString, bool isThrowInt)
{
    if(isThrowString)
    {
        throw string("抛出 string 对象");
    }
    if(isThrowInt)
    {
        throw 7;
    }
    printf("test02(%d, %d)\n",isThrowString,  isThrowInt);
}

void test()
{
    try
    {
        test01(false);
        test02(true, true);
    }
    catch(const string& errMsg)
    {
        cout << "捕捉到 string 对象: " << errMsg << endl;
    }
    catch(int errId)
    {
        cout << "捕捉到 int 对象: " << errId << endl;
    }
    catch(const Exception& exc)
    {
        exc.what();
    }
    catch(...)
    {
        cout << "未知异常" << endl;
    }
    printf("test()\n");
}

void Func01()
{
    throw string("throw Func01 string");
}

void Func02()
{
    try
    {
        Func01();
    }
    catch(string& errMsg)
    {
        cout << errMsg << endl;
        Exception e(1, "throw Exception");
        throw e;
        // throw errMsg;
    }
}

void Func03()
{
    try
    {
        Func02();
    }
    catch(Exception& e)
    {
        e.what();
    }
}

class Exception01 : public exception
{
public:
    Exception01(int t_err_id = 0, const string& t_err_msg = "")
        :m_err_id(t_err_id)
        ,m_err_msg(t_err_msg)
    {}

    virtual const char* what() const
    {
        cout << "错误码: " << m_err_id <<  endl;
        cout << "错误消息: " << m_err_msg <<  endl;
        return m_err_msg.c_str();
    }
private:
    int m_err_id;
    string m_err_msg;
};


class Exception02 : public exception
{
public:
    Exception02(int t_err_id = 0, const string& t_err_msg = "")
        :m_err_id(t_err_id)
        ,m_err_msg(t_err_msg)
    {}

    virtual const char* what() const
    {
        cout << "错误码: " << m_err_id <<  endl;
        cout << "错误消息: " << m_err_msg <<  endl;
        return m_err_msg.c_str();
    }
private:
    int m_err_id;
    string m_err_msg;
};

void func01()
{
    try
    {
        throw Exception01(1, "Exception01");
        throw Exception02(2, "Exception02");
    }
    catch(exception& e)
    {
        e.what();
    }
}




int main()
{
    // test();
    // Func01();
    // Func02();
    // Func03();
    func01();
    return 0;
}

