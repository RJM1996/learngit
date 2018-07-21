#include<iostream>
#include<vector>
using namespace std;

class Solution {
    public:
        int removeElement(vector<int>& nums, int val) {
            size_t size = (size_t)nums.size();
            if(size == 0)
              return 0;
            vector<int>::iterator it = nums.begin(); // 迭代器
            while(it != nums.end())
            {
                if(*it == val)
                  nums.erase(it); // erase 删除指定位置的元素
                else
                  it++;
            }
            return nums.size();
        }
};

int main()
{
    Solution s;
    vector<int> nums;
    // nums.push_back(0);
    // nums.push_back(1);
    // nums.push_back(2);
    // nums.push_back(2);
    // nums.push_back(3);
    // nums.push_back(0);
    // nums.push_back(4);
    // nums.push_back(2);
    nums.push_back(2);
    nums.push_back(2);
    nums.push_back(2);
    nums.push_back(0);
    nums.push_back(0);
    int len = s.removeElement(nums, 0);
    for(int i = 0; i < len; i++)
    {
        cout << nums[i] << " ";
    }
    cout << endl;
    return 0;
}
