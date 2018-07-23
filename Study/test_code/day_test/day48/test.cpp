
// 字符串去重
#include<iostream>
#include<string>
#include<malloc.h>

using namespace std;

void CharSet(string& str)
{
    string ret;
    int flag = 0;
    size_t str_size = str.size();
    size_t i = 0;
    size_t j = 0;
    for(i=0; i<str_size; i++)
    {
        flag = 0;
        for(j=0; j<str_size; j++)
        {
            if(ret[j] == str[i])
            {
                flag = 1;
                break;
            }
        }

        if(flag != 1)
        {
            ret += str[i];
        }
    }
    cout << ret << endl;
}

bool Exist(char ch, string& str)
{
    size_t len = str.size();
    bool exist = false;
    for(size_t i=0; i<len; i++)
    {
        if(ch == str[i])
        {
            exist = true;
            return exist;
        }
    }
    return exist;
}

void Test()
{
    string str;
    while(cin >> str)
    {
        CharSet(str);
    }
}

int main()
{
    Test();
//    string str;
//    while(getline(cin, str))
//    {
//        string ret;
//        size_t len = str.size();
//        for(size_t i=0; i<len; i++)
//        {
//            if(Exist(str[i], ret) == false)
//            {
//                ret += str[i];
//            }
//        }
//        cout << ret << endl;
//    }
    return 0;
}
