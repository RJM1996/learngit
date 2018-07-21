/*================================================================

# File Name: test.c
# Author: rjm
# mail: rjm96@foxmail.com
# Created Time: 2018年05月03日 星期四 18时15分26秒

================================================================*/



#include "game.h"

//游戏菜单
void menu()
{
    printf("=======================================\n");
    printf("---------------扫雷游戏----------------\n");
    printf("=====1,开始================2,退出======\n");
    printf("=======================================\n");
}

void game()
{
    char mine[ROW][COL];
    char show[ROW][COL];
    char spread[ROW][COL];
    int x, y, m;
    int row, col;
    int count=0;
    int ret;
    row = ROW;
    col = COL;
    m = M;
    init(mine, show, spread);
    displayboard(show);
    Set_Mine(mine, m);
    displaymine(mine);
    do
    {
        displayboard(show);
        count++;
        printf("==========开始扫雷>:");
        scanf("%d %d", &x, &y);
        getchar();
        x = x - 1;
        y = y - 1;
        if (count == 1)
        {
            prevent_first_death(mine, x, y);
        }
        sweep_Mine(mine, show, x, y);
        ret = check_win(mine, show, m);
        if(ret == 1)
        {
            displayboard(show);
            printf("\n=========踩到炸弹! gg========\n\n");
            break;
        }
        else if(ret == 0)
        {
            displayboard(show);
            printf("\n==========扫雷成功！==========\n\n");
            break;
        }
    }
    while (1);
}

int main()
{
    int n = 0;
    do
    {
        menu();
        printf("=====请选择=>");
        scanf("%d", &n);
        printf("==================================\n");
        getchar();
        if(n == 1)
        {
            game();
        }
        else if(n == 2)
        {
            printf("\nbye!\n");
            break;
        }
        else
        {
            printf("输入有误 重新输入\n");
        }
    }
    while (1);
    printf("\n\n\n");
    printf("\n\n\n");
    printf("\n\n\n");
    return 0;
}
