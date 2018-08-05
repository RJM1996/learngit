#include <bits/stdc++.h>
using namespace std;


void sumMethod()
{
    int n, sum;
    int arr[1001];
    cin >> n >> sum;
    for(int i=1; i<=n; i++)
    {
        cin >> arr[i];
    }

    long long dp[1001];
    dp[0] = 1;

    for(int i=1; i<=n; i++)
    {
        for(int j=sum; j>=arr[i]; j--)
        {
            dp[j] += dp[j - arr[i]];
        }
    }
    cout << dp[sum] << endl;
}

void delstr()
{
    string str1;
    string str2;
    getline(cin, str1);
    getline(cin, str2);
    int flag = 0;
    for(size_t i=0; i<str1.size(); i++)
    {
        flag = 0;
        for(size_t j=0; j<str2.size(); j++)
        {
            if(str1[i] == str2[j])
            {
                flag = 1;
            }
        }
        if(flag != 1)
        {
            cout << str1[i];
        }
    }
}

void beike()
{
    long long x = 0;
    cin >> x;
    long long cur = x;
    long long count = 0;
    while(count <= 100000)
    {
        count = 1;
        if((cur*4 + 3) % 1000000007 == 0)
        {
            cout << count;
            break;
        }
        else
        {
            if((cur*8 + 7) % 1000000007 == 0)
            {
                cout << count;
                break;
            }
            else
            {
                cur = 8*cur+7;
            }
            ++count;
        }

        if((cur*8+7) % 1000000007 == 0)
        {
            cout << count;
            break;
        }
        else
        {
            if((cur*4 + 3) % 1000000007 == 0)
            {
                cout << count;
                break;
            }
            else
            {
                cur = cur*4 + 3;
            }
            ++count;
        }
    }
    if(count > 100000)
        cout << -1;
}

int main ()
{
    // while(1)
    // {
    //     std::string name;
    //     std::cout << "Please, enter your full name: ";
    //     std::getline (std::cin, name);
    //     std::cout << name << std::endl;
    // }
    // sumMethod();
    beike();
    // delstr();
    return 0;
}
