/*================================================================
 
# File Name: binary_tree.c
# Author: rjm
# mail: rjm96@foxmail.com
# Created Time: 2018年04月22日 星期日 20时33分20秒

================================================================*/


#include <stdio.h>
#include <stdlib.h>
#include "binary_tree.h"

//二叉树的初始化
void InitBiTree(BiTree* tree)
{
    if(tree == NULL)
      //非法输入
      return ;
    *tree = NULL;
}

/* * 
 * * @brief 根据前序遍历结果(带有空节点标记) 
 * * 构造一棵树 
 * * 
 * * @param array[] 前序遍历的结果 
 * * @param size 数组中元素个数 
 * * @param null_node 数组中空节点的特殊标记. 
 * * 
 * * @return 
 * */ 
BiTree _CreateBiTree(DataType array[], size_t size, DataType null_node, size_t* index)
{
    if(array == NULL)
      //非法输入
      return NULL;
    if(size == 0)
      //空数组, 返回空树
      return NULL;

    if(*index < size && array[*index] == null_node)
    {
        //创建一个空节点
        return NULL;
    }
    if(*index < size && array[*index] != null_node)
    {
        //给节点申请空间
        BiTree tree = (BiTree)malloc(sizeof(DataType));
        if(tree == NULL)
          //申请失败
          perror("malloc");


        (tree)->data = array[*index];
        (*index)++;
        (tree)->lchild = _CreateBiTree(array, size, null_node, index);
        (*index)++;
        (tree)->rchild = _CreateBiTree(array, size, null_node, index);
        return tree;
    }
    return NULL;
}

BiTree CreateBiTree(DataType array[], size_t size, DataType null_node)
{
    if(array == NULL)
      return NULL;
    if(size == 0)
      return NULL;

    size_t index = 0;

    BiTree tree =  _CreateBiTree(array, size, null_node, &index);
    return tree;
}

//创建二叉树
void CreateBiTree_void(BiTree* tree)
{
    if(tree == NULL)
    {
        //非法输入
        return ;
    }

    DataType value;
    scanf("%c", &value);
    if(value == '#')
    {
        // # 代表空节点
        *tree = NULL;
    }
    else
    {
        //给一个节点开辟空间
        *tree = (BiTree)malloc(sizeof(BiTNode));
        if(*tree == NULL)
        {
            //开辟失败, 退出
            perror("malloc");
            exit(0);
        }
        //前序遍历: 根左右
        //给节点赋值
        (*tree)->data = value;
        //创建左右孩子节点
        CreateBiTree_void(&(*tree)->lchild);
        CreateBiTree_void(&(*tree)->rchild);
    }
}


//输出二叉树的节点 所在层数
void PrintBiTree(DataType value, int tier)
{
    printf("[%c] 在第%02d层\n", value, tier);
}

//递归方式 前序遍历二叉树
void PreOrderTraverse(BiTree tree, int tier)
{
    if(tree == NULL)
      return ;
    //前序: 根左右
    PrintBiTree(tree->data, tier);
    PreOrderTraverse(tree->lchild, tier + 1);
    PreOrderTraverse(tree->rchild, tier + 1);
}
//递归方式 中序遍历二叉树
void InOrderTraverse(BiTree tree, int tier)
{
    if(tree == NULL)
      return ;
    //中序: 左根右
    InOrderTraverse(tree->lchild, tier + 1);
    PrintBiTree(tree->data, tier);
    InOrderTraverse(tree->rchild, tier + 1);
}
//递归方式 后序遍历二叉树
void PostOrderTraverse(BiTree tree, int tier)
{
    if(tree == NULL)
      return ;
    //中序: 左根右
    PostOrderTraverse(tree->lchild, tier + 1);
    PostOrderTraverse(tree->rchild, tier + 1);
    PrintBiTree(tree->data, tier);
}


//队列初始化
void seqQueueInit(seqQueue* queue)
{
    if(queue == NULL)
      return ;
    queue->size = 0;
}
//入队列
void seqQueuePush(seqQueue* queue, BiTNode node)
{
    if(queue == NULL)
      return ;
    queue->data[queue->size++] = node;
}
//出队列并取队首元素
int seqQueueFront(seqQueue* queue, BiTNode* node)
{
    if(queue == NULL)
      return 0;
    if(queue->size == 0)
    {
        //空队列
        return 0;
    }

    *node = queue->data[0];
    for(int i=0; i<queue->size-1; i++)
    {
        queue->data[i] = queue->data[i+1];
    }
    --queue->size;

    return 1;
}

//借助队列 层序遍历二叉树
void LevelOrderTraverse(BiTree tree, seqQueue* queue)
{
    if(tree == NULL)
      return ;

    //从根节点开始入队列
    seqQueuePush(queue, *tree);

    while(1)
    {
        //然后出队列一个节点,并访问(打印),如果它的左右孩子节点不是空,就把它的左右孩子节点入队列
        BiTNode node;
        int ret = seqQueueFront(queue, &node);
        if(ret == 0)
        {
            //队列为空 遍历完毕
            return ;
        }

        //打印 出队列的这个节点
        printf("[%c] ", node.data);

        //入队列它的左右孩子节点
        if((node).lchild != NULL)
        {
            seqQueuePush(queue, *(node.lchild));
        }
        if((node).rchild != NULL)
        {
            seqQueuePush(queue, *(node.rchild));
        }
    }
}

//销毁二叉树
void DestroyBiTree(BiTree* tree)
{
    //用后序遍历比较方便我们销毁, 因为它最后才访问根节点
    if(tree == NULL)
      //非法输入
      return ;
    if(*tree == NULL)
      //空树
      return ;
    DestroyBiTree(&(*tree)->lchild);
    DestroyBiTree(&(*tree)->rchild);
    free(*tree);
    *tree = NULL;
}

//BiTree CreatNode(BiTree* tree)
//{
//    if(tree == NULL)
//      return NULL;
//    if(*tree == NULL)
//      return NULL;
//    BiTree new_node = (BiTree)malloc(sizeof(DataType));
//    new_node.data = (*tree)->data;
//}

//克隆二叉树
BiTree CloneBiTree(BiTree tree)
{
    if(tree == NULL)
      //空树
      return NULL;
    BiTree new_tree = tree;
    CloneBiTree(tree->lchild);
    CloneBiTree(tree->rchild);
    return new_tree;
}

//求二叉树的大小
size_t BiTreeSize(BiTree tree)
{
    if(tree == NULL)
      //空树, 大小为 0
      return 0;
    return 1 + (BiTreeSize(tree->lchild)) + (BiTreeSize(tree->rchild));
}

//求一棵树的叶子节点个数 
size_t BiTreeLeafRootSize(BiTree tree)
{
    if(tree == NULL)
      //空树
      return 0;
    if(tree->lchild == NULL && tree->rchild == NULL)
    {
        return 1;
    }
    return BiTreeLeafRootSize(tree->lchild) + BiTreeLeafRootSize(tree->rchild);
}

//求一棵树第 K 层节点的个数 
size_t BiTreeKlevelRootSize(BiTree tree, int K)
{
    //大化小, 转化为求第 1 层节点的个数
    if(tree == NULL)
      //空树
      return 0;
    if(K == 1)
    {
        return 1;
    }
    return BiTreeKlevelRootSize(tree->lchild, K-1) + BiTreeKlevelRootSize(tree->rchild, K-1);
}


//树的深度
size_t TreeHeight(BiTree tree)
{
    if(tree == NULL)
      return 0;
    int nLeft = TreeHeight(tree->lchild);
    int nRight = TreeHeight(tree->rchild);
    //return 1 + (TreeHeight(tree->lchild) > TreeHeight(tree->rchild)
    //            ? TreeHeight(tree->lchild) : TreeHeight(tree->rchild));
    //            这种写法需要递归 3 次, 开销太大, 不推荐
    return 1 + (nLeft > nRight
                ? TreeHeight(tree->lchild) : TreeHeight(tree->rchild));
}
//树中找一个节点(前序遍历 递归版)
BiTree TreeFind(BiTree tree, DataType to_find)
{
    if(tree == NULL)
      //空树
      return NULL;
    if(tree->data == to_find)
    {
      return tree;
    }
    BiTree node = TreeFind(tree->lchild, to_find);
    if(node == NULL)
      return TreeFind(tree->rchild, to_find);
    else
      return node;
}
//查找节点(非递归版)
BiTree TreeFind_NoRecur(BiTree tree, DataType to_find, seqQueue* queue)
{
    if(tree == NULL)
      //空树
      return NULL;

    //从根节点开始入队列
    seqQueuePush(queue, *tree);

    while(1)
    {
        //然后出队列一个节点,如果它的左右孩子节点不是空,就把它的左右孩子节点入队列
        static BiTNode node;
        int ret = seqQueueFront(queue, &node);
        if(ret == 0)
        {
            //队列为空 遍历完毕
            return NULL;
        }

        //打印 出队列的这个节点
        //printf("[%c] ", node.data);
        //打印操作变为比较操作
        if(node.data == to_find)
          return &node;

        //入队列它的左右孩子节点
        if((node).lchild != NULL)
        {
            seqQueuePush(queue, *(node.lchild));
        }
        if((node).rchild != NULL)
        {
            seqQueuePush(queue, *(node.rchild));
        }
    }
}



BiTree LChild(BiTree tree, BiTree node)
{
    if(tree == NULL)
      //空树
      return NULL;
    if(node == NULL)
      //空节点, 没有孩子节点
      return NULL;
    return node->lchild;
}

BiTree RChild(BiTree tree, BiTree node)
{
    if(tree == NULL)
      //空树
      return NULL;
    if(node == NULL)
      //空节点, 没有孩子节点
      return NULL;
    return node->rchild;
}

BiTree Parent(BiTree tree, BiTree node)
{
    if(tree == NULL)
        //空树
        return NULL;
    if(node == NULL)
      //空节点的父节点, 不确定
      return NULL;
    if(tree->lchild == node || tree->rchild == node)
    {
        return tree;
    }
    BiTree father = Parent(tree->lchild, node);
    if(father == NULL)
      return NULL;
    else
      return Parent(tree->rchild, node);
}

//前中后遍历 循环实现
void PreOrderByLoop(BiTree tree); 

void InOrderByLoop(BiTree tree); 

void PostOrderByLoop(BiTree tree); 

//镜像树
void TreeMirror(BiTree tree); 
//判断是否为完全二叉树
int IsCompleteTree(BiTree tree);

////////////////////////////////////////////////
//测试代码
////////////////////////////////////////////////

//测试前序遍历
void TestPreOrder(BiTree tree, int tier)
{
    TEST_HEAD;

    printf("\n前序遍历输出二叉树\n");
    PreOrderTraverse(tree, tier);
}
//测试中序遍历
void TestInOrder(BiTree tree, int tier)
{
    TEST_HEAD;

    printf("\n中序遍历输出二叉树\n");
    InOrderTraverse(tree, tier);
}
//测试后序遍历
void TestPostOrder(BiTree tree, int tier)
{
    TEST_HEAD;

    printf("\n后序遍历输出二叉树\n");
    PostOrderTraverse(tree, tier);
}
//测试层序遍历
void TestLevelOrder(BiTree tree)
{
    TEST_HEAD;
    seqQueue queue;
    seqQueueInit(&queue);
    printf("\n层序遍历输出二叉树\n");
    LevelOrderTraverse(tree, &queue);
}
//测试二叉树创建(数组方式), 并前中后层序遍历
void TestBiTreeCreate()
{
    TEST_HEAD;
    DataType array[] = {"abd##eg###c#f##"};
    size_t size = sizeof(array)/sizeof(array[0]) - 1;

    BiTree tree = CreateBiTree(array, size, '#');
    int tier = 1;
    TestPreOrder(tree, tier);
    TestInOrder(tree, tier);
    TestPostOrder(tree, tier);
    TestLevelOrder(tree);
}

//测试二叉树的创建(无返回值, 从键盘输入), 并前中后层序遍历
void TestBiTreeCreate_void()
{
    TEST_HEAD;
    BiTree tree;
    int tier = 1;

    //创建二叉树
    printf("请以前序遍历方式输入二叉树('#'代表空节点) \n");
    CreateBiTree_void(&tree);

    TestPreOrder(tree, tier);
    TestInOrder(tree, tier);
    TestPostOrder(tree, tier);
    TestLevelOrder(tree);
}
//测试二叉树的销毁
void TestDestroy()
{
    TEST_HEAD;
    DataType array[] = {"abd##eg###c#f##"};
    size_t size = sizeof(array)/sizeof(array[0]) - 1;

    BiTree tree = CreateBiTree(array, size, '#');
    DestroyBiTree(&tree);
    int tier = 1;
    TestPreOrder(tree, tier);
    TestInOrder(tree, tier);
    TestPostOrder(tree, tier);
    TestLevelOrder(tree);
}

//测试二叉树的克隆
void TestClone()
{
    TEST_HEAD;
    DataType array[] = {"abd##eg###c#f##"};
    size_t size = sizeof(array)/sizeof(array[0]) - 1;

    BiTree tree = CreateBiTree(array, size, '#');
    BiTree new_tree = CloneBiTree(tree);
    int tier = 1;
    TestPreOrder(tree, tier);
    TestInOrder(tree, tier);
    TestPostOrder(tree, tier);
    TestLevelOrder(tree);
}

//测试二叉树的大小
void TestBiTreeSize()
{
    TEST_HEAD;
    DataType array[] = {"abd##eg###c#f##"};
    size_t size = sizeof(array)/sizeof(array[0]) - 1;

    BiTree tree = CreateBiTree(array, size, '#');
    size_t ret = BiTreeSize(tree);
    printf("ret expected 7, actual %d\n", ret);
    printf("销毁之后的求二叉树的大小\n");
    DestroyBiTree(&tree);
    size_t ret1 = BiTreeSize(tree);
    printf("ret expected 7, actual %d\n", ret1);
}

//测试二叉树叶子节点的个数
void TestLeafRootSize()
{
    TEST_HEAD;
    DataType array[] = {"abd##eg###c#f##"};
    size_t size = sizeof(array)/sizeof(array[0]) - 1;

    BiTree tree = CreateBiTree(array, size, '#');
    size_t ret = BiTreeLeafRootSize(tree);
    printf("ret expected 3, actual %d\n", ret);
}

//测试求第K层节点的个数
void TestKLevelRootSize()
{
    TEST_HEAD;
    DataType array[] = {"abd##eg###c#f##"};
    size_t size = sizeof(array)/sizeof(array[0]) - 1;

    BiTree tree = CreateBiTree(array, size, '#');
    size_t ret1 = BiTreeKlevelRootSize(tree, 1); 
    printf("ret expected 1, actual %d\n", ret1);
    size_t ret2 = BiTreeKlevelRootSize(tree, 2); 
    printf("ret expected 2, actual %d\n", ret2);
    size_t ret3 = BiTreeKlevelRootSize(tree, 3); 
    printf("ret expected 3, actual %d\n", ret3);
    size_t ret4 = BiTreeKlevelRootSize(tree, 4); 
    printf("ret expected 1, actual %d\n", ret4);
    size_t ret5 = BiTreeKlevelRootSize(tree, 5); 
    printf("ret expected 0, actual %d\n", ret5);
}

//测试求树的深度
void TestHeight()
{
    TEST_HEAD;
    DataType array[] = {"abd##eg###c#f##"};
    size_t size = sizeof(array)/sizeof(array[0]) - 1;
    BiTree tree = CreateBiTree(array, size, '#');

    size_t height = TreeHeight(tree);
    printf("height expected 4, actual %d\n", height);
}

//测试在树中找一个节点
void TestFind()
{
    TEST_HEAD;
    DataType array[] = {"abd##eg###c#f##"};
    size_t size = sizeof(array)/sizeof(array[0]) - 1;
    BiTree tree = CreateBiTree(array, size, '#');

    seqQueue queue;
    printf("\n=====前序遍历 递归版 查找节点=====\n");
    BiTree node = TreeFind(tree, 'g');
    printf("node expected [g], actual [%c]\n", node->data);

    printf("\n=====层序遍历 非递归版 查找节点=====\n");
    BiTree node1 = TreeFind_NoRecur(tree, 'c', &queue);
    printf("node expected [c], actual [%c]\n", node1->data);
}

//测试查找父节点
void TestParent()
{
    TEST_HEAD;
    DataType array[] = {"abd##eg###c#f##"};
    size_t size = sizeof(array)/sizeof(array[0]) - 1;
    BiTree tree = CreateBiTree(array, size, '#');

    printf("=====找 b 节点的父节点=====\n");
    BiTree node = TreeFind(tree, 'b');//先得到 b 节点的地址
    BiTree father = Parent(tree, node);//找 b 节点的父节点
    printf("expected [a], actual [%c]\n", father->data);

    printf("=====找 NULL 节点的父节点=====\n");
    BiTree father1 = Parent(tree, NULL);//找空节点的父节点
    if(father1 == NULL)
    {
        printf("没找到\n");
    }
    else
    {
        printf("expected [a], actual [%c]\n", father1->data);
    }

    printf("=====找 根 节点的父节点=====\n");
    BiTree node1 = TreeFind(tree, 'a');//先得到 a 节点的地址
    BiTree father2 = Parent(tree, node1);//找 a 节点的父节点
    if(father2 == NULL)
    {
        printf("没找到\n");
    }
    else
    {
        printf("expected [null], actual [%c]\n", father2->data);
    }
}

//测试查找孩子节点
void TestChild()
{
    TEST_HEAD;
    DataType array[] = {"abd##eg###c#f##"};
    size_t size = sizeof(array)/sizeof(array[0]) - 1;
    BiTree tree = CreateBiTree(array, size, '#');

    printf("=====找 a 节点的孩子节点=====\n");
    BiTree father = TreeFind(tree, 'a');//先得到 a 节点的地址
    BiTree L = LChild(tree, father);//找 a 节点的孩子节点
    printf("expected [b], actual [%c]\n", L->data);
    BiTree R = RChild(tree, father);//找 a 节点的孩子节点
    printf("expected [c], actual [%c]\n", R->data);

    printf("=====找 b 节点的孩子节点=====\n");
    BiTree father1 = TreeFind(tree, 'b');//先得到 b 节点的地址
    BiTree L1 = LChild(tree, father1);//找 b 节点的左孩子节点
    printf("expected [d], actual [%c]\n", L1->data);
    BiTree R1 = RChild(tree, father1);//找 b 节点的右孩子节点
    printf("expected [e], actual [%c]\n", R1->data);

    printf("=====找 e 节点的孩子节点=====\n");
    BiTree father_e = TreeFind(tree, 'e');//先得到 b 节点的地址
    BiTree e_L = LChild(tree, father_e);//找 b 节点的左孩子节点
    if(e_L != NULL)
    {
        printf("lchild expected [g], actual [%c]\n", e_L->data);
    }
    BiTree e_R = RChild(tree, father_e);//找 b 节点的右孩子节点
    if(e_R != NULL)
    {
        printf("rchild expected [null], actual [%c]\n", e_R->data);
    }
}

//测试循环版中序遍历
void TestInOrderByLoop()
{
    TEST_HEAD;
    DataType array[] = {"abd##eg###c#f##"};
    size_t size = sizeof(array)/sizeof(array[0]) - 1;
    BiTree tree = CreateBiTree(array, size, '#');

    InOrderByLoop(tree);
}
//测试循环版前序遍历
void TestPreOrderByLoop()
{
    TEST_HEAD;
    DataType array[] = {"abd##eg###c#f##"};
    size_t size = sizeof(array)/sizeof(array[0]) - 1;
    BiTree tree = CreateBiTree(array, size, '#');

    PreOrderByLoop(tree);
}
//测试循环版后序遍历
void TestPostOrderByLoop()
{
    TEST_HEAD;
    DataType array[] = {"abd##eg###c#f##"};
    size_t size = sizeof(array)/sizeof(array[0]) - 1;
    BiTree tree = CreateBiTree(array, size, '#');

    PostOrderByLoop(tree);
}

//测试求镜像树
void TestBiTreeMirror_ByRecur()
{
    TEST_HEAD;
    DataType array[] = {"abd##eg###c#f##"};
    size_t size = sizeof(array)/sizeof(array[0]) - 1;
    BiTree tree = CreateBiTree(array, size, '#');

    PreOrderByLoop(tree);
    printf("\n");
    InOrderByLoop(tree);
    printf("\n");
    PostOrderByLoop(tree);
    printf("\n");

    BiTreeMirror_ByRecur(tree);
    printf("\n=====镜像翻转后(递归版)=====\n");

    PreOrderByLoop(tree);
    printf("\n");
    InOrderByLoop(tree);
    printf("\n");
    PostOrderByLoop(tree);
    printf("\n");
}
void TestBiTreeMirror_ByLoop()
{
    TEST_HEAD;
    DataType array[] = {"abd##eg###c#f##"};
    size_t size = sizeof(array)/sizeof(array[0]) - 1;
    BiTree tree = CreateBiTree(array, size, '#');

    PreOrderByLoop(tree);
    printf("\n");
    InOrderByLoop(tree);
    printf("\n");
    PostOrderByLoop(tree);
    printf("\n");

    BiTreeMirror_ByLoop(tree);
    printf("\n=====镜像翻转后(循环版)=====\n");

    PreOrderByLoop(tree);
    printf("\n");
    InOrderByLoop(tree);
    printf("\n");
    PostOrderByLoop(tree);
    printf("\n");
}

//测试完全二叉树的判定
void TestIsCompleteBiTree()
{
    TEST_HEAD;
    DataType array[] = {"abd##e##cg###"};
    size_t size = sizeof(array)/sizeof(array[0]) - 1;
    BiTree tree = CreateBiTree(array, size, '#');

    PreOrderByLoop(tree);
    printf("\n");
    InOrderByLoop(tree);
    printf("\n");
    PostOrderByLoop(tree);
    printf("\n");

    if(IsCompleteBiTree(tree) == 1)
      printf("是完全二叉树\n");
    else
      printf("不是完全二叉树\n");
}
void TestNoCompleteBiTree()
{
    TEST_HEAD;
    DataType array[] = {"abd##e##c#f##"};
    size_t size = sizeof(array)/sizeof(array[0]) - 1;
    BiTree tree = CreateBiTree(array, size, '#');

    PreOrderByLoop(tree);
    printf("\n");
    InOrderByLoop(tree);
    printf("\n");
    PostOrderByLoop(tree);
    printf("\n");

    if(IsCompleteBiTree(tree) == 1)
      printf("是完全二叉树\n");
    else
      printf("不是完全二叉树\n");
}

//测试将二叉搜索树转换为有序的双链表
void TestBinarySortTree_to_DbLinkList()
{
    TEST_HEAD;
    //创建了一棵二叉搜索树
    DataType array[] = {"dba##c##e#f##"};
    size_t size = sizeof(array)/sizeof(array[0]) - 1;
    BiTree tree = CreateBiTree(array, size, '#');

    
    BinarySortTree_to_DbLinkList(tree, pfront, ptail);

}


int main()
{
    //TestBiTreeCreate_void();
    TestBiTreeCreate();
    TestDestroy();
    TestClone();
    TestBiTreeSize();
    TestLeafRootSize();
    TestKLevelRootSize();
    TestHeight();
    TestFind();
    TestParent();
    TestChild();
    TestPreOrderByLoop();
    TestInOrderByLoop();
    TestPostOrderByLoop();
    TestBiTreeMirror_ByRecur();
    TestBiTreeMirror_ByLoop();
    TestIsCompleteBiTree();
    TestNoCompleteBiTree();

    printf("\n\n\n");
    printf("\n\n\n");
    printf("\n\n\n");
    printf("\n\n\n");
    return 0;
}
