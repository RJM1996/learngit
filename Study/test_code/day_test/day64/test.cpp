#include <iostream>
#include <vector>

using namespace std;

class Solution {
public:
    bool VerifySquenceOfBST(vector<int> sequence) {
        if(sequence.size() == 0)
            return false;
        return help(sequence, 0, sequence.size()-1);
    }

    bool help(vector<int> sequence, int left, int right)
    {
        if(left >= right)
            return true;
        int i = right;
        while(i > left && sequence[i-1] > sequence[right])
        {
            --i;
        }
        for(int j=i-1; j>=left; --j)
        {
            if(sequence[j] > sequence[right])
                return false;
        }
        return help(sequence, left, i-1) && 
               (help(sequence, i, right-1));
    }
};

int main()
{
    Solution s;
    vector<int> vc;
    vc.push_back(1);
    vc.push_back(4);
    vc.push_back(3);
    vc.push_back(6);
    vc.push_back(8);
    vc.push_back(7);
    vc.push_back(5);
    cout << s.VerifySquenceOfBST(vc) << endl;
}
