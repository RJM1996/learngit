/*================================================================

# File Name: game.h
# Author: rjm
# mail: rjm96@foxmail.com
# Created Time: 2018年05月03日 星期四 18时14分07秒

================================================================*/



#pragma once

#include <stdio.h>
#include  <stdlib.h>
#include  <time.h>
#define M  10//定义炸弹数量
#define ROW 10//定义棋盘大小
#define COL 10
void init(char mine[ROW][COL], char show[ROW][COL], char spread[ROW][COL]);
void displayboard(char show[ROW][COL]);
void displaymine(char mine[ROW][COL]);
void Set_Mine(char mine[ROW][COL],  int m);
void sweep_Mine(char mine[ROW][COL], char show[ROW][COL],   int x, int y);
int check_win(char mine[ROW][COL], char show[ROW][COL], int m );
void prevent_first_death(char mine[ROW][COL], int x, int y);
int mineNum(char mine[ROW][COL], int x, int y);
void spread(char mine[ROW][COL], char show[ROW][COL], const int x, const int y);
