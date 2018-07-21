/*================================================================

# File Name: binary_search_tree.c
# Author: rjm
# mail: rjm96@foxmail.com
# Created Time: 2018年05月13日 星期日 16时45分20秒

================================================================*/

#include <stdio.h>
#include <stdlib.h>
#include "binary_search_tree.h"

//初始化
void SearchTreeInit(SearchTreeNode **root)
{
    if(root == NULL)
    {
        //非法输入
        return ;
    }
    *root = NULL;
}

SearchTreeNode* CreateNewNode(SearchTreeType key)
{
    SearchTreeNode* tmp = (SearchTreeNode*)malloc(sizeof(SearchTreeType));
    tmp->key = key;
    return tmp;
}

#if 0

// 递归版本

//插入
void SearchTreeInsert(SearchTreeNode **root, SearchTreeType key)
{
    if(root == NULL)
    {
        //非法输入
        return ;
    }
    SearchTreeNode* new_node = CreateNewNode(key);
    if(*root == NULL)
    {
        //如果根节点为空, 直接插到根节点
        *root = new_node;
        return ;
    }
    if(key > (*root)->key)
    {
        SearchTreeInsert(&(*root)->rchild, key);
    }
    if(key < (*root)->key)
    {
        SearchTreeInsert(&(*root)->lchild, key);
    }
}

//查找
SearchTreeNode* SearchTreeFind(SearchTreeNode *root, SearchTreeType to_find)
{
    if(root == NULL)
      return NULL;
    if(to_find == root->key)
    {
        return root;
    }
    if(to_find > root->key)
    {
        return SearchTreeFind(root->rchild, to_find);
    }
    if(to_find < root->key)
    {
        return SearchTreeFind(root->lchild, to_find);
    }
    return NULL;
}

void RemoveNode(SearchTreeNode** root, SearchTreeType key)
{
    if(root == NULL)
      return ;
    if((*root) == NULL)
      return ;
    SearchTreeNode* tmp = NULL;
    //如果该节点没有子树, 则直接删除
    if((*root)->lchild == NULL && (*root)->rchild == NULL)
    {
        free(*root);
        *root = NULL;
        return ;
    }
    //如果该节点只有左右一棵子树, 则将其子树接到其父节点后面, 然后删除该节点
    else if((*root)->rchild == NULL)
    {
        tmp = (*root);
        (*root) = (*root)->lchild;
        free(tmp);
        tmp = NULL;
        return ;
    }
    else if((*root)->lchild == NULL)
    {
        tmp = (*root);
        (*root) = (*root)->rchild;
        free(tmp);
        tmp = NULL;
        return ;
    }
    //如果左右子树都不为空
    else
    {
        SearchTreeNode* Inorder_pre = NULL;
        tmp = (*root);
        Inorder_pre = (*root)->lchild;
        //找到该节点的中序前驱节点
        while(Inorder_pre->rchild != NULL)
        {
            Inorder_pre = Inorder_pre->rchild;
        }
        (*root)->key = Inorder_pre->key;
        RemoveNode(&(*root)->lchild, Inorder_pre->key);
        return ;
    }
}

//删除
void SearchTreeRemove(SearchTreeNode **root, SearchTreeType key)
{
    if(root == NULL)
      return ;
    if((*root) == NULL)
      //空树
      return ;
    //1,要删除的没找到 直接返回
    //2,如果要删除的元素没子树 直接将其父节点对应的指针指向null 释放内存
    //3,要删除的元素只有一棵子树 让其父节点指向当前节点的子树 释放内存
    //4,要删除的元素有两棵子树 将其与它的右子树的最小节点(或者左子树的最大节点)交换 
    //  再尝试递归地删除它
    if(key > (*root)->key)
    {
        SearchTreeRemove(&(*root)->rchild, key);
    }
    else if(key < (*root)->key)
    {
        SearchTreeRemove(&(*root)->lchild, key);
    }
    else
    {
        RemoveNode(root, key);
    }
}
#endif
//================================================================

#if 1
//非递归版本

//插入
void SearchTreeInsert(SearchTreeNode **root, SearchTreeType key)
{
    if(root == NULL)
      // 非法输入
      return ;
    // 根据要插入的值, 创建一个要插入的节点
    SearchTreeNode* to_insert = CreateNewNode(key);
    to_insert->lchild = NULL;
    to_insert->rchild = NULL;
    // 将cur指向根节点
    SearchTreeNode* cur = *root;
    // 保存父节点
    SearchTreeNode* parent = cur;
    // 循环遍历, 找到cur为 NULL
    while(cur != NULL)
    {
        parent = cur;
        if(key > cur->key)
        {
            cur = cur->rchild;
        }
        else if(key < cur->key)
        {
            cur = cur->lchild;
        }
        else
        {
            //元素相同, 插入失败
            return ;
        }
    }

    // 根节点为空, 说明是空树
    if(parent == NULL)
    {
        // 如果为空树, 直接插到根节点
        *root = to_insert;
    }
    else if(key > parent->key)
    {
        // 如果要插入的值比parent要大, 就插到它的右子树
        parent->rchild = to_insert;
    }
    else if(key < parent->key)
    {
        // 如果要插入的值比parent要小, 就插到它的左子树
        parent->lchild = to_insert;
    }
    else
    {
        // 元素相同, 插入失败
        return ;
    }
}

//查找
SearchTreeNode* SearchTreeFind(SearchTreeNode *root, SearchTreeType to_find)
{
    if(root == NULL)
      // 空树, 找不到
      return NULL;
    if(root->key == to_find)
      return root;
    SearchTreeNode* cur = root;
    while(cur != NULL)
    {
        if(cur->key > to_find)
        {
            cur = cur->lchild;
        }
        if(cur->key < to_find)
        {
            cur = cur->rchild;
        }
        else
        {
            return cur;
        }
    }
    return NULL;
}

void RemoveNode_NoRecur(SearchTreeNode** root, SearchTreeNode* cur, SearchTreeNode* parent)
{
    if(root == NULL)
      // 非法输入
      return ;
    if(*root == NULL)
      // 空树
      return ;

    // 1, 要删除的节点没有左子树(只有右子树或者左右子树都没有)
    if(cur->lchild == NULL)
    {
        if(cur == *root)
        {
            *root = cur->rchild;
        }
        else
        {
            if(cur == parent->lchild)
            {
                parent->lchild = cur->rchild;
            }
            else
            {
                parent->rchild = cur->rchild;
            }
        }
    }
    // 2, 要删除的节点没有右子树(只有左子树或者左右子树都没有)
    if(cur->rchild == NULL)
    {
        if(cur == *root)
        {
            *root = cur->lchild;
        }
        else
        {
            if(cur == parent->lchild)
            {
                parent->lchild = cur->lchild;
            }
            else
            {
                parent->rchild = cur->lchild;
            }
        }
    }

    // 3, 如果待删除节点的左右子树都不为空
    //    则在其右子树中找出最小的节点, 替换待删除节点, 然后删除那个最小的节点
    if(cur->rchild != NULL && cur->lchild != NULL)
    {
        SearchTreeNode* right_min = cur->rchild;
        parent = right_min;
        while(right_min->lchild != NULL)
        {
            parent = right_min;
            right_min = right_min->lchild;
        }
        cur->key = right_min->key;
        if(right_min == parent->lchild)
        {
            parent->lchild = right_min->rchild;
        }
        else
        {
            parent->rchild = right_min->rchild;
        }
        cur = right_min;
        free(right_min);
        right_min = NULL;
    }
    return ;
}

//删除
void SearchTreeRemove(SearchTreeNode **root, SearchTreeType key)
{
    if(root == NULL)
    {
        // 非法输入
        return ;
    }
    if(*root == NULL)
    {
        // 空树
        return ;
    }

    SearchTreeNode* cur = *root; // cur是待删除的节点
    SearchTreeNode* parent = cur; // parent是cur的父节点

    // 先找到待删除的节点 cur
    while(cur != NULL)
    {
        if(key < cur->key)
        {
            parent = cur;
            cur = cur->lchild;
        }
        else if(key > cur->key)
        {
            parent = cur;
            cur = cur->rchild;
        }
        else
        {
            // 到这里说明找到了要删除的元素
            break;
        }
    }
    if(cur == NULL)
    {
        printf("要删除的元素不存在\n");
        return ;
    }

    // 到这里说明要删除的元素存在, 开始分情况讨论
    RemoveNode_NoRecur(root, cur, parent);
    return ;
}


#endif

void SearchTreeInorder(SearchTreeNode* root)
{
    if(root == NULL)
      return ;
    SearchTreeInorder(root->lchild);
    printf("[%d]", root->key);
    SearchTreeInorder(root->rchild);
}

void SearchTreePreorder(SearchTreeNode* root)
{
    if(root == NULL)
      return ;
    printf("[%d]", root->key);
    SearchTreePreorder(root->lchild);
    SearchTreePreorder(root->rchild);
}
//////////////////////////////////////////////
//测试代码
//////////////////////////////////////////////
void TestInsert()
{
    TEST_HEAD;
    SearchTreeNode* mytree;
    SearchTreeInit(&mytree); 
    SearchTreeInsert(&mytree, 1);
    SearchTreeInsert(&mytree, 3);
    SearchTreeInsert(&mytree, 5);
    SearchTreeInsert(&mytree, 7);
    SearchTreeInsert(&mytree, 8);
    SearchTreeInsert(&mytree, 2);
    SearchTreeInsert(&mytree, 4);
    SearchTreeInsert(&mytree, 6);
    SearchTreeInsert(&mytree, 9);

    printf("\n中序遍历\n");
    SearchTreeInorder(mytree);
    printf("\n前序遍历\n");
    SearchTreePreorder(mytree);
    printf("\n");
}

void TestFind()
{
    TEST_HEAD;
    SearchTreeNode* mytree;
    SearchTreeInit(&mytree); 
    SearchTreeInsert(&mytree, 1);
    SearchTreeInsert(&mytree, 3);
    SearchTreeInsert(&mytree, 5);
    SearchTreeInsert(&mytree, 7);
    SearchTreeInsert(&mytree, 2);
    SearchTreeInsert(&mytree, 4);
    SearchTreeInsert(&mytree, 9);

    SearchTreeNode* ret = SearchTreeFind(mytree, 9);
    if(ret == NULL)
    {
        printf("\n没找到\n");
        return ;
    }
    else
    {
        printf("expected [9], actual [%p|%d]\n", ret, ret->key);
    }
}

//测试删除
void TestRemove()
{
    TEST_HEAD;
    SearchTreeNode* mytree;
    SearchTreeInit(&mytree); 
    SearchTreeInsert(&mytree, 4);
    SearchTreeInsert(&mytree, 2);
    SearchTreeInsert(&mytree, 6);
    SearchTreeInsert(&mytree, 1);
    SearchTreeInsert(&mytree, 3);
    SearchTreeInsert(&mytree, 5);
    SearchTreeInsert(&mytree, 7);
    SearchTreeInsert(&mytree, 8);
    printf("\n===删除前===\n");
    SearchTreeInorder(mytree);
    printf("\n");
    SearchTreePreorder(mytree);
    printf("\n");

    //SearchTreeRemove(&mytree, 4);
    //printf("\n===删除有两棵子树的节点 4 ===\n");
    //SearchTreeInorder(mytree);
    //printf("\n");
    //SearchTreePreorder(mytree);
    //printf("\n");

    SearchTreeRemove(&mytree, 8);
    SearchTreeRemove(&mytree, 7);
    printf("\n===删除两个元素 8 7 ===\n");
    SearchTreeInorder(mytree);
    printf("\n");
    SearchTreePreorder(mytree);
    printf("\n");

    SearchTreeRemove(&mytree, 3);
    SearchTreeRemove(&mytree, 1);
    printf("\n===再删除两个元素 1 3 ===\n");
    SearchTreeInorder(mytree);
    printf("\n");
    SearchTreePreorder(mytree);
    printf("\n");

    SearchTreeRemove(&mytree, 5);
    SearchTreeRemove(&mytree, 6);
    printf("\n===再删除两个元素 5 6 ===\n");
    SearchTreeInorder(mytree);
    printf("\n");
    SearchTreePreorder(mytree);
    printf("\n");

    SearchTreeRemove(&mytree, 2);
    printf("\n===再删除一个元素 2 ===\n");
    SearchTreeInorder(mytree);
    printf("\n");
    SearchTreePreorder(mytree);
    printf("\n");

    SearchTreeRemove(&mytree, 4);
    printf("\n===再删除一个元素 4 ===\n");
    SearchTreeInorder(mytree);
    printf("\n");
    SearchTreePreorder(mytree);
    printf("\n");

    SearchTreeRemove(&mytree, 4);
    printf("\n===对空树删除 ===\n");
    SearchTreeInorder(mytree);
    printf("\n");
    SearchTreePreorder(mytree);
    printf("\n");

}

int main()
{
    TestInsert();
    TestFind();
    TestRemove();

    printf("\n");
    printf("\n");
    printf("\n");
    return 0;
}
