
#include <iostream>
#include <string>

using namespace std;

// 返回最长的数字序列的长度, 并输出该数字序列, 如果有多个也一起输出
#if 0
unsigned int Continumax(char** pOutputstr,  char* intputstr)
{

}
#endif

int main()
{
    string str;
    while(cin >> str)
    {
        size_t i = 0;
        size_t max = 0;
        string tmp;
        string ret;
        for(i=0; i<str.size(); i++)
        {
            if(str[i] >= '0' && str[i] <= '9')
            {
                tmp += str[i];
                // 说明是数字
                while(str[i+1] >= '\0' && str[i+1] <= '\0')
                {
                    i++;
                    tmp += str[i];
                }
                if(tmp.size() > max)
                {
                    max = tmp.size();
                    ret = tmp;
                }
                else if(tmp.size() == max)
                {
                    ret += tmp;
                }
            }
            tmp.clear();
        }
        cout << ret << "," << max << endl;
    }
    return 0;
}
