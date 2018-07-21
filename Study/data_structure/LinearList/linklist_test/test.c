
#include<stdio.h>
#include<stdlib.h>
#include<assert.h>

#define DataType int
#define TESTHEAD printf("=====%s=====\n", __FUNCTION__);

typedef struct Node
{
    DataType data;
    struct Node* next;
    struct Node* random;
}linklist, *plinklist;

//创建新结点
plinklist CreateNode()
{
    plinklist Node = (plinklist)malloc(sizeof(linklist));
    Node->random = NULL;
    return Node;
}
//销毁结点
void DestoryNode(plinklist Node)
{
    free(Node);
    Node = NULL;
}
//链表初始化
void LinkListInit(plinklist* head)
{
    *head = CreateNode();
    (*head)->next = NULL;
    (*head)->random = NULL;
    printf("初始化完成\n");
}
//链表的插入(尾插)
void LinkListPushBack(plinklist* head, DataType data)
{
    plinklist Node;
    plinklist temp;
    if((*head)->next == NULL)
    {
        Node = CreateNode();
        Node->data = data;
        (*head)->next = Node;
        Node->next = NULL;
    }
    else if((*head)->next)
    {
        temp = *head;
        while(temp->next)
        {
            temp = temp->next;
        }

        Node = CreateNode();
        Node->data = data;
        temp->next = Node;
        Node->next = NULL;
        temp = Node;
    }
}
//顺序打印链表
void LinkListPrint(plinklist* head)
{
    if((*head)->next == NULL)
    {
        printf("空链表\n");
        return ;
    }
    plinklist temp = (*head)->next;
    while(temp)
    {
        if(temp->random == NULL)
        {
            printf("[%d|%9p|NULL]\n", temp->data, temp->next);
        }
        else
        {
            printf("[%d|%9p][%d]\n", temp->data, temp->next, temp->random->data); 
        }
        temp = temp->next;
    }      
}
//逆序打印单链表
void LinkListReversePrint(plinklist* head)
{
    if(*head == NULL)
      return ;
    if((*head)->next)
    {
        LinkListReversePrint(&((*head)->next));
    }
    printf("[%d|%9p]\n", (*head)->data, (*head)->next);
}

// 右旋单链表
plinklist rotateRight(plinklist head, int k)
{
    if(head->next == NULL)
      return NULL;
    // 先算出链表的长度
    plinklist cur = head->next;
    int len = 0;
    while(cur != NULL)
    {
        cur = cur->next;
        len++;
    }
    printf("len = %d\n", len);
    int gap = len - k;
    cur = head;
    while(gap--)
    {
        cur = cur->next;
    }
    printf("cur->data: %d\n", cur->data);
    plinklist first = head->next;
    printf("first->data: %d\n", first->data);
    plinklist cur_head = cur->next;
    printf("cur_head->data: %d\n", cur_head->data);
    cur->next = NULL;
    plinklist tail = cur_head;

    while(tail->next != NULL)
    {
        tail = tail->next;
    }
    tail->next = first;
    printf("cur_head->data: %d\n", cur_head->data);
    head->next = cur_head;
    return head;
}



//不允许遍历链表, 在 pos 之前插入 
//思路:先在pos后插入,然后和pos的值交换
void LinkListInsertBeforePos(plinklist* head, plinklist pos, DataType data)
{
    if(head == NULL)
    {
        printf("非法输入\n");
        return ;
    }
    if((*head) == NULL)
    {
        printf("空链表\n");
        return ;
    }
    plinklist temp = *head;
    plinklist Node = CreateNode();
    Node->data = data;
    Node->next = pos->next;
    pos->next = Node;
    int tmp = Node->data;
    Node->data = pos->data;
    pos->data = tmp;
}
//单链表逆置
void LinkListReverse(plinklist* head)
{
    if(head == NULL) 
    {
        printf("非法输入\n");
        return ;
    }
    if((*head)->next == NULL) 
    {
        printf("空链表\n");
        return ;
    }
    //思路:从第一个结点开始,删除它的下一个结点,然后插入到头部
    plinklist temp = (*head)->next;
    plinklist after_head = (*head)->next;
    plinklist cur;
    while(temp->next)
    {
        cur = temp->next;
        temp->next = cur->next;
        cur->next = after_head;
        (*head)->next = cur;
        after_head = cur;
    }
    while(cur)
    {
        printf("%d ", cur->data);
        cur = cur->next;
    }
    printf("\n");
}
//交换函数
void swap(int* a, int* b)
{
    int ch = *a;
    *a = *b;
    *b = ch;
}
//求链表长度函数
int LinkListSize(plinklist* head)
{
    if(head == NULL) 
    {
        return -1;
    }
    if((*head)->next == NULL)
    {
        return 0;
    }
    plinklist temp = (*head)->next;
    int size = 0;
    while(temp)
    {
        size++;
        temp = temp->next;
    }
    return size;
}
//比较函数
int Cmp(DataType* a, DataType* b)
{
    if(*a > *b)
      return 1;
    else
      return 0;
}
//链表冒泡排序
void LinkListBubble(plinklist* head, int(*cmp)())
{
    if(head == NULL) 
    {
        return ;
    }
    if((*head)->next == NULL)
    {
        printf("空链表\n");
        return ;
    }
    int len = LinkListSize(head);
    for(int i=0; i<len; i++)
    {
        plinklist cur = (*head)->next;
        for(int j=0; j<len-i-1; j++)
        {
            if(Cmp(&(cur->data), &(cur->next->data))== 1)
            {
                swap(&(cur->data), &(cur->next->data));
            }
            cur = cur->next;
        }
    }
}
//将两个有序链表, 合并成一个有序链表 
plinklist LinkListMerge(plinklist head1, plinklist head2) 
{
    if(head1 == NULL)
    {
        return head2;
    }
    if(head2 == NULL)
    {
        return head1;
    }
    //定义两个结点,头结点和尾结点,形成只有两个结点的链表,然后每次把小的往尾结点后面插,尾结点后移.
    plinklist new_head = CreateNode();
    LinkListInit(&new_head);
    plinklist new_tail = CreateNode();
    LinkListInit(&new_tail);
    new_head->next = new_tail;
    plinklist cur1 = head1->next;
    plinklist cur2 = head2->next;
    while(cur1 != NULL && cur2 != NULL)
    {
        if(cur1->data < cur2->data)
        {
            new_tail->next = cur1;
            new_tail = new_tail->next;
            cur1 = cur1->next;
        }
        else
        {
            new_tail->next = cur2;
            new_tail = new_tail->next;
            cur2 = cur2->next;
        }
    }
    //一个链表走完了,另一个链表剩余的接在尾结点后面
    if(cur1 == NULL)
    {
        new_tail->next = cur2;
    }
    if(cur2 == NULL)
    {
        new_tail->next = cur1;
    }
    return new_head;
}
//找到倒数第 K 个节点. 
plinklist FindLastKNode(plinklist head, size_t K)
{
    if(head == NULL)
    {
        return NULL;
    }
    plinklist slow = head->next;
    plinklist fast = head->next;
    while(K--)
    {
        fast = fast->next;
    }
    while(fast)
    {
        slow = slow->next;
        fast = fast->next;
    }
    return slow;
}
//删除倒数第K个节点 
void EraseLastKNode(plinklist* head, size_t K)
{
    if(head == NULL)
    {
        return ;
    }
    if(*head == NULL)
    {
        printf("空链表\n");
        return ;
    }
    plinklist K_node = FindLastKNode(*head, K);
    if(K_node->next)
    {
        K_node->data = K_node->next->data;
        plinklist to_delete = K_node->next;
        K_node->next = K_node->next->next;
        DestoryNode(to_delete);
    }
    if(K_node->next == NULL)
    {
        plinklist temp = (*head)->next;
        plinklist before_temp = temp;
        while(temp)
        {
            before_temp = temp;
            temp = temp->next;
        }
        before_temp->next = NULL;
        DestoryNode(temp);
    }

}

//判断链表是否带环, 带环返回1
int HasCycle(plinklist head) 
{
    if(head->next == NULL)
    {
        printf("空链表\n");
        return 0;
    }
    if(head->next->next == NULL)
    {
        printf("只有一个结点\n");
        return 0;
    }
    plinklist slow = head->next;
    plinklist fast = head->next;
    do
    {
        slow = slow->next;
        fast = fast->next->next;
        if(slow == fast)
        {
            return 1;
        }
    }
    while(slow != fast && fast != NULL);

    return 0;
}

//求环的长度
size_t GetCycleLen(plinklist head) 
{
    if(head == NULL)
    {
        return 0;
    }
    if(HasCycle(head))
    {
        size_t count = 0;
        plinklist cur;
        plinklist slow = head->next;
        plinklist fast = head->next;
        do
        {
            slow = slow->next;
            fast = fast->next->next;
            if(slow == fast)
            {
                cur = slow;
                count = 0;
            }
        }
        while(slow != fast);

        slow = slow->next;
        count = 1;
        while(slow != cur)
        {
            slow = slow->next;
            count++;
        }
        return count;
    }
    return 0;
}

//如果链表带环, 求出环的入口 
plinklist GetCycleEntry(plinklist head)
{
    if(head == NULL)
    {
        return NULL;
    }
    plinklist outcycle = head->next;
    plinklist meet = NULL;
    plinklist slow = head->next;
    plinklist fast = head->next;
    do
    {
        slow = slow->next;
        fast = fast->next->next;
        if(slow == fast)
        {
            meet = slow;
            break;
        }
    }
    while(slow != NULL && fast != NULL);

    while(outcycle != meet && meet != NULL && outcycle != NULL)
    {
        outcycle = outcycle->next;
        meet = meet->next;
    }
    return meet;
}


//判定两个链表是否相交, 并求出交点, 不带环 
plinklist HasCross(plinklist head1, plinklist head2)
{
    if(head1 == NULL || head2 == NULL)
    {
        return NULL;
    }
    plinklist cur1 = head1->next;
    plinklist cur2 = head2->next;
    int len_cur1 = 0;
    int len_cur2 = 0;
    //先遍历两个链表, 求出长度L1 L2
    while(cur1)
    {
        cur1 = cur1->next;
        len_cur1++;
    }
    plinklist cur1_last = cur1;
    while(cur2)
    {
        cur2 = cur2->next;
        len_cur2++;
    }
    plinklist cur2_last = cur2;

    //如果两个链表的最后一个结点相同,则它们是相交的
    if(cur1_last == cur2_last)
    {
        cur1 = head1->next;
        cur2 = head2->next;
        int len = len_cur1 - len_cur2;
        //链表1先遍历到第L1-L2个结点
        while(len--)
        {
            cur1 = cur1->next;
        }

        //然后链表2从头开始,链表1从L2-L1开始,当他们相遇时,那个结点就是交点
        while(cur1 != cur2)
        {
            cur1 = cur1->next;
            cur2 = cur2->next;
        }
        return cur1;
    }
    return NULL;
}

//判定两个链表是否相交,链表可能带环
//如果相交, 返回交点, 否则返回NULL 
plinklist HasCrossWithCycle(plinklist head1, plinklist head2) 
{
    if(head1 == NULL || head2  == NULL)
    {
        return NULL;
    }
    //两个都不带环
    int len1 = 0;
    int len2 = 0;
    int len = 0;
    plinklist cur1 = head1->next;
    plinklist cur2 = head2->next;
    if(HasCycle(head1) == 0 && HasCycle(head2) == 0)
    {
        while(cur1 != NULL) 
        {
            cur1 = cur1->next;
            len1++;
        }
        while(cur2 != NULL) 
        {
            cur2 = cur2->next;
            len2++;
        }
        if(len1 > len2)
        {
            len = len1 -len2;
            cur1 = head1->next;
            while(len--)
            {
                cur1 = cur1->next;
            }
            while(cur1 != cur2)
            {
                cur1 = cur1->next;
                cur2 = cur2->next;
            }
            return cur1;
        }
        else
        {
            len = len2 - len1;
            cur2 = head2->next;
            while(len--)
            {
                cur2 = cur2->next;
            }
            while(cur1 != cur2)
            {
                cur1 = cur1->next;
                cur2 = cur2->next;
            }
            return cur1;
        }

    }
    //第一种情况,一个带环,一个不带环,则一定不相交
    if(HasCycle(head1) == 0 || HasCycle(head2) == 0)
    {
        return NULL;
    }
    //第二种情况,两个都带环,交点在环外
    //如果两个都带环,那么求它们的环入口点,若两入口点相同,则两个链表环外相交
    if(HasCycle(head1) == 1 && HasCycle(head2))
    {
        plinklist head1_entry = GetCycleEntry(head1);
        plinklist head2_entry = GetCycleEntry(head2);
        if(head1_entry == head2_entry)
        {
            len1 = 0, len2 = 0;
            cur1 = head1->next, cur2 = head2->next;
            while(cur1 != head1_entry)
            {
                len1++;
                cur1 = cur1->next;
            }
            while(cur2 != head2_entry)
            {
                len2++;
                cur2 = cur2->next;
            }
            len = 0;
            if(len1 > len2)
            {
                len = len1 - len2;
                cur1 = head1->next;
                cur2 = head2->next;
                while(len--)
                {
                    cur1 = cur1->next;
                }
                while(cur1 != cur2)
                {
                    cur1 = cur1->next;
                    cur2 = cur2->next;
                }
                return cur1;
            }
            else
            {
                len = len2 - len1;
                cur1 = head1->next;
                cur2 = head2->next;
                while(len--)
                {
                    cur2 = cur2->next;
                }
                while(cur1 != cur2)
                {
                    cur1 = cur1->next;
                    cur2 = cur2->next;
                }
                return cur1;
            }
        }
        else
        {
            //第三种情况,两个都带环,交点在环上
            //求环入口点,然后从入口点走,能遇到另一个入口点,则环上相交
            while(head1_entry != head2_entry)
            {
                head1_entry = head1_entry->next;
            }
            return head1_entry;
        }
    }
    return NULL;
}


//求两个有序链表的交集 
//return 返回表示交集的新链表 
plinklist UnionSet(plinklist head1, plinklist head2) 
{
    if(head1->next == NULL)
    {
        return NULL;
    }
    if(head2->next == NULL)
    {
        return NULL;
    }
    plinklist cur1 = (head1)->next;
    plinklist cur2 = (head2)->next;
    plinklist new_head = CreateNode();
    plinklist new_tail = CreateNode();
    new_head->next = new_tail;
    new_tail->next = NULL;

    while(cur1 != NULL && cur2 != NULL) 
    {
        if(cur1->data < cur2->data)
        {
            cur1 = cur1->next;
        }
        if(cur1->data > cur2->data)
        {
            cur2 = cur2->next;
        }
        if(cur1->data == cur2->data)
        {
            plinklist Node = CreateNode();
            Node->data = cur1->data;
            new_tail->next = Node;
            Node->next = NULL;
            new_tail = Node;

            cur1 = cur1->next;
            cur2 = cur2->next;
        }
    }

    return new_head->next;
}

//拷贝复杂链表 
plinklist CopyComplex(plinklist head) 
{
    if(head->next == NULL) 
    {
        return NULL;
    }
    //把每个结点的后面都插入一个自身节点
    plinklist cur = head->next;
    plinklist after_cur = NULL;
    while(cur != NULL)
    {
        //创建新结点, 拷贝它前一个结点的值, 并插入其后
        plinklist Node = CreateNode();
        Node->data = cur->data;
        after_cur = cur->next;
        cur->next = Node;
        Node->next = after_cur;

        cur = cur->next->next;
    }

    //复制random指针的指向
    cur = head->next;
    while(cur)
    {
        if(cur->random == NULL)
        {
            cur->next->random = NULL;
        }
        else
        {
            cur->next->random = cur->random->next;
        }
        cur = cur->next->next;
    }

    printf("-----分离前-----\n");
    LinkListPrint(&head);
    //接下来,将链表分离为两份
    plinklist new_head = CreateNode();
    plinklist new_tail = CreateNode();
    new_head->next = new_tail;
    new_tail->next = NULL;
    cur = head->next;
    while(cur)
    {
        //将拷贝完的结点分离,插入新的链表
        plinklist to_sep = cur->next;
        plinklist to_connect = cur->next->next;
        new_tail->next = to_sep;
        to_sep->next = NULL;
        new_tail = to_sep;
        cur->next = to_connect;

        cur = cur->next;
    }
    return new_head->next;
}

// 链表排序 
// 时间复杂度: O( N*logN )
// 空间复杂度: O(1)
plinklist sortList(plinklist head)
{
    assert(NULL != head);
    if (NULL == head)
      return NULL;

    //先得到链表的长度
    plinklist p = head;
    int len = 0;        
    while (NULL != p)
    {
        p = p->next;
        len++;
    }

    // 创建一个临时节点, 它的下一个节点是 head
    plinklist temp = CreateNode(-1);
    temp->next = head;

    int interval = 1;   //合并子列表的长度
    for (; interval <= len; interval *= 2)
    {
        plinklist pre = temp;
        plinklist first = temp->next;  //两段子列表的起始位置
        plinklist second = temp->next;

        while (NULL != first || NULL != second)
        {
            int i = 0;
            while (i < interval && NULL != second)
            {
                second = second->next; //将second移到第二段子列表的起始处
                i++;
            }

            int fvisit = 0, svisit = 0; //访问子列表的的次数<interval，保证列表中的元素全部能被访问
            while (fvisit < interval && svisit < interval && NULL != first && NULL != second)
            {
                if (first->data < second->data)
                {
                    pre->next = first;
                    pre = first;
                    first = first->next;
                    fvisit++;
                }
                else
                {
                    pre->next = second;
                    pre = second;
                    second = second->next;
                    svisit++;
                }
            }
            while (fvisit < interval && NULL != first)
            {
                pre->next = first;
                pre = first;
                first = first->next;
                fvisit++;
            }
            while (svisit < interval && NULL != second)
            {
                pre->next = second;
                pre = second;
                second = second->next;
                svisit++;
            }
            pre->next = second;
            first = second;
        }
    }

    plinklist retResult = temp->next;
    free(temp);
    temp = NULL;
    return retResult;
}


//////////////////////////////////////////////////////////
//测试函数
//////////////////////////////////////////////////////////


void TestHasCrossWithCycle() 
{
    TESTHEAD;
    plinklist mylinklist1;
    LinkListInit(&mylinklist1);
    LinkListPushBack(&mylinklist1, 1);
    LinkListPushBack(&mylinklist1, 2);
    LinkListPushBack(&mylinklist1, 3);
    LinkListPushBack(&mylinklist1, 4);
    printf("------链表1------\n");
    LinkListPrint(&mylinklist1);
    plinklist pos1 = FindLastKNode(mylinklist1, 1);
    pos1->next = mylinklist1->next->next->next;
    plinklist mylinklist2;
    LinkListInit(&mylinklist2);
    LinkListPushBack(&mylinklist2, 5);
    LinkListPushBack(&mylinklist2, 6);
    LinkListPushBack(&mylinklist2, 7);
    LinkListPushBack(&mylinklist2, 8);
    printf("------链表2------\n");
    LinkListPrint(&mylinklist2);

    plinklist pos3 = FindLastKNode(mylinklist2, 1);
    pos3->next = mylinklist1->next->next;

    printf("-----判断带环链表是否相交\n");
    printf("[都带环]\n");
    plinklist cross_pos = HasCrossWithCycle(mylinklist1, mylinklist2);
    printf("cross_pos expect [2] , actual [%d]\n", cross_pos->data);
}

void TestCopyComplexList()
{
    TESTHEAD;
    plinklist complexlist;
    LinkListInit(&complexlist);
    LinkListPushBack(&complexlist, 1);
    LinkListPushBack(&complexlist, 2);
    LinkListPushBack(&complexlist, 3);
    LinkListPushBack(&complexlist, 4);
    LinkListPrint(&complexlist);

    complexlist->next->random = complexlist->next->next->next;
    complexlist->next->next->random = complexlist->next->next;

    plinklist list = CopyComplex(complexlist);
    printf("-----分离后-----\n");
    LinkListPrint(&list);
    printf("\n");

}

void TestUnionSet()
{
    TESTHEAD;
    plinklist mylinklist1;
    LinkListInit(&mylinklist1);
    LinkListPushBack(&mylinklist1, 1);
    LinkListPushBack(&mylinklist1, 2);
    LinkListPushBack(&mylinklist1, 3);
    LinkListPushBack(&mylinklist1, 4);
    LinkListPrint(&mylinklist1);
    printf("\n");

    plinklist mylinklist2;
    LinkListInit(&mylinklist2);
    LinkListPushBack(&mylinklist2, 2);
    LinkListPushBack(&mylinklist2, 3);
    LinkListPushBack(&mylinklist2, 4);
    LinkListPushBack(&mylinklist2, 5);
    LinkListPrint(&mylinklist2);

    plinklist list = UnionSet(mylinklist1, mylinklist2);
    printf("-----两个链表的交集-----\n");
    LinkListPrint(&list);
}

void TestCross()
{
    TESTHEAD;
    plinklist mylinklist1;
    LinkListInit(&mylinklist1);
    LinkListPushBack(&mylinklist1, 1);
    LinkListPushBack(&mylinklist1, 3);
    LinkListPushBack(&mylinklist1, 5);
    LinkListPushBack(&mylinklist1, 7);
    LinkListPrint(&mylinklist1);
    printf("\n");
    plinklist mylinklist2;
    LinkListInit(&mylinklist2);
    LinkListPushBack(&mylinklist2, 2);
    LinkListPushBack(&mylinklist2, 4);
    LinkListPushBack(&mylinklist2, 6);
    LinkListPushBack(&mylinklist2, 8);
    LinkListPushBack(&mylinklist2, 9);
    LinkListPrint(&mylinklist2);
    plinklist cro1 = FindLastKNode(mylinklist1, 1);//取链表1的最后一个结点7
    plinklist cro2 = FindLastKNode(mylinklist2, 3);//取链表2的倒数第3个结点6
    cro1->next = cro2;//把7指向6 使两个链表相交 
    printf("-----交点应该是[6]-----\n");
    plinklist cross = HasCross(mylinklist1, mylinklist2);
    if(cross != NULL)
    {
        printf("cross = [%d|%p]\n", cross->data, cross->next);
    }
    else
    {
        printf("-----没有交点-----\n");
    }
    printf("\n");

}

void  TestEntry()
{
    TESTHEAD;
    plinklist mylinklist;
    LinkListInit(&mylinklist);
    LinkListPushBack(&mylinklist, 1);
    LinkListPushBack(&mylinklist, 3);
    LinkListPushBack(&mylinklist, 7);
    LinkListPushBack(&mylinklist, 9);
    LinkListPrint(&mylinklist);
    printf("-----无环-----\n");
    int res = HasCycle(mylinklist);
    printf("res = %d\n", res);
    printf("-----有环-----\n");
    plinklist pos = FindLastKNode(mylinklist, 2);//找到倒数第2个元素
    pos->next = mylinklist->next;//接到1结点,形成环,环长为3
    printf("-----入口应该为[1]-----\n");
    plinklist entry = GetCycleEntry(mylinklist);
    printf("Entry = [%d|%p]\n", entry->data, entry->next);

}

void TestCycleLen()
{
    TESTHEAD;
    plinklist mylinklist;
    LinkListInit(&mylinklist);
    LinkListPushBack(&mylinklist, 1);
    LinkListPushBack(&mylinklist, 3);
    LinkListPushBack(&mylinklist, 7);
    LinkListPushBack(&mylinklist, 9);
    LinkListPrint(&mylinklist);
    printf("-----无环-----\n");
    int res = HasCycle(mylinklist);
    printf("res = %d\n", res);
    printf("-----有环-----\n");
    plinklist pos = FindLastKNode(mylinklist, 2);//找到倒数第2个元素
    pos->next = mylinklist->next;//接到1结点,形成环,环长为3
    int len = GetCycleLen(mylinklist);
    printf("cycle len = %d\n", len);


}
void TestHasCycle()
{
    TESTHEAD;
    plinklist mylinklist;
    LinkListInit(&mylinklist);
    LinkListPushBack(&mylinklist, 1);
    LinkListPushBack(&mylinklist, 3);
    LinkListPushBack(&mylinklist, 7);
    LinkListPushBack(&mylinklist, 9);
    LinkListPrint(&mylinklist);
    printf("-----无环-----\n");
    int res = HasCycle(mylinklist);
    printf("res = %d\n", res);
    printf("-----有环-----\n");
    plinklist pos = FindLastKNode(mylinklist, 2);//找到倒数第2个元素
    pos->next = mylinklist;//接到头结点,形成环
    int ret = HasCycle(mylinklist);
    printf("ret = %d\n", ret);
}

void TestDeleKnode()
{
    TESTHEAD;
    plinklist mylinklist;
    LinkListInit(&mylinklist);
    LinkListPushBack(&mylinklist, 1);
    LinkListPushBack(&mylinklist, 3);
    LinkListPushBack(&mylinklist, 7);
    LinkListPushBack(&mylinklist, 9);
    LinkListPrint(&mylinklist);
    printf("删除倒数第三个结点[3]\n");
    EraseLastKNode(&mylinklist, 3);
    LinkListPrint(&mylinklist);
    printf("\n");

}

void TestFindKnode()
{
    TESTHEAD;
    plinklist mylinklist;
    LinkListInit(&mylinklist);
    LinkListPushBack(&mylinklist, 1);
    LinkListPushBack(&mylinklist, 3);
    LinkListPushBack(&mylinklist, 7);
    LinkListPushBack(&mylinklist, 9);
    LinkListPrint(&mylinklist);
    plinklist k = FindLastKNode(mylinklist, 2);
    printf("\n");
    printf("倒数第二个结点应该是[7]\n");
    printf("\nk = [%d|%p]\n", k->data, k->next);
    printf("\n");

}

void TestMerge()
{
    TESTHEAD;
    plinklist mylinklist1;
    LinkListInit(&mylinklist1);
    LinkListPushBack(&mylinklist1, 1);
    LinkListPushBack(&mylinklist1, 3);
    LinkListPushBack(&mylinklist1, 5);
    LinkListPushBack(&mylinklist1, 7);
    LinkListPrint(&mylinklist1);
    printf("\n");
    plinklist mylinklist2;
    LinkListInit(&mylinklist2);
    LinkListPushBack(&mylinklist2, 2);
    LinkListPushBack(&mylinklist2, 4);
    LinkListPushBack(&mylinklist2, 6);
    LinkListPushBack(&mylinklist2, 8);
    LinkListPushBack(&mylinklist2, 9);
    LinkListPrint(&mylinklist2);
    printf("\n");
    printf("-----合并链表-----\n");
    plinklist new = LinkListMerge(mylinklist1, mylinklist2);
    LinkListPrint(&new->next);
    printf("\n");

}

void TestPushBack()
{
    TESTHEAD;
    plinklist mylinklist;
    LinkListInit(&mylinklist);
    LinkListPrint(&mylinklist);
    LinkListPushBack(&mylinklist, 1);
    LinkListPushBack(&mylinklist, 3);
    LinkListPushBack(&mylinklist, 7);
    LinkListPushBack(&mylinklist, 9);
    LinkListPrint(&mylinklist);
    printf("\n");
}
void TestReversePrint()
{
    TESTHEAD;
    plinklist mylinklist;
    LinkListInit(&mylinklist);
    LinkListPrint(&mylinklist);
    LinkListPushBack(&mylinklist, 1);
    LinkListPushBack(&mylinklist, 3);
    LinkListPushBack(&mylinklist, 7);
    LinkListPushBack(&mylinklist, 9);
    printf("顺序打印\n");
    LinkListPrint(&mylinklist);
    printf("逆序打印\n");
    LinkListReversePrint(&mylinklist);
    printf("\n");
}
void TestInsertBeforePos()
{
    TESTHEAD;
    plinklist mylinklist;
    LinkListInit(&mylinklist);
    LinkListPushBack(&mylinklist, 1);
    LinkListPushBack(&mylinklist, 3);
    LinkListPushBack(&mylinklist, 7);
    LinkListPushBack(&mylinklist, 9);
    LinkListPrint(&mylinklist);
    plinklist pos = mylinklist->next->next;
    printf("-----在pos前插入6-----\n");
    LinkListInsertBeforePos(&mylinklist, pos, 6);
    LinkListPrint(&mylinklist);
    printf("-----在pos前插入8-----\n");
    LinkListInsertBeforePos(&mylinklist, pos, 8);
    LinkListPrint(&mylinklist);
    printf("\n");
}
void TestReverse()
{
    TESTHEAD;
    plinklist mylinklist;
    LinkListInit(&mylinklist);
    LinkListPushBack(&mylinklist, 1);
    LinkListPushBack(&mylinklist, 3);
    LinkListPushBack(&mylinklist, 7);
    LinkListPushBack(&mylinklist, 9);
    LinkListPrint(&mylinklist);
    printf("-----逆置-----\n");
    LinkListReverse(&mylinklist);
    LinkListPrint(&mylinklist);
    printf("\n");
}
void TestBubble()
{
    TESTHEAD;
    plinklist mylinklist;
    LinkListInit(&mylinklist);
    LinkListPushBack(&mylinklist, 4);
    LinkListPushBack(&mylinklist, 3);
    LinkListPushBack(&mylinklist, 1);
    LinkListPushBack(&mylinklist, 2);
    LinkListPrint(&mylinklist);
    printf("-----冒泡排序----\n");
    LinkListBubble(&mylinklist, Cmp);
    LinkListPrint(&mylinklist);
    printf("\n");
}

void TestRotate()
{
    TESTHEAD;
    plinklist mylinklist;
    LinkListInit(&mylinklist);
    LinkListPushBack(&mylinklist, 1);
    LinkListPushBack(&mylinklist, 2);
    LinkListPushBack(&mylinklist, 3);
    LinkListPushBack(&mylinklist, 4);
    LinkListPushBack(&mylinklist, 5);
    LinkListPrint(&mylinklist);
    plinklist cur = rotateRight(mylinklist, 2);
    LinkListPrint(&cur);
}

void TestSortList()
{
    TESTHEAD;
    plinklist mylinklist;
    LinkListInit(&mylinklist);
    LinkListPushBack(&mylinklist, 7);
    LinkListPushBack(&mylinklist, 2);
    LinkListPushBack(&mylinklist, 4);
    LinkListPushBack(&mylinklist, 8);
    LinkListPushBack(&mylinklist, 1);
    LinkListPushBack(&mylinklist, 3);
    LinkListPushBack(&mylinklist, 5);
    LinkListPushBack(&mylinklist, 9);
    LinkListPushBack(&mylinklist, 6);
    LinkListPrint(&mylinklist);
    sortList(mylinklist);
    LinkListPrint(&mylinklist);
}

int main()
{
    //    TestRotate();
    //    TestPushBack();
    //    TestReversePrint();
    //    TestInsertBeforePos();
    //    TestReverse();
    //    TestBubble();
    //    TestMerge();
    //    TestFindKnode();
    //    TestDeleKnode();
    //    TestHasCycle();
    //    TestCycleLen();
    //    TestEntry();
    //    TestCross();
    //    TestCopyComplexList();
    //    TestHasCrossWithCycle();
    //    TestUnionSet();
    TestSortList();
    printf("\n\n\n");
    printf("\n\n\n");
    printf("\n\n\n");
    return 0;
}
