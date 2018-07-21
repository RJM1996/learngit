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
    // ˼· : ���Ƿ���������ڵ��ǵ� 1 ��
    // ��ô �����㶼�Ǵ������� , ż���㶼�Ǵ�������
    // ���� ���԰�ÿһ��Ĳ����������������� , �ٰ�ż����ķ�ת , �Ϳ��ԴﵽҪ����
    public:
        vector<vector<int>> zigzagLevelOrder(TreeNode* root) {
            int Level = TreeLevel(root);
            return LevelOrder(root, Level);
        }

        vector<vector<int>> LevelOrder(TreeNode* root, size_t Level) {
            // �������
            vector<vector<int>> ret(Level);
            if(root == NULL)
              return ret;
            // �������� ��ɲ������
            std::queue<TreeNode*> my_queue;
            my_queue.push(root);
            size_t curLevel = 1; // ��ǰ�Ĳ���
            size_t curLevelSize = 0; // ��ǰ��Ľڵ���

            while(!my_queue.empty() && curLevel <= Level)
            {
                curLevelSize = my_queue.size();

                while(curLevelSize > 0) // һֱ���ʵ���ǰ������һ��Ԫ��
                {
                    TreeNode* node = my_queue.front(); // ���ʶ���Ԫ��
                    my_queue.pop(); // ������Ԫ�س�����   
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
