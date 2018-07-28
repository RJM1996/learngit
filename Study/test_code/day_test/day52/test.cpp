#include <iostream>

// n 为整数的个数
// sum 和
// arr: n 个整数的数组
int MaxMethodSum(int n, int sum, int* arr)
{
    int ret = 0;
    int count = 0;
    for(int i=0; i<n; ++i)
    {
        ret += arr[i];
        if(ret == sum)
        {
            count++;
        }
    }
    return count;
}

int main()
{
    int n = 0;
    int sum = 0;
    int* arr;
    std::cin >> n >> sum;
    for(int i=0; i<n; ++i)
    {
        std::cin >> arr[i];
    }
    int ret = MaxMethodSum(n, sum, arr);
    std::cout << ret << std::endl;
}
