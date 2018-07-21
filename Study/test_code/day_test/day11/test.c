/*================================================================

# File Name: test.c
# Author: rjm
# mail: rjm96@foxmail.com
# Created Time: 2018年06月06日 星期三 10时12分28秒

================================================================*/



#include <stdio.h>

// 1, 求数组内第一个重复的元素
int duplicate(int numbers[], int length, int* duplication) {
    for(int i = 0; i < length; i++){
        int pre = numbers[i];
        for(int j = i+1; j < length; j++){
            int next = numbers[j];
            if(pre == next){
                *duplication = pre;
                return 1;
            }
        }
    }
    return 0;
}

// 2, 求两个链表的交点 
//    长的先走长度之差的步数, 再和短的一起走, 相遇时, 就是第一个交点
class Solution
{
    public:
        ListNode *FindFirstCommonNode( ListNode *pHead1, ListNode *pHead2 )
        {
            if(pHead1 == NULL || pHead2 == NULL)
              return NULL;
            ListNode *cur1 = pHead1;
            ListNode *cur2 = pHead2;
            //ListNode *cur1_last = NULL;
            //ListNode *cur2_last = NULL;
            unsigned int len1 = 0;
            unsigned int len2 = 0;
            int gap = 0;
            while(cur1 != NULL)
            {
                ++len1;
                cur1 = cur1->next;
            }
            //cur1_last = cur1;
            while(cur2 != NULL)
            {
                ++len2;
                cur2 = cur2->next;
            }
            //cur2_last = cur2;

            if(len2 > len1)
            {
                cur1 = pHead1;
                cur2 = pHead2;
                gap = len2 - len1;
                while(gap--)
                {
                    cur2 = cur2->next;
                }
            }
            else
            {
                cur1 = pHead1;
                cur2 = pHead2;
                gap = len1 - len2;
                while(gap--)
                {
                    cur1 = cur1->next;
                }
            }
            while(cur1 != NULL && cur2 != NULL && cur1 != cur2)
            {
                cur1 = cur1->next;
                cur2 = cur2->next;

            }
            return cur1;
        }
};

int main()
{
    int arr[] = {2, 3, 1, 0, 2, 5, 3};
    int len = sizeof(arr)/sizeof(arr[0]);
    int dup = 0;
    if(duplicate(arr, len, &dup) == 1)
      printf("%d\n", dup);
    else
      printf("没有重复元素\n");
    return 0;
}
