/*
   class Solution for a binary tree node.
   struct TreeNode {
   int val;
   TreeNode *left;
   TreeNode *right;
   TreeNode(int x) : val(x), left(NULL), right(NULL) {}
   };
*/
class Solution {
    // 思路 : 我们发现如果根节点是第 1 层
    // 那么 奇数层都是从左往右 , 偶数层都是从右往左
    // 所有 可以把每一层的层序遍历结果保存起来 , 再把偶数层的翻转 , 就可以达到要求了
    public:
        vector<vector<int>> zigzagLevelOrder(TreeNode* root) {
            int Level = TreeLevel(root);
            return LevelOrder(root, Level);
        }

        vector<vector<int>> LevelOrder(TreeNode* root, size_t Level) {
            // 层序遍历
            vector<vector<int>> ret(Level);
            if(root == NULL)
              return ret;
            // 借助队列 完成层序遍历
            std::queue<TreeNode*> my_queue;
            my_queue.push(root);
            size_t curLevel = 1; // 当前的层数
            size_t curLevelSize = 0; // 当前层的节点数

            while(!my_queue.empty() && curLevel <= Level)
            {
                curLevelSize = my_queue.size();

                while(curLevelSize > 0) // 一直访问到当前层的最后一个元素
                {
                    TreeNode* node = my_queue.front(); // 访问队首元素
                    my_queue.pop(); // 将队首元素出队列   
                    ret[curLevel-1].push_back(node->val);

                    if(node->left != NULL)
                      my_queue.push(node->left);
                    if(node->right != NULL)
                      my_queue.push(node->right);                       

                    --curLevelSize;
                } 


                if(curLevel % 2 == 0)
                {
                    std::reverse(ret[curLevel-1].begin(), ret[curLevel-1].end());
                }


                ++curLevel;
            }  
            return ret;
        }

        size_t TreeLevel(TreeNode* root) {
            if(root == NULL)
              return 0;
            int nLeft = TreeLevel(root->left);
            int nRight = TreeLevel(root->right);
            return 1 + (nLeft > nRight
                        ? TreeLevel(root->left) : TreeLevel(root->right));
        }
};
