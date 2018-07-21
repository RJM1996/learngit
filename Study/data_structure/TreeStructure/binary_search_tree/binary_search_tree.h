/*================================================================

# File Name: binary_search_tree.h
# Author: rjm
# mail: rjm96@foxmail.com
# Created Time: 2018年05月13日 星期日 16时45分43秒

================================================================*/
// 实现二叉搜索树的递归和非递归版本

#pragma once

#define TEST_HEAD printf("\n=======%s=======\n", __FUNCTION__)

typedef char SearchTreeType;

typedef struct SearchTreeNode
{
    SearchTreeType key; // 关键码
    struct SearchTreeNode *lchild;
    struct SearchTreeNode *rchild;

} SearchTreeNode;

//初始化
void SearchTreeInit(SearchTreeNode **root);
//插入
void SearchTreeInsert(SearchTreeNode **root, SearchTreeType key);
//查找
SearchTreeNode* SearchTreeFind(SearchTreeNode *root,
                               SearchTreeType to_find);
//删除
void SearchTreeRemove(SearchTreeNode **root, SearchTreeType key);
