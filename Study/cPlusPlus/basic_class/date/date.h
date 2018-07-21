#include<iostream>

using namespace std;

// 日期类
// 四个主要的默认成员函数
//   1. 构造函数
//   2. 析构函数
//   3. 拷贝构造函数
//   4. 赋值操作符重载
class Date
{
    public:
        //   1. 构造函数
        Date(int t_year, int t_month, int t_day)
            :m_year(t_year), m_month(t_month), m_day(t_day)
        {
            cout << "Date(...)" <<endl;
            if (!(m_year >= 1900
                            && m_month > 0 && m_month < 13
                            && m_day > 0 && m_day <= GetMonthDay(m_year, m_month)))
            {
                cout << "非法日期" << endl;
            }
        }

        //   2. 析构函数
        ~Date()
        {
            cout << "~Date()" <<endl;
        }

        //   3. 拷贝构造函数
        Date(const Date& date)
        {
            cout << "Date(const Date& date)" << endl;
            m_year = date.m_year;
            m_month = date.m_month;
            m_day = date.m_day;
        }

        //   4. 赋值操作符重载
        Date& operator=(const Date& date)
        {
            cout << "operator=(...)" <<endl;
            if(this != &date)
            {
                m_year = date.m_year;
                m_month = date.m_month;
                m_day = date.m_day;
            }
            return *this;
        }

        // 设定日期
        void SetDate(int t_year, int t_month, int t_day)
        {
            if(t_year < 1900 || t_month < 1 || t_month > 12 || t_day < 1 || t_day > GetMonthDay(t_year, t_month))
            {
                cout << "非法日期" << endl;
                return ;
            }
            m_year = t_year;
            m_month = t_month;
            m_day = t_day;
        }

        // 显示日期
        void Display()
        {
            cout << m_year << "-" << m_month << "-" << m_day << endl;
        }

        // 获得某个月的天数
        int GetMonthDay(const int& t_year, const int& t_month)
        {
            if(t_year < 1900 || t_month < 1 || t_month > 12)
              return -1;
            int days[13] = {0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
            if(t_month == 2)
            {
                if((t_year % 4 == 0 && t_year % 100 != 0)
                            || t_year % 400 == 0)
                {
                    return days[2] + 1;
                }
            }
            return days[t_month];
        }

        // 重载 + 运算符
        // 2018-7-6 + 100天 = ?
        Date operator+ (int days)
        {
            if(days == 0)
              return *this;
            Date ret = *this;
            ret.m_day += days;
            while(ret.m_day > GetMonthDay(ret.m_year, ret.m_month))
            {
                ret.m_day -= GetMonthDay(ret.m_year, ret.m_month);
                ++ret.m_month;
                if(ret.m_month > 12)
                {
                    ++ret.m_year;
                    ret.m_month = 1;
                }
            }
            return ret;
        }

        Date& operator+= (int days)
        {
            *this = *this + days;
            return *this;
        }

        // 重载 += 运算符
        // 2018-7-6 += 100天 = ?
        // Date operator+= (int days)
        // {
        //     ;
        // }

        // 重载 + - > < == != >= <= & 运算符
        // Date operator+(int day);
        

        bool operator!= (const Date& d)
        {
            return !(*this == d);
        }
        // 日期 - 天数
        Date operator-(int day)
        {
            Date ret(*this);
            ret.m_day -= day;
            while(ret.m_day <= 0)
            {
                ret.m_month--;
                if(ret.m_month == 0)
                {
                    ret.m_year--;
                }
                ret.m_day += GetMonthDay(ret.m_year, ret.m_month);
            }
            return ret;
        }

        // 日期 - 日期
        int operator-(const Date& d)
        {
            if(this == &d)
              return 0;
            Date min(d);
            Date max(*this);
            int count = 0;
            while(min != max)
            {
                min++;
                count++;
            }
            return count;
        }

        Date operator++(int)
        {
            *this += 1;
            return *this;
        }

        bool operator>(const Date& x)
        {
            if(m_year < x.m_year)
              return false;
            else if(m_year > x.m_year)
              return true;
            else
            {
              if(m_month < x.m_month)
                return false;
              else if(m_month > x.m_month)
                return true;
              else
              {
                  if(m_day <= x.m_day)
                    return false;
                  else if(m_day > x.m_day)
                    return true;
              }
            }
            return false;
        }

        bool operator< (const Date& d)
        {
            return !(*this == d || *this > d);
        }

        bool operator==(const Date& x)
        {
            return m_year == x.m_year &&
                   m_month == x.m_month &&
                   m_day == x.m_day;
        }

        bool operator>=(const Date& x)
        {
            return !(*this < x);
        }

        bool operator<=(const Date& x)
        {
            return !(*this > x);
        }

        Date* operator& (const Date& x)
        {
            return this;
            // return NULL;
        }


    private:
        int m_year;
        int m_month;
        int m_day;
};

