/*================================================================

# File Name: bitree_test.c
# Author: rjm
# mail: rjm96@foxmail.com
# Created Time: 2018年05月04日 星期五 12时15分18秒

================================================================*/

#include <stdio.h>
#include <unistd.h>
#include "binary_tree.h"

//二叉树经典试题


//1,前中后序遍历二叉树（非递归）
//  非递归遍历二叉树需要用到栈 

//栈初始化
void seqStackInit(seqStack* stack)
{
    if(stack == NULL)
      return ;
    stack->size = 0;
}
//入栈
void seqStackPush(seqStack* stack, BiTree node)
{
    if(stack == NULL)
      return ;
    stack->data[stack->size] = node;
    ++stack->size;
}
//出栈一个元素
void seqStackPop(seqStack* stack)
{
    if(stack == NULL)
      return ;
    if(stack->size == 0)
      //空栈
      return ;

    --stack->size;
}
//取栈顶元素
int seqStackTop(seqStack* stack, BiTree* node)
{
    if(stack == NULL)
      return 0;
    if(stack->size == 0)
      //空栈
      return 0;

    *node = stack->data[stack->size-1];
    return 1;
}

//前序
void PreOrderByLoop(BiTree tree)
{
    if(tree == NULL)
    {
        //空树
        return ;
    }
    //定义栈并初始化
    seqStack stack;
    seqStackInit(&stack);

    while(tree != NULL || (&stack)->size != 0)
    {
        while(tree != NULL)
        {
            seqStackPush(&stack, tree);
            //根
            printf("[%c] ", tree->data);
            //左
            tree = tree->lchild;
        }

        BiTree node;
        if(seqStackTop(&stack, &node) == 0)
          printf("seqStackTop error\n");
        seqStackPop(&stack);
        //右
        tree = node->rchild;
    }
}

//中序
void InOrderByLoop(BiTree tree)
{
    if(tree == NULL)
    {
        //空树
        return ;
    }
    //定义栈并初始化
    seqStack stack;
    seqStackInit(&stack);

    while(tree != NULL || (&stack)->size != 0)
    {
        //左
        while(tree != NULL)
        {
            seqStackPush(&stack, tree);
            tree = tree->lchild;
        }
        //根
        BiTree node;
        if(seqStackTop(&stack, &node) == 0)
          printf("seqStackTop error\n");
        seqStackPop(&stack);
        printf("[%c] ", node->data);
        //右
        tree = node->rchild;
    }
}
//后序
void PostOrderByLoop(BiTree tree)
{
    if(tree == NULL)
    {
        //空树
        return ;
    }
    //定义栈并初始化
    seqStack stack;
    seqStackInit(&stack);

    BiTree cur = tree;
    BiTree pre = NULL;

    while(1)
    {
        //将所有最左节点入栈
        while(cur != NULL)
        {
            seqStackPush(&stack, cur);
            cur = cur->lchild;
        }

        BiTree top;
        int ret = seqStackTop(&stack, &top);
        if(ret == 0)
        {
            printf("\n");
            return ;
        }
        if(top->rchild == NULL || top->rchild == pre)
        {
            usleep(1000);
            printf("[%c] ", top->data);
            pre = top;
            seqStackPop(&stack);
        }
        else
        {
            cur = top->rchild;
        }
    }
}

//交换节点函数
void Swap(BiTree* lchild, BiTree* rchild)
{
    BiTree tmp = *lchild;
    *lchild = *rchild;
    *rchild = tmp;
}
//求二叉树的镜像
void BiTreeMirror_ByRecur(BiTree tree)
{
    if(tree == NULL || (tree->lchild == NULL && tree->rchild == NULL))
      return ;

    Swap(&(tree->lchild), &(tree->rchild));
    //     BiTNode* tmp = tree->lchild;
    //     tree->lchild = tree->rchild;
    //     tree->rchild = tmp;

    if(tree->lchild != NULL)
      BiTreeMirror_ByRecur(tree->lchild);
    if(tree->rchild != NULL)
      BiTreeMirror_ByRecur(tree->rchild);
}
void BiTreeMirror_ByLoop(BiTree tree)
{
    if(tree == NULL || (tree->lchild == NULL && tree->rchild == NULL))
      return ;

    //定义栈并初始化
    seqStack stack;
    seqStackInit(&stack);

    while(tree != NULL || (&stack)->size != 0)
    {
        while(tree != NULL)
        {
            seqStackPush(&stack, tree);
            //根
            //交换
            Swap(&(tree->lchild), &(tree->rchild));
            //BiTNode* tmp = tree->lchild;
            //tree->lchild = tree->rchild;
            //tree->rchild = tmp;

            //左
            tree = tree->lchild;
        }

        BiTree node;
        if(seqStackTop(&stack, &node) == 0)
          printf("seqStackTop error\n");
        seqStackPop(&stack);
        //右
        tree = node->rchild;
    }

}

//判断是否为完全二叉树
int IsCompleteBiTree(BiTree tree)
{
    if(tree == NULL)
      return 0;

    //定义队列并初始化
    seqQueue queue;
    seqQueueInit(&queue);
    //层序遍历每个节点 
    seqQueuePush(&queue, *tree);

    int goto_stage_two = 0;

    BiTNode front;

    while(seqQueueFront(&queue, &front) == 1)
    {
        //1, 判断每个节点是否同时拥有左右子树
        if(goto_stage_two == 0) //阶段1 的判定规则
        {
            if((&front)->lchild != NULL && (&front)->rchild != NULL)
            {
                seqQueuePush(&queue, *(&front)->lchild);
                seqQueuePush(&queue, *(&front)->rchild);
            }
            else
            {
                //   如果不满足,那么如果
                //   a)此节点只有右子树 一定不是完全二叉树
                if((&front)->lchild == NULL && (&front)->rchild != NULL)
                  return 0;
                //   b)此节点只有左子树 进入阶段2继续判断
                if((&front)->lchild != NULL && (&front)->rchild == NULL)
                {
                    goto_stage_two = 1;
                    seqQueuePush(&queue, *(&front)->lchild);
                }
                //   c)此节点没有子树 进入阶段2继续判断
                if((&front)->lchild == NULL && (&front)->rchild == NULL)
                  goto_stage_two = 1;
            }
        }

        //2, 进入阶段2
        //   判断后面的节点是否都没有子树
        //   若有 则不是完全二叉树
        //   若没有 就是
        else if(goto_stage_two == 1) //阶段2 的判断
        {
            if((&front)->lchild == NULL && (&front)->rchild == NULL)
              ;
            else
              return 0;
        }
    }
    return 1;
}

//将二叉搜索树转换成一个排序的双向链表
//要求: 不能创建任何新的结点，只能调整树中结点指针的指向
//二叉查找树或者是一棵空树，或者是具有下列性质的二叉树:
//（1）若左子树不空，则左子树上所有结点的值均小于或等于它的根结点的值
//（2）若右子树不空，则右子树上所有结点的值均大于或等于它的根结点的值
//（3）左、右子树也分别为二叉排序树
//即二叉查找树的中序遍历结果是有序的
void BinarySortTree_to_DbLinkList(BiTree tree, BiTree pfront, BiTree ptail)
{
    BiTree pfrontLeft, pfrontRight, ptailLeft, ptailRight; 
    if(tree == NULL)
    {
        //如果是空树, 则双链表也是空, 头指针尾指针都是空
        pfront = NULL;
        ptail = NULL;
        return ;
    }

    //对左子树的操作
    if(tree->lchild == NULL)
    {
        //如果左子树为空, 双链表的第一个节点就是根节点
        pfront = tree;
    }
    else
    {
        //如果左子树不为空, 双链表的第一个节点就是最左边的那个节点
        BinarySortTree_to_DbLinkList(tree->lchild, pfrontLeft, ptailLeft);
        pfront = pfrontLeft;
        tree->lchild = ptailLeft;
        ptailLeft->rchild = tree;
    }

    //对右子树的操作
    if(tree->rchild == NULL)
    {
        //如果右子树为空, 双链表的最后一个节点就是根节点
        ptail = tree;
    }
    else
    {
        //如果右子树不为空, 双链表的最后一个节点就是最右边的那个节点
        BinarySortTree_to_DbLinkList(tree->rchild, pfrontRight, ptailRight);
        pfront = pfrontRight;
        tree->rchild = ptailRight;
        ptailRight->lchild = tree;
    }
}

///////////////////////////////////////////////////////
//测试代码
///////////////////////////////////////////////////////

// 见 binary_tree.c
