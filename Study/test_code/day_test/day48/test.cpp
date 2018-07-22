
// 字符串去重
#include<iostream>
#include<string>
#include<malloc.h>

using namespace std;

void CharSet(string& str)
{
    string ret(100, '\0');
    int flag = 0;
    size_t str_size = str.size();
    size_t i = 0;
    size_t j = 0;
    for(i=0; i<str_size; i++)
    {
        for(j=0; j<100; j++)
        {
            if(ret[j] == str[i])
            {
                flag = 1;
                break;
            }
        }
        if(flag != 1)
        {
            ret[i] = str[i];
        }
    }
    cout << ret << endl;
    cout << ret[0] << endl;
    cout << ret[1] << endl;
    cout << ret[2] << endl;
    cout << ret[3] << endl;
}

int main()
{
    string str;
    while(getline(cin, str))
    {
        CharSet(str);
    }
    return 0;
}
