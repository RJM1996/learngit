/*================================================================

# File Name: test.cpp
# Author: rjm
# mail: rjm96@foxmail.com
# Created Time: 2018年06月27日 星期三 14时15分34秒

================================================================*/



#include <iostream>

using namespace std;

// minimum-depth-of-binary-tree
// 求二叉树的最小深度

class Solution
{
    public:
        int run(TreeNode *root)
        {
            if(root == NULL)
            {
                return 0;
            }
            if(root->left == NULL && root->right == NULL)
            {
                return 1;
            }
            if(root->left == NULL)
            {
                return run(root->right) + 1;
            }
            if(root->right == NULL)
            {
                return run(root->left) + 1;
            }
            if(root->left != NULL && root->right != NULL)
            {
                int leftDepth = run(root->left) + 1;
                int rightDepth = run(root->right) + 1;
                return (leftDepth > rightDepth) ? rightDepth : leftDepth;
            }
            return 0;
        }
};

// 根据中序遍历和后序遍历结果构建二叉树

/**
 * Definition for binary tree
 * struct TreeNode {
 *     int val;
 *     TreeNode *left;
 *     TreeNode *right;
 *     TreeNode(int x) : val(x), left(NULL), right(NULL) {}
 * };
 **/
class Solution
{
    public:

        //在中序遍历序列中找到根结点的位置
        int findRoot(vector<int> &array, int start, int end, int key)
        {
            for (int i = start; i <= end; i++)
            {
                if (array[i] == key)
                {
                    return i;
                }
            }
            return -1;
        }

        TreeNode *build(vector<int> &inorder, int inStart, int inEnd, 
                    vector<int> &postorder, int postStart, int postEnd)
        {
            if (inStart > inEnd)
            {
                return NULL;
            }

            //根据后序遍历序列的最后一个数字建立根结点root
            TreeNode *root = new TreeNode(postorder[postEnd]);

            //获取根结点的位置position
            int position = findRoot(inorder, inStart, inEnd, postorder[postEnd]);
            //创建左子树
            root->left = build(inorder, inStart, position - 1, 
                        postorder, postStart, 
                        postStart + (position - inStart - 1));
            //创建右子树
            root->right = build(inorder, position + 1, inEnd, 
                        postorder, postStart + (position - inStart), 
                        postEnd - 1);

            return root;    //返回根结点
        }

        TreeNode *buildTree(vector<int> &inorder, vector<int> &postorder)
        {
            if(inorder.size() != postorder.size())
              return NULL;
            return build(inorder, 0, inorder.size() - 1, 
                        postorder, 0, postorder.size() - 1);
        }
};
