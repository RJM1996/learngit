/*================================================================

# File Name: game.h
# Author: rjm
# mail: rjm96@foxmail.com
# Created Time: 2018年05月04日 星期五 11时12分17秒

================================================================*/

#pragma once

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define ROWS 3
#define COLS 3

//初始化棋盘
void init_board(char board[ROWS][COLS], int row, int col);
//显示棋盘
void display_board(char board[ROWS][COLS], int row, int col);
//玩家下子
void player_move(char board[ROWS][COLS], int row, int col);
//电脑下子
void computer_move(char board[ROWS][COLS], int row, int col);
//判断输赢
char check_win(char board[ROWS][COLS], int row, int col);



