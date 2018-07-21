/*================================================================

# File Name: 02_test.cpp
# Author: rjm
# mail: rjm96@foxmail.com
# Created Time: 2018年06月25日 星期一 23时19分28秒

================================================================*/



#include <iostream>

using namespace std;

/**
 * Definition for binary tree
 * struct TreeNode {
 *     int val;
 *     TreeNode *left;
 *     TreeNode *right;
 *     TreeNode(int x) : val(x), left(NULL), right(NULL) {}
 * };
 **/
class Solution {
    public:
        void PostOrderTraverse(TreeNode* tree, vector<int> vec)
        {
            if(tree == NULL)
              return ;
            //中序: 左根右
            PostOrderTraverse(tree->lchild);
            PostOrderTraverse(tree->rchild);
            vec.push_back(tree->val);
        }

        vector<int> postorderTraversal(TreeNode *root) {
            if(root == NULL)
              return {};
            vector<int> vec;
            PostOrderTraverse(root, vec);
            return vec;
        }
};
