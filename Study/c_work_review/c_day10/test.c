/*================================================================
# File Name: test.c
# Author: rjm
# mail: rjm96@foxmail.com
# Created Time: 2018年05月04日 星期五 11时19分23秒
================================================================*/
#include "game.h"

void game()
{
    char board[ROWS][COLS] = {0};
    char ret = 0;
    init_board(board, ROWS, COLS); //初始化棋盘
    display_board(board, ROWS, COLS); //打印棋盘
    srand((unsigned int)time(NULL)); //根据时间生成随机数
    while(1)
    {
        player_move(board, ROWS, COLS); //玩家走
        if((ret = check_win(board, ROWS, COLS)) != ' ')//判断输赢
          break;
        display_board(board, ROWS, COLS);//打印棋盘
        computer_move(board, ROWS, COLS);//电脑走
        if((ret = check_win(board, ROWS, COLS)) != ' ')//判断输赢
          break;
        display_board(board, ROWS, COLS);//打印棋盘
    }
    display_board(board, ROWS, COLS);
    if(ret == 'X')
    {
        printf("——————恭喜你赢了——————\n");
        printf("\n");
    }
    if(ret == '0')
    {
        printf("——————很遗憾你输了——————\n");
        printf("\n");
    }
    if(ret == 'q')
    {
        printf("————————平局————————\n");
        printf("\n");
    }
    printf("\n");
}
void menu()
{
    printf("=============三子棋游戏============\n");
    printf("=====1,开始游戏=====0,退出游戏=====\n");
    printf("===================================\n");
}
int main()
{
    int input = 0;
    do
    {
        menu();
        printf("=======请选择>:");
        scanf("%d", &input);
        switch(input)
        {
            case 1:
                game();
                break;
            case 0:
                printf("\nbye!\n");
                break;
            default:
                printf("对不起，没有这个选项\n");
                break;
        }
    }
    while (input);
    return 0;
}
