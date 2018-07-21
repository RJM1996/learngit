/*================================================================

# File Name: c_day08.c
# Author: rjm
# mail: rjm96@foxmail.com
# Created Time: 2018年05月01日 星期二 07时36分41秒

================================================================*/



#include <stdio.h>

//1, 5位运动员参加了10米台跳水比赛，有人让他们预测比赛结果 
//   A选手说：B第二，我第三； 
//   B选手说：我第二，E第四； 
//   C选手说：我第一，D第二； 
//   D选手说：C最后，我第三； 
//   E选手说：我第四，A第一； 
//   比赛结束后，每位选手都说对了一半，请编程确定比赛的名次。 

void judgeRank()
{
    int A, B, C, D, E;
    for(A = 1; A <= 5; A++)
      for(B = 1; B <= 5; B++)
        for(C = 1; C <= 5; C++)
          for(D = 1; D <= 5; D++)
            for(E = 1; E <= 5; E++)
            {
                if (A!=B && A!=C && A!=D && A!=E && B!=C && B!=D && B!=E && C!=D && C!=E && D!=E)
                {
                    if((B == 2 && A != 3) || (B !=2 && A == 3))
                      if((B == 2 && E != 4) || (B !=2 && E == 4))
                        if((C == 1 && D != 2) || (C != 1 && D == 2))
                          if((C == 5 && D != 3) || (C != 5 && D == 3))
                            if((E == 4 && A != 1) || (E != 4 && A == 1))
                            {
                                printf("A = %d\n", A);
                                printf("B = %d\n", B);
                                printf("C = %d\n", C);
                                printf("D = %d\n", D);
                                printf("E = %d\n", E);
                            }
                }
            }
}

//2, 日本某地发生了一件谋杀案，警察通过排查确定杀人凶手必为4个嫌疑犯的一个。
//   以下为4个嫌疑犯的供词。 
//   A说：不是我。 
//   B说：是C。 
//   C说：是D。 
//   D说：C在胡说 
//   已知3个人说了真话，1个人说的是假话。 
//   现在请根据这些信息，写一个程序来确定到底谁是凶手。 
void judgeMurderer()
{
    int A, B, C, D;
    for(A=0; A<=1; A++)
      for(B=0; B<=1; B++)
        for(C=0; C<=1; C++)
          for(D=0; D<=1; D++)
          {
              if(A == 1 && C == 1 && D == 1 && D == 0 && A+B+C+D == 1)
              {
                  printf("A = %d\n", A);
                  printf("B = %d\n", B);
                  printf("C = %d\n", C);
                  printf("D = %d\n", D);
              }
              if(A == 0 && C == 0 && D == 1 && D == 0 && A+B+C+D == 1)
              {
                  printf("A = %d\n", A);
                  printf("B = %d\n", B);
                  printf("C = %d\n", C);
                  printf("D = %d\n", D);
              }
              if(A == 0 && C == 1 && D == 0 && D == 0 && A+B+C+D == 1)
              {
                  printf("A = %d\n", A);
                  printf("B = %d\n", B);
                  printf("C = %d\n", C);
                  printf("D = %d\n", D);
              }
              if(A == 0 && C == 1 && D == 1 && D == 1 && A+B+C+D == 1)
              {
                  printf("A = %d\n", A);
                  printf("B = %d\n", B);
                  printf("C = %d\n", C);
                  printf("D = %d\n", D);
              }
          }
}

#define N 21
void printPascalTriangle()
{
    int i = 0; 
    int j = 0;
    int k = 0; 
    int n = 0; 
    int a[N][N] = {0}; //定义二维数组a[21][21]

    while(n<=0 || n>=21)//最多打印20行
    { 
        printf("请输入要打印的行数(不超过20)：");
        scanf("%d",&n);
    }
    printf("%d行杨辉三角：\n",n);
    for(i=1;i<=n;i++)
    {
        a[i][1] = 1;
        a[i][i] = 1;
    }
    for(i=3; i<=n; i++)
    {
        for(j=2; j<=i-1; j++)
        {
            a[i][j] = a[i-1][j-1]+a[i-1][j]; 
        }
    }
    for(i=1; i<=n; i++)
    {
        for(k=1; k<=n-i;    k++)
        {
            printf("  "); 
        }
        for(j=1; j<=i; j++) 
        {
            printf("%6d",a[i][j]);
        }
        printf("\n");
    }
    printf("\n");
}

int main()
{
    //judgeRank();
    judgeMurderer();
    printPascalTriangle();

    printf("\n");
    printf("\n");
    printf("\n");
    return 0;
}
