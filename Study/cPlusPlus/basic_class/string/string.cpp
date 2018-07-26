#include <iostream>
#include <string.h>
#include <assert.h>

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
        if(n > _capacity)
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
            for(size_t i = _size; i < n; i++)
            {
                _str[i] = ch;
            }
            _str[n] = '\0';
            _size = n;
        }
    }
    // 11. 任意位置插入字符
    void Insert(size_t pos, char ch)
    {
        assert(pos <= _size);
        if(_capacity == _size)
        {
            Expand(_capacity * 2);
        }
        int end = _size;
        while(end >= (int)pos)
        {
            _str[end+1] = _str[end];
            --end;
        }
        _str[pos] = ch;
        ++_size;
    }
    // 12. 在任意位置插入字符串
    void Insert(size_t pos, const char* str)
    {
        assert(pos <= _size);
        int len = strlen(str);
        if(_size+len >= _capacity)
        {
            Expand(_size + len);
        }
        int end = _size;
        while(end >= (int)pos)
        {
            _str[end+len] = _str[end];
            --end;
        }
        strncpy(_str+pos, str, len);
        _size += len;
    }
    // 13. 尾插
    void PushBack(char ch)
    {
        Insert(_size, ch); // 调在任意位置插入字符的 Insert
    }
    // 14. 添加字符串
    void Append(const char* str)
    {
        Insert(_size, str); // 调在任意位置插入字符串的 Insert
    }
    // 15. 重载 += 
    // s1 += "hello"
    String& operator+= (const char* str)
    {
        this->Append(str);
        return *this;
    }
    // s1 += s2
    String& operator+= (const String& s)
    {
        *this += s._str;
        return *this;
    }
    // 16. 重载 +
    // s1 + "hello"
    String operator+ (const char* str)
    {
        String ret(*this);
        ret.Append(str);
        return ret;
    }
    // s1 + s2
    String operator+ (const String& s)
    {
        return *this + s._str;
    }
    // 17. 尾删
    void PopBack()
    {
        _str[--_size] = '\0';
    }
    // 18. 从 pos 位置开始删除 len 个字符
    void Erase(size_t pos, size_t len)
    {
        assert(pos <= _size);
        if(pos + len > _size)
        {
            _str[_size] = '\0';
            _size = pos;
        }
        else
        {
            strcpy(_str+pos, _str+pos+len);
            _size -= len;
        }
    }

    // 19. 求 size
    size_t Size()
    {
        return _size;
    }
    // 20. 求 capacity
    size_t Capacity()
    {
        return _capacity;
    }
    // 21. 判空
    bool Empty()
    {
        return _size == 0;
    }
    // 22. 查找字符
    size_t Find(char ch) const
    {
        for(size_t i=0; i<_size; i++)
        {
            if(ch == _str[i])
                return i;
        }
        return npos;
    }
    // 23. 查找字符串
    size_t Find(const char* sub) const
    {
        char* src = _str;
        while(*src)
        {
            const char* src_tmp = src;
            const char* sub_tmp = sub;
            while( *sub_tmp && *src_tmp == *sub_tmp )
            {
                ++src_tmp;
                ++sub_tmp;
            }
            if(*sub_tmp == '\0')
            {
                return src-_str;
            }
            else
            {
                ++src;
            }
        }
        return npos;
    }
    // 24. 字符串比大小 重载 <
    bool operator< (const String& s) const
    {
        const char* str_left = _str;
        const char* str_right = s._str;
        while(*str_left && *str_right)
        {
            if(*str_left < *str_right)
            {
                return true;
            }
            else if(*str_left > *str_right)
            {
                return false;
            }
            else
            {
                ++str_left;
                ++str_right;
            }
        }
        if(*str_left == '\0' && *str_right != '\0')
        {
            return true;
        }
        else
        {
            return false;
        }
    }
    // 25. 判断字符串是否相等 重载 ==
    bool operator== (const String& s) const
    {
        const char* str_left = _str;
        const char* str_right = s._str;
        while(*str_left && *str_right)
        {
            if(*str_left != *str_right)
            {
                return false;
            }
            else
            {
                ++str_left;
                ++str_right;
            }
        }
        if(*str_left == '\0' && *str_right == '\0')
        {
            return true;
        }
        else
        {
            return false;
        }
    }
    // 重载 <= 
    bool operator<= (const String& s) const
    {
        return (*this < s) || (*this == s);
    }
    // 重载 >
    bool operator> (const String& s) const
    {
        return !(*this <= s);
    }
    // 重载 >=
    bool operator>= (const String& s) const
    {
        return !(*this < s);
    }
    // 重载 !=
    bool operator!= (const String& s) const
    {
        return !(*this == s);
    }

private:
    char *_str; 
    size_t _size;
    size_t _capacity;

public:
    static size_t npos;
};
size_t String::npos = -1;


void TestString()
{
    String s1("hello, world");
    String s2 = s1;
    cout << s1.c_str() << endl;
    cout << s2.c_str() << endl;
    s1.PushBack('a');
    s1.PushBack('b');
    s1.PushBack('c');
    cout << s1.c_str() << endl;
    s1 += "hahahaha";
    cout << s1.c_str() << endl;
    s1.PopBack();
    s1.PopBack();
    s1.PopBack();
    cout << s1.c_str() << endl;
    s1.Append("zxc");
    cout << s1.c_str() << endl;
    s1.Resize(30, 'a');
    cout << s1.c_str() << endl;
    cout << s1.Size() << endl;
    cout << s1.Capacity() << endl;
    cout << s1.Find('a') << endl;
    cout << (int)s1.Find("ccc") << endl;
    s1.Erase(5, 10);
    cout << s1.c_str() << endl;
    bool ret = s1 < s2;
    cout << ret << endl;
}

int main()
{
    TestString();
    return 0;
}
