
//迷宫求解
//思路: 从一个入口点开始, 依次判断它的 上,右,下,左 方位能不能走 
//      如果能就直接走, 每走一步将这个位置的坐标入栈, 并且标记为2, 代表已经走过
//      若都不能走, 说明走到死路了, 要开始回溯
//      回溯时就是把入栈的坐标出栈, 即可原路返回, 每返回一步就重新再判断它的 上右下左 能不能走
//      直到找到出口
//方法一: 利用递归的函数调用栈, 保存已经走过的点
//方法二: 利用自己定义的栈, 保存已经走过的点
#include <stdio.h>

#define ROW 9
#define COL 9

//先定义一个迷宫地图
int map[ROW][COL] = {
    {0, 0, 1, 0, 0, 0, 1, 0, 0},
    {0, 0, 1, 0, 0, 0, 0, 0, 0},
    {0, 0, 1, 0, 0, 1, 1, 1, 0},
    {0, 0, 1, 0, 0, 1, 0, 0, 0},
    {0, 0, 1, 1, 1, 1, 0, 1, 0},
    {0, 0, 1, 0, 0, 1, 0, 1, 0},
    {0, 0, 1, 0, 0, 1, 1, 1, 1},
    {0, 0, 1, 0, 0, 1, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0, 0},
};

//定义一个点
typedef struct point
{
    int row;
    int col;
}point;

//打印迷宫
void MazePrint(int map[][COL], char* msg)
{
    printf("\n==========%s==========\n", msg);
    if(map == NULL)
      return ;
    for(int i=0; i<ROW; i++)
    {
        for(int j=0; j<COL; j++)
        {
            printf("%2d ", map[i][j]);
        }
        printf("\n");
    }
}


//一, 利用递归的函数调用栈


//判断能否落脚的函数
int canStay(point cur)
{
    //点在地图外, 则不能走
    if(cur.row < 0 || cur.col < 0 || cur.row > ROW || cur.col > COL)
    {
        //点越界
        return 0;
    }

    //点的值是 0 或 2 则不能走
    if(map[cur.row][cur.col] == 0 || map[cur.row][cur.col] == 2)
    {
        return 0;
    }
    //点的值是 1 则能走
    if(map[cur.row][cur.col] == 1)
    {
        return 1;
    }
    return 0;
}

//遍历判断 上右下左 能否落脚的函数
//point CW_Traversal(point cur)
//{
//    //定义上右下左 4个点
//    point up = {cur.row-1, cur.col};
//    point right = {cur.row, cur.col+1};
//    point down = {cur.row+1, cur.col};
//    point left = {cur.row, cur.col-1};
//
//    if( canStay(up) )
//    {
//        return up;
//    }
//    if( canStay(right) )
//    {
//        return right;
//    }
//    if( canStay(down) )
//    {
//        return down;
//    }
//    if( canStay(left) )
//    {
//        return left;
//    }
//    //如果都能落脚, 就返回当前点
//    return cur;
//}

//标记
void Mark(point cur)
{
    map[cur.row][cur.col] = 2;
}

//判读出口
int isExit(point cur, point entry)
{
    //点的坐标在边界, 就说明是出口
    //但是如果是入口, 肯定不是出口
    if(cur.row == entry.row && cur.col == entry.col)
    {
        return 0;
    }
    else if(cur.row == 0 || cur.col == 0 || cur.row == ROW-1 || cur.col == COL-1)
    {
        return 1;
    }

    return 0;
}

//辅助递归
void assistRecursion(point now_cur, point entry)
{
    //判断这个入口点能否落脚
    if( canStay(now_cur) )
    {
        printf("cur : (%d, %d)\n", now_cur.row, now_cur.col);

        //如果能落脚, 把这个点标记为 2
        Mark(now_cur);

        //判断是否为出口
        if( isExit(now_cur, entry) )
        {
            //是出口, 直接返回
            printf("找到了一条路径\n");
            return ;
        }

        //遍历它的 上右下左 判断能否落脚
        point up = {now_cur.row-1, now_cur.col};
        assistRecursion(up, entry);

        point right = {now_cur.row, now_cur.col+1};
        assistRecursion(right, entry);

        point down = {now_cur.row+1, now_cur.col};
        assistRecursion(down, entry);

        point left = {now_cur.row, now_cur.col-1};
        assistRecursion(left, entry);
    }
}

//寻找路径
void getPath(point entry)
{
    //辅助递归函数
    assistRecursion(entry, entry);
}


int main()
{
    point entry = {0, 2};//定义入口
    MazePrint(map, "打印迷宫");
    getPath(entry);
    MazePrint(map, "迷宫路线");
    printf("\n\n\n");
    printf("\n\n\n");
    printf("\n\n\n");
    return 0;
}
