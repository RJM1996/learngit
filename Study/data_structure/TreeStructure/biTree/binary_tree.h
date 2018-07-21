/*================================================================
  Copyright (C) 2018 Sangfor Ltd. All rights reserved.
# File Name: binary_tree.h
# Author: rjm
# mail: rjm96@foxmail.com
# Created Time: 2018年04月24日 星期二 17时42分20秒

================================================================*/

#pragma once

#define TEST_HEAD printf("\n\n=====%s=====\n\n", __FUNCTION__)

//定义树中的数据类型
typedef char DataType;

//定义树的节点
typedef struct BiTNode
{
    DataType data;//数据域
    struct BiTNode *lchild, *rchild;//指向左右孩子节点
}BiTNode, *BiTree;

//定义一个队列
typedef struct seqQueue
{
    BiTNode data[100];
    int size;
}seqQueue;

//队列初始化
void seqQueueInit(seqQueue* queue);
//入队列
void seqQueuePush(seqQueue* queue, BiTNode node);
//出队列并取队首元素
int seqQueueFront(seqQueue* queue, BiTNode* node);

//定义一个栈
typedef struct seqStack
{
    BiTree data[100];
    int size;
}seqStack;

//栈初始化
void seqStackInit(seqStack* stack);
//入栈
void seqStackPush(seqStack* stack, BiTree node);
//出栈
void seqStackPop(seqStack* stack);
//取栈顶元素
int seqStackTop(seqStack* stack, BiTree* node);


//二叉树的初始化
void InitBiTree(BiTree* tree); 
//创建二叉树(以键盘输入方式)
void CreateBiTree_void(BiTree* tree);
//二叉树创建(以数组方式)
BiTree CreateBiTree(DataType array[], size_t size, DataType null_node);
BiTree _CreateBiTree(DataType array[], size_t size, DataType null_node, size_t* index);
//层序遍历二叉树
void LevelOrderTraverse(BiTree tree, seqQueue* queue);

//销毁二叉树
void DestroyBiTree(BiTree* tree); 
//克隆二叉树
BiTree CloneBiTree(BiTree tree); 
//求二叉树的大小
size_t BiTreeSize(BiTree tree); 
//求一棵树的叶子节点个数 
size_t BiTreeLeafRootSize(BiTree tree); 
//求一棵树第 K 层节点的个数 
size_t BiTreeKlevelRootSize(BiTree tree, int K); 
//树的高度
size_t TreeHeight(BiTree tree); 

//树中找一个节点
BiTree TreeFind(BiTree tree, DataType to_find); 

//求一个节点的左右孩子节点
BiTree LChild(BiTree tree, BiTree node); 
BiTree RChild(BiTree tree, BiTree node); 

//求一个节点的父节点
BiTree Parent(BiTree tree, BiTree node); 

//前中后遍历 循环实现
void PreOrderByLoop(BiTree tree); 
void InOrderByLoop(BiTree tree); 
void PostOrderByLoop(BiTree tree); 

//镜像树
void BiTreeMirror_ByRecur(BiTree tree);
void BiTreeMirror_ByLoop(BiTree tree);

//判断是否为完全二叉树
int IsCompleteBiTree(BiTree tree);
