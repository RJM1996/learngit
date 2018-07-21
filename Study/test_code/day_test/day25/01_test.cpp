/*================================================================

# File Name: test.cpp
# Author: rjm
# mail: rjm96@foxmail.com
# Created Time: 2018年06月25日 星期一 22时59分47秒

================================================================*/


// 判断一棵二叉树是否为平衡二叉树

#include <iostream>

using namespace std;

class Solution {
    public:
        bool IsBalanced_Solution(TreeNode* pRoot, int* depth) {
            if(pRoot == NULL)
            {
                *depth = 0;
                return true;
            }
            int left_depth = 0;
            int right_depth = 0;
            if(IsBalanced_Solution(pRoot->left, &left_depth) 
            && IsBalanced_Solution(pRoot->right, &right_depth)) {
                int diff = left_depth - right_depth;
                if(diff <= 1 && diff >= -1) {
                    *depth = 1 + (left_depth > right_depth ? left_depth : right_depth);
                    return true;
                }
            }
            return false;
        }

        bool IsBalanced_Solution(TreeNode* pRoot) {
            int depth = 0;
            return IsBalanced_Solution(pRoot, &depth);
        }
};
