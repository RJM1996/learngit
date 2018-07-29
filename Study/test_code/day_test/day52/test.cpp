// n 为整数的个数
// sum 和
// arr: n 个整数的数组
#include<iostream>
#include<vector>
using namespace std;

int main() 
{
    int n, sum;
    cin>>n>>sum;

    vector<long long> a(sum+1);
    vector<int> b(n);

    for(int i=0; i<n; i++)
        cin>>b[i];
    a[0] = 1;

    // 动态规划 ??? 
    for (int i=0; i<n; i++)
        for (int j=sum; j>=b[i]; j--)
            a[j] += a[j-b[i]];

    cout<<a[sum]<<endl;
    return 0;
}
