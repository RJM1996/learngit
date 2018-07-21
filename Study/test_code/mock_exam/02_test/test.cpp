/*================================================================

# File Name: test.cpp
# Author: rjm
# mail: rjm96@foxmail.com
# Created Time: 2018年06月14日 星期四 20时49分08秒

================================================================*/



#include <iostream>
#include <vector>

using namespace std;

class TwoStacks
{
    public:
        vector<int> twoStacksSort(vector<int> numbers)
        {
            vector<int> ans;
            int len = numbers.size();
            if(len == 0)
              return ans;
            while(numbers.size() != 0)
            {
                int tmp = numbers.back(); // 传回最后一个数据，不检查这个数据是否存在
                numbers.pop_back(); // 删除最后一个数据
                while(ans.size() != 0 && tmp < ans.back())
                {
                    numbers.push_back(ans.back());
                    ans.pop_back(); // 删除最后一个数据
                }
                ans.push_back(tmp);
            }
            while(ans.size() != 0)
            {
                numbers.push_back(ans.back());
                ans.pop_back();
            }
            return numbers;
        }
};

int main()
{
    TwoStacks ts;
    int a[] = {5, 3, 4, 1, 2, 7, 9, 6, 8};
    int size = sizeof(a)/sizeof(a[0]);
    vector<int> arr(a, a+size);
    for(int i=0; i<arr.size(); i++)
    {
        cout << arr[i] << " ";
    }
    cout << endl;

    vector<int> ret = ts.twoStacksSort(arr);
    for(int i=0; i<ret.size(); i++)
    {
        cout << ret[i] << " ";
    }
    cout << endl;
    
}
