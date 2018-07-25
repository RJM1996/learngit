#include <iostream>
#include <string>
using namespace std;

// 在字符串中找出连续最长的数字串
int Test01()
{
    string str;
    while( cin >> str  )
    {
        size_t i;
        size_t max = 0;
        string ss;
        string out;
        for(i = 0; i < str.size(); i++)
        {
            if(str[i] >= '0' && str[i] <= '9')
            {
                ss += str[i];
                while(str[i + 1] >= '0' && str[i + 1] <= '9')
                {
                    i++;
                    ss += str[i];
                }
                if(ss.size() > max)
                {
                    max = ss.size();
                    out = ss;
                }
                else if(ss.size() == max)
                    out += ss;
            }
            ss.clear();
        }
        cout << out << ',' << max << endl;
    }
    return 0;
}

// 和位 sum 的方法数
#include<iostream>
#include<vector>
using namespace std;

int Test02()
{
    int n, sum;
    cin >> n >> sum;

    vector<long long> a(sum + 1);
    vector<int> b(n);

    for(int i = 0; i < n; i++)
        cin >> b[i];
    
    a[0] = 1;

    for (int i = 0; i < n; i++)
        for (int j = sum; j >= b[i]; j--)
            a[j] += a[j - b[i]];

    cout << a[sum] << endl;
    return 0;
}

int main()
{
    // Test01();
    Test02();
    return 0;
}
