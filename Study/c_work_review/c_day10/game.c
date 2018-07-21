/*================================================================
# File Name: game.c
# Author: rjm
# mail: rjm96@foxmail.com
# Created Time: 2018年05月04日 星期五 11时13分31秒
================================================================*/
#include "game.h"

//初始化棋盘
void init_board(char board[ROWS][COLS], int row, int col)//初始化棋盘
{
    memset(board, ' ', col * row * sizeof(char));
}
//打印棋盘
void display_board(char board[ROWS][COLS], int row, int col) //打印棋盘
{
    int i = 0;
    for(i = 0; i < row; i++)
    {
        printf(" %c | %c | %c \n",  board[i][0], board[i][1], board[i][2]);
        if(i != 2)
        {
            printf("---|---|---\n");
        }
    }
}
//玩家下子
void player_move(char board[ROWS][COLS], int row, int col) //玩家走
{
    int x = 0;
    int y = 0;
    printf("玩家下棋——————");
    while(1)
    {
        printf("请输入坐标:>");
        scanf("%d%d", &x, &y);
        x--; //将玩家输入的坐标减1 因为棋盘坐标是从0开始的
        y--;
        if(((x >= 0) && (x <= 2)) && ((y >= 0) && (y <= 2))) //坐标在0-2之间
        {
            if(board[x][y] == ' ')
            {
                board[x][y] = 'X';
                break;
            }
            else
            {
                printf("下标有误, 重新输入！");
            }
        }
        else
        {
            printf("下标有误, 重新输入！");
        }
    }
}
//电脑下子
void computer_move(char board[ROWS][COLS], int row, int col) //电脑走
{
    int x = 0;
    int y = 0;
    int i = 0;
    int j = 1;
    printf("电脑下棋——————————————\n");
    if (j == 1)
    {
        for (i = 0; i < row; i++)
        {
            if (board[i][0] == board[i][1] && board[i][2] == ' ' && board[i][1] != ' ') //比如 如果00=01 并且 02为空 01不为空
            {
                board[i][2] = '0'; //那么在02下棋
                j = 0;
                break;
            }
        }
    }
    if (j == 1)
    {
        for (i = 0; i < row; i++)
        {
            if (board[i][1] == board[i][2] && board[i][0] == ' ' && board[i][1] != ' ')
            {
                board[i][0] = '0';
                j = 0;
                break;
            }
        }
    }
    if (j == 1)
    {
        for (i = 0; i < row; i++)
        {
            if (board[0][i] == board[1][i] && board[2][i] == ' ' && board[1][i] != ' ')
            {
                board[2][i] = '0';
                j = 0;
                break;
            }
        }
    }
    if (j == 1)
    {
        for (i = 0; i < row; i++)
        {
            if (board[1][i] == board[2][i] && board[0][i] == ' ' && board[1][i] != ' ')
            {
                board[0][i] = '0';
                j = 0;
                break;
            }
        }
    }
    if (j == 1)
    {
        for (i = 0; i < row; i++)
        {
            if (board[i][0] == board[i][2] && board[i][1] == ' ' && board[i][0] != ' ')
            {
                board[i][1] = '0';
                j = 0;
                break;
            }
        }
    }
    if (j == 1)
    {
        for (i = 0; i < row; i++)
        {
            if (board[0][i] == board[2][i] && board[1][i] == ' ' && board[0][i] != ' ')
            {
                board[1][i] = '0';
                j = 0;
                break;
            }
        }
    }
    else if (board[1][1] == ' ')
    {
        board[1][1] = '0';
        j = 0;
    }
    else if (board[0][0] == ' ' && (board[0][1] == '*' || board[1][0] == '*'))
    {
        board[0][0] = '0';
        j = 0;
    }
    else if (board[0][2] == ' ' && (board[0][1] == '*' || board[1][2] == '*'))
    {
        board[0][2] = '0';
        j = 0;
    }
    else if (board[2][0] == ' ' && (board[1][0] == '*' || board[2][1] == '*'))
    {
        board[2][0] = '0';
        j = 0;
    }
    else if (board[2][2] == ' ' && (board[2][1] == '*' || board[1][2] == '*'))
    {
        board[2][2] = '0';
        j = 0;
    }
    else if (board[0][0] == ' ')
    {
        board[0][0] = '0';
        j = 0;
    }
    else if (board[0][2] == ' ')
    {
        board[0][2] = '0';
        j = 0;
    }
    else if (board[2][0] == ' ')
    {
        board[2][0] = '0';
        j = 0;
    }
    else if (board[2][2] == ' ')
    {
        board[2][2] = '0';
        j = 0;
    }
    else if(board[0][0] == board[1][1] && board[2][2] == ' ' && board[1][1] != ' ')
    {
        board[2][2] = '0';
        j = 0;
    }
    else if (board[0][2] == board[1][1] && board[2][0] == ' ' && board[1][1] != ' ')
    {
        board[2][0] = '0';
        j = 0;
    }
    else if (board[2][0] == board[1][1] && board[0][2] == ' ' && board[1][1] != ' ')
    {
        board[0][2] = '0';
        j = 0;
    }
    else if (board[2][2] == board[1][1] && board[0][0] == ' ' && board[1][1] != ' ')
    {
        board[0][0] = '0';
        j = 0;
    }
    while (j)
    {
        x = rand() % row;
        y = rand() % col;
        if (board[x][y] == ' ')
        {
            board[x][y] = '0';
            break;
        }
    }
}
//判断棋盘是否下满
static int is_full(char board[ROWS][COLS], int row, int col) //判断棋盘是否满了
{
    int i = 0;
    int j = 0;
    for(i = 0; i < row; i++)
    {
        for(j = 0; j < col; j++)
        {
            if(board[i][j] == ' ')
              return 0;
        }
    }
    return 1; //返回1 表示棋盘满了
}
//判断输赢
char check_win(char board[ROWS][COLS], int row, int col)//判断输赢
{
    int i = 0;
    for(i = 0; i < row; i++)
    {
        if((board[i][0] == board[i][1])
                    && (board[i][1] == board[i][2])
                    && (board[i][1] != ' '))
          return board[i][1];
    }
    for(i = 0; i < col; i++)
    {
        if((board[0][i] == board[1][i])
                    && (board[1][i] == board[2][i])
                    && (board[1][i] != ' '))
          return board[1][i];
    }
    if((board[0][0] == board[1][1])
                && (board[1][1] == board[2][2])
                && (board[1][1] != ' '))
      return board[1][1];
    if((board[0][2] == board[1][1])
                && (board[1][1] == board[2][0])
                && (board[1][1] != ' '))
      return board[1][1];
    if(is_full(board, row, col))//如果棋盘满了 返回q
    {
        return 'q';
    }
    return ' ';
}
