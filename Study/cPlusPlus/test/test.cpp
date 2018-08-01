#include <iostream>
#include <string>

using namespace std;

#if 0
void print()
{
    cout << "Jim" << endl;
    cout << 21 << endl;
}
void print(string t_name, size_t t_age)
{
    cout << t_name << endl;
    cout << t_age << endl;
}
void Test01()
{
    print();
    print("tom", 20);
}

#include <sys/time.h>
#include <unistd.h>

struct BigData
{
    int array [1000];

};
void DealBigData (BigData& x)
{
    x.array [0]= 0;
    x.array [1]= 1;
    x.array [2]= 2;
}
void DealBigData1 (BigData* x)
{
    x->array [0]= 0;
    x->array [1]= 1;
    x->array [2]= 2;
}
void TestReference3 ()
{
    long long L1,L2,L3;
    timeval tv;
    gettimeofday(&tv,NULL);
    L1 = tv.tv_sec*1000*1000 + tv.tv_usec;
    BigData bd;
    for (int i = 0; i < 10000000; ++i )
    {
        DealBigData(bd);
    }
    gettimeofday(&tv,NULL);
    L2 = tv.tv_sec*1000*1000+tv.tv_usec;
    cout<<"引用 time:" <<L2 - L1<<endl ;
}
void TestReference4 ()
{
    long long L1,L2,L3;
    timeval tv;
    gettimeofday(&tv,NULL);
    L1 = tv.tv_sec*1000*1000 + tv.tv_usec;
    BigData bd;
    for (int i = 0; i < 10000000; ++i )
    {
        DealBigData1(&bd);
    }
    gettimeofday(&tv,NULL);
    L2 = tv.tv_sec*1000*1000+tv.tv_usec;
    cout<<"指针 time:" <<L2 - L1<<endl ;
}

int& Add (int d1, int d2)
        //int Add ( int d1 , int d2  )
{
    int ret = d1 + d2;
    return ret ;
}
void Test02 ()
{
    int a = 3, b = 4;
    int c = Add( a, b );
    cout << "c: " << c << endl;
}

void Test03()
{
    int a = 7;
    int& b = a;
    int* c = &a;
    //b++;
    c++;
    cout << "a: " << a << endl;
    cout << "b: " << b << endl;
    cout << "&a: " << &a << endl;
    cout << " c: " << c << endl;
    cout << sizeof(c) << endl;
}

// gcc 对齐数 默认是 4
class A
{
    public:
        char ch ; // 1 字节
        double d ; // 8 字节 对齐数是 4
}; // 1000 1111 1111 总大小为 12
class B
{
    char ch1 ; // 1 字节
    A a ; // 12 字节  最大对齐数是 4
    char ch2 ; // 1 字节
}; // 1000 1111 1111 1111 1000 总大小是 20
class C
{
    void print()
    {
        int _a = 100;
        cout << _a << endl;
    }
    private:
    // int _a;
};
class D
{

};
void Test04()
{
    A a;
    cout << sizeof(A) << endl;
    cout << sizeof(B) << endl;
    cout << sizeof(C) << endl;
    cout << sizeof(D) << endl;
}

class Date
{
    public :
        // 1.无参构造函数
        Date ()
        {
            cout << "Date()" << endl;
        }
        // 2.带参构造函数
        Date (int year, int month , int day )
        {
            cout << "Date(...)" << endl;
            _year = year ;
            _month = month ;
            _day = day ;
        }
    private :
        int _year ;
        int _month ;
        int _day ;
};
void TestDate1 ()
{
    Date d1 ; // 调用无参构造函数
    Date d2 (2015, 1, 1); // 调用带参的构造函数
    // Date  (); // 注意这里没有调用d3的构造函数定义出 d3
}


class Date
{
    public :
        // 3.全缺省参数的构造函数
        Date (int year = 2000, int month = 1, int day = 1)
        {
            cout << "Date(.. .. ..)" << endl;
            _year = year ;
            _month = month ;
            _day = day ;
        }
        // 4.半缺省参数的构造函数（不常用）
        Date (int year, int month = 1)
        {
            cout << "Date(  .. )" << endl;
            _year = year ;
            _month = month ;
            _day = 1;
        }
    private :
        int _year ;
        int _month ;
        int _day ;
};
void Test()
{
    // Date d1(2010) ; // 调用缺省构造函数
    Date d2 (2015, 1, 12); // 调用缺省构造函数
}

class Date
{
    public :
        Date()
        {}
        // 拷贝构造函数
        Date (const Date &d)
        {
            cout << "Date( & )" << endl;
            _year = d ._year;
            _month = d ._month;
            _day = d ._day;
        }
    private :
        int _year ;
        int _month ;
        int _day ;
};
void TestDate1 ()
{
    Date d1 ;
    // 下面两种用法都是调用拷贝构造函数，是等价的。
    Date d2 (d1); // 调用拷贝构造函数
    Date d3 = d1; // 调用拷贝构造函数
}

#include <malloc.h>
class Array
{
    public :
        Array (int size)
        {
            cout << "申请空间" << endl;
            _ptr = (int *)malloc( size * sizeof (int) );

        }
        // 这里的析构函数需要完成清(shi)理(fang)工(kong)作(jian)。
        ~ Array ()
        {
            cout << "释放空间" << endl;
            if (_ptr )
            {
                free(_ptr );
                _ptr = 0;
            }
        }
    private :
        int *_ptr ;
};

void Test05()
{
    Array arr(5);
}


class Date
{
    public :
        Date(int t_year, int t_month, int t_day)
            :_year(t_year), _month(t_month), _day(t_day)
        {
            cout << "Date() " << endl;
        }
        // 拷贝构造函数
        /*    Date (const Date &d)
              : _year(d._year)
              , _month(d._month)
              , _day(d._day)
              {
              cout << "拷贝构造" << endl;
              } */
        // 赋值操作符的重载
        // 1.思考为什么operator=赋值函数需要一个 Date& 的返回值，使用void做返回值可以吗？请验证
        void operator= (const Date& d)
        {
            cout << "赋值操作符的重载" << endl;
            // 2.这里的if条件判断是在检查什么？
            //   防止自己给自己赋值
            if (this != &d)
            {
                this->_year = d. _year;
                this->_month = d. _month;
                this->_day = d. _day;
            }
            // return *this ;
        }
        void print()
        {
            cout << _year << "-" << _month << "-" << _day << endl;
        }
        void SetDate(int t_year, int t_month, int t_day)
        {
            cout << "SetDate(...) " << endl;
            this->_year = t_year;
            this->_month = t_month;
            this->_day = t_day;
        }
    private:
        int _year ;
        int _month ;
        int _day ;
};

void Test06 ()
{
    Date d1(2018, 7, 20) ;
    Date d2 = d1; // 调用拷贝构造函数
    d1.print();
    d2.print();
    d1.SetDate(2017, 1, 1);
    d2.print();
    Date d3(2018, 7, 21) ;
    d3.print();
    d3 = d1 ; // 调用赋值运算符的重载
    d3.print();
}

class TestCls{
    public:
        int a;
        int *p;

    public:
        TestCls(int _a = 0)   //无参构造函数
            :a(_a)
        {
            std::cout<<"TestCls()"<<std::endl;
            // p = new int;
        }

        ~TestCls()     //析构函数
        {
            // delete p;   
            std::cout<<"~TestCls()"<<std::endl;
        }
        void Set_a(int _a)
        {
            a = _a;
        }
        void print()
        {
            cout << a << endl;
            cout << &a << endl;
            cout << p << endl;
        }
    private:
        // 这样这个类就不可以被拷贝了
        /* TestCls(const TestCls& ts)
           {} */
};
void Test07()
{
    TestCls tc1(100);
    TestCls tc2 = tc1;
    tc1.print();
    tc2.print();
    tc2.Set_a(200);
    tc1.print();
    tc2.print();
}


class Time
{
    public :
        Time (const Time &t)
        {
            cout << "Time (const Time& t)" << endl;
            _hour = t._hour;
            _minute = t._minute;
            _second = t._second;
        }
    private:
        int _hour ;
        int _minute ;
        int _second ;
};
class Date
{
    public :
        Date (int year, int month , int day, const Time &t)
            :_testConst(100), _testReference(_year), _t(t)
        {
            cout << "Date ()" << endl;
            _year = year ;
            _month = month ;
            _day = day ;
            _t = t ;
        }
    private :
        int _year ; // 年
        int _month ; // 月
        int _day ; // 日
        const int _testConst; // 1.测试const 成员变量的初始化
        int &_testReference ; // 2.测试引用成员变量的初始化
        Time _t ; // 3.测试无缺省构造函数的成员变量的初始化
};

void Test08()
{
    Time tm;
    Date dt(2018, 7, 20, tm);
}


#include<vector>

class MaxSum {
    public:
        int getMaxSum(vector<int> A, int n) {
            if(n == 0)
              return 0;
            int cur_sum = 0;
            int max_sum = 0;
            for(int i=0; i<n; i++)
            {
                cur_sum += A[i];
                if(cur_sum > max_sum)
                  max_sum = cur_sum;
                else if(cur_sum < 0)
                  cur_sum = 0;
            }
            return max_sum;
            // write code here
        }
};

void Test09()
{
    MaxSum m;
    vector<int> arr;
    arr.push_back(1);
    arr.push_back(-6);
    //arr.push_back(2);
    //arr.push_back(3);
    arr.push_back(1);
    arr.push_back(2);
    arr.push_back(3);
    int ret = m.getMaxSum(arr, arr.size());
    cout << ret << endl;
}

#endif

#include <vector>

void print(const vector<int>& v)
{
    for(size_t i=0; i<v.size(); ++i)
    {
        // for + operator[]
        cout << v[i] << " ";
    }
    cout << endl;
}

void test_vector()
{
    vector<int> v1;
    // 1. push_back
    v1.push_back(1);
    v1.push_back(2);
    v1.push_back(3);
    v1.push_back(4);
    v1.push_back(5);
    print(v1);
    // 2. 迭代器
    vector<int>::iterator it = v1.begin();
    while(it != v1.end())
    {
        cout << *it << " ";
        ++it;
    }
    cout << endl;
    // 3. const 迭代器
    vector<int>::const_iterator const_it = v1.begin();
    while(const_it != v1.end())
    {
        cout << *const_it << " ";
        // *const_it = 99; // 不能修改
        ++const_it;
    }
    cout << endl;
    // 4. 反向迭代器
    vector<int>::reverse_iterator reverse_it = v1.rbegin();
    while(reverse_it != v1.rend())
    {
        cout << *reverse_it << " ";
        ++reverse_it;
    }
    cout << endl;
    // 5. assign
    // template <class InputIterator>
    // void assign (InputIterator first, InputIterator last);
    // void assign (size_type n, const value_type& val);
    v1.assign(10, 100);
    print(v1);
    vector<int> v2(10, 99);
    v1.assign(v2.begin(), v2.end());
    print(v1);
    v1.assign(v2.begin()+1, v2.end()-1);
    print(v1);
}

// 1/1+2 + 1/1+2+3 + 1/1+2+3+4 + ... + 1/1+2+3+ ... +10
float sum(float x)
{
    float fenmu = 1;
    float sum = 1/fenmu;
 //   cout << "fenmu: " << fenmu << endl;
 //   cout << "sum: " << sum << endl;
    for(int i=fenmu+1; i<=x; i++)
    {
        fenmu += i;
 //       cout << "fenmu: " << fenmu << endl;
        sum += 1.0/fenmu;
 //       cout << "sum: " << sum << endl;
    }
    return sum;
}

int main()
{
    // Test01();
    // TestReference3();
    // TestReference4();
    // Test02();
    // Test03();
    // Test04();
    // Test();
    // TestDate1();
    // Test05();
    // Test06();
    // Test07();
    // Test09();
    // test_vector();
    cout << sum(10) << endl;
    return 0;
}
