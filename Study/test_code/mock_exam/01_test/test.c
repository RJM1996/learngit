/*================================================================

# File Name: test.c
# Author: rjm
# mail: rjm96@foxmail.com
# Created Time: 2018年06月14日 星期四 18时49分58秒

================================================================*/



#include <stdio.h>

// 共有 n + 1 个人
// 门票 k 元
// 有 m 种套餐
// 二维数组表示 每种套餐的总价和门票张数
// 2 2 5
// 6  2
// 13 3
int buyTicket(int n, int m, int k, int arr[m][2])
{
    if(arr == NULL)
      return -1;
    // 先算出单独买需要的钱数
    int k_total = k * (n + 1);
    // 再算出哪种套餐的平均价格最便宜
    int cheapest_package = 0;
    int min = k_total;
    int package_num = 0;
    for(int i = 0; i < m; i++)
    {
        // min 代表每种套餐的每张票的均价
        if(arr[i][0] / arr[i][1] < min)
        {
            min = arr[i][0] / arr[i][1];
            package_num = i;
        }
    }
    // 此时 min 表示票价的最小值
    // package_num 表示第几个套餐
    int residue = (n + 1) % arr[package_num][1]; // 表示买了这个套餐后剩余的人数
    int package_count = (n + 1) / arr[package_num][1]; // 表示买了几个此套餐
    return residue * k + package_count * arr[package_num][0];
}

int main()
{
    int n = 0;
    int m = 0;
    int k = 0;
    scanf("%d %d %d", &n, &m, &k);
    printf("%d %d %d", n, m, k);
    int arr[m][2];

    // 2 2 5
    // 6  2
    // 13 3
    for(int i=0; i<m; i++)
    {
        for(int j=0; j<2; j++)
        {
            scanf("%d ", &arr[i][j]);
        }
    }

    for(int i=0; i<m; i++)
    {
        for(int j=0; j<2; j++)
        {
            printf("%d ", arr[i][j]);
        }
    }

    int ret = buyTicket(n, m, k, arr);
    printf("ret = %d\n", ret);

}
