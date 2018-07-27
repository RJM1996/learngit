#include <iostream>
#include <memory.h>
#include <malloc.h>

using namespace std;

// 因为不允许拼桌, 那么如果客人数大于餐桌最大容纳人数, 那批客人就过滤掉
// 在客人数相同的情况下, 首选消费金额高的
// 已经被选过的后面就不能再选了
// 例如:有3张桌子,5批客人, 那么每张桌子有5种选择, 把每张桌子的最优选择的消费金额相加, 就是最终结果

// 3 5  // 3 张桌子 5 批客人
// 2 4 2  // 每张桌子分别容纳 2 4 2 个人
// 1 3  // 1 个客人 消费金额 3 
// 3 5 
// 3 7 
// 5 9 
// 1 10
// 
// desk_num : 桌子数量
// desk_capacity : 每张桌子的容量
// guest_num : 客人批数
// guest[][2] : 每批客人的人数和消费金额
int MaxMonetary(int desk_num, int* desk_capacity, int guest_num, int guest[][2])
{
    int max_sum = 0; // 最大消费金额
    int i = 0;
    int j = 0;
    int group = 0;
    int* desk_max_sum = (int*)malloc(desk_num*sizeof(int));
    memset(desk_max_sum, 0, sizeof(*desk_max_sum));
    for(; i<desk_num; ++i)
    {
        j = 0;
        for(; j<guest_num; ++j)
        {
            // 如果桌子容量大于客人数
            if(desk_capacity[i] > guest[j][0])
            {
                if(guest[j][1] > desk_max_sum[i])
                {
                    desk_max_sum[i] = guest[j][1];
                    group = j;
                }
            }
        }
        // 每个桌子选完以后, 就把它选过的删除
        guest[group][1] = 0;
        // printf("第 %d 个桌子的最大金额 : %d\n", i+1, desk_max_sum[i]);
    }
    for(i=0; i<desk_num; ++i)
    {
        max_sum += desk_max_sum[i];
    }
    free(desk_max_sum);
    return max_sum;
}

int main()
{
    int n = 3;
    int m = 5;
    int desk_capacity[3] = {2, 4, 2};
    int guest[][2] = {
        {1, 3},
        {3, 5},
        {3, 7},
        {5, 9},
        {1, 10},
    };
    cin >> n >> m ;
    for(int i=0; i<n; i++)
    {
        cin >> desk_capacity[i];
    }
    for(int j=0; j<m; ++j)
    {
        for(int k=0; k<2; ++k)
        {
            cin >> guest[j][k];
        }
    }
    int ret = MaxMonetary(n, desk_capacity, m, guest);
    cout << ret << endl;
}
