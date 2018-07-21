/*================================================================

# File Name: test.c
# Author: rjm
# mail: rjm96@foxmail.com
# Created Time: 2018年06月06日 星期三 11时06分29秒

================================================================*/



#include <stdio.h>

// 1, 求带环链表的入口
class Solution {
    public:
        ListNode* EntryNodeOfLoop(ListNode* pHead)
        {
            if(pHead == NULL)
              return NULL;

            ListNode* slow = pHead->next;
            if(slow == NULL)
              return NULL;
            ListNode* fast = slow->next;

            ListNode* meet = NULL;
            while(fast != NULL && slow != NULL)
            {
                if(slow == fast)
                {
                    meet = slow;
                    break;
                }
                slow = slow->next;
                fast = fast->next;
                if(fast != NULL)
                {
                    fast = fast->next;
                }
            }
            if(fast == NULL || slow == NULL)
            {
                return NULL;
            }
            // 到这里说明肯定有环
            ListNode* out_cycle = pHead;
            while(out_cycle != meet)
            {
                meet = meet->next;
                out_cycle = out_cycle->next;
            }
            return meet;
        }
};



