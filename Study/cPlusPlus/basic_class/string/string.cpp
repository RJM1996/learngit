#include <iostream>
#include <string.h>

using namespace std;

// 实现两种方式的引用计数, 写时拷贝。

// 一. 浅拷贝
/*
   class String
   {
   public:
// 1. 构造
String(const char *str = " ")
:_str(new char[strlen(str)+1])
{
strcpy(_str, str); 
}
// 2. 拷贝构造
// s2(s1)
String(const String &str)
:_str(str._str)
{}
// 3. 赋值操作符重载
// s2 = s1
String& operator=(const String &str)
{
if(this != &str)
{
_str = str._str;
}
return *this;
}
// 4. 析构
~String()
{
if(_str)
delete[] _str;
}
// 5. C 风格字符串
const char *c_str()
{
return _str;
}
// 6. 写时拷贝
void CopyOnWrite();
// 7. 随机访问
char &operator[](size_t pos)
{
return _str[pos];
}
private:
char *_str;
};
*/

// 二. 深拷贝1.0
/*
   class String
   {
   public:
// 1. 构造
String(const char *str = " ")
:_str(new char[strlen(str)+1])
{
strcpy(_str, str); 
}
// 2. 拷贝构造
// s2(s1)
String(const String &str)
:_str(new char[strlen(str._str) + 1])
{
strcpy(_str, str._str);
}
// 3. 赋值操作符重载
// s2 = s1
String& operator=(const String &str)
{
if(this != &str)
{
// 深拷贝
char* tmp = new char[strlen(str._str) + 1];
strcpy(tmp, str._str);
delete[] _str;
_str = tmp;
}
return *this;
}
// 4. 析构
~String()
{
if(_str)
{
delete[] _str;
_str = NULL;
}
}
// 5. C 风格字符串
const char *c_str()
{
return _str;
}
// 6. 写时拷贝
void CopyOnWrite();
// 7. 随机访问
char &operator[](size_t pos)
{
return _str[pos];
}
private:
char *_str;
};
*/

// 三. 深拷贝2.0
class String
{
public:
    // 1. 构造
    String(const char *str = " ")
        :_size(strlen(str))
        ,_capacity(_size)
        {
            _str = new char[_size+1];
            strcpy(_str, str);
        }
    void Swap(String& s)
    {
        swap(_str, s._str);
        swap(_size, s._size);
        swap(_capacity, s._capacity);
    }
    // 2. 拷贝构造
    // s2(s1)
    String(const String &s)
        :_str(NULL)
    {
        String tmp(s._str);
        this->Swap(tmp);
    }
    // 3. 赋值操作符重载
    // s2 = s1
    String& operator= (String& s)
    {
        this->Swap(s);
        return *this;
    }
    // 4. 析构
    ~String()
    {
        if(_str)
        {
            delete[] _str;
            _str = NULL;
        }
    }
    // 5. 返回 C 字符串
    const char *c_str()
    {
        return _str;
    }
    // 6. 写时拷贝
    void CopyOnWrite();
    // 7. 随机访问, 重载 []
    char &operator[] (size_t pos)
    {
        return _str[pos];
    }
    // 8. 扩容
    void Expand(size_t n)
    {
        if(n < _capacity)
        {
            char* tmp = new char[n+1];
            strcpy(tmp, _str);
            delete[] _str;
            _str = tmp;
            _capacity = n;
        }
    }
    // 9. 预先开空间
    void Reserve(size_t n)
    {
        Expand(n);
    }
    // 10. 调整大小
    void Resize(size_t n, char ch = '\0')
    {
        if(n < _size)
        {
            _size = n;
            _str[_size] = '\0';
        }
        else
        {
            if(n > _capacity)
            {
                Expand(n);
            }
        }
    }

private:
    char *_str; 
    size_t _size;
    size_t _capacity;
};


void TestString()
{
    String s1("hello, world");
    String s2 = s1;
    cout << s1.c_str() << endl;
    cout << s2.c_str() << endl;
}

int main()
{
    TestString();
    return 0;
}
