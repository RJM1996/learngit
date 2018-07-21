
#include<stdio.h>
#define N 6

#if 0
// 旋转 数组
void rotate(int arr[N][N], int a, int b, int c, int d)
{
    for(int i=0; i<d-b; ++i)
    {
        int tmp = arr[a][b-i];
        arr[a][b-i] = arr[c][d+i]; 
        arr[c][d+i] = arr[c][d-i];
        arr[c][d-i] = arr[a+i][b];
        arr[a+i][b] = tmp;
    }
}

void show(int arr[N][N])
{
    for(int i=0; i<N; i++)
    {
        for(int j=0; j<N; j++)
        {
            printf("%3d ", arr[i][j]);
        }
        printf("\n");
    }
    printf("\n");
}

// 岛屿问题
// 111000
// 100010
// 101100
// 001001


int island(int arr[N][N], int m, int n)
{
    int land = 0;
    for(int i=0; i<N; i++)
    {
        for(int j=0; j<N; j++)
        {
            if(arr[i][j] == 1)
            {
                land++;
                // 把 1 周围(上下左右)的 1 变成 2
                // 扫描到几个 1 就有几个岛
                
            }
        }
        printf("\n");
    }
}

int main()
{
    int arr[N][N];
    int num = 1;
    for(int i=0; i<N; i++)
    {
        for(int j=0; j<N; j++)
        {
            arr[i][j] = num++;
        }
    }
    show(arr);
//   rotate(arr, 0, 0, N-1, N-1);
    show(arr);
}


// 定时器
// setitimer
// 间隔定时器

#include<unistd.h>
#include<errno.h>
#include<sys/time.h>

int main()
{
    int tfd = timerfd_create(CLOCK_MONOTONIC, 
                             TFD_CLOEXEC);
    if(tfd == -1)
      perror("timerfd_create"), exit(1);

    struct itimerspec isp;
    memset(&isp, 0x00, sizeof(isp));
    isp.it_value.tv_sec = 3;
    isp.it_invalue.tv_sec = 1;
    timerfd_settime(tfd, 0, &isp, NULL);

    int kfd = fileno(stdin);
    int maxfd = tfd > kfd ? tfd : kfd;

    fd_set set;
    while(1)
    {
        FD_ZERO(&set);
        FD_SET(tfd, &set);
        FD_SET(kfd, &set);
        int nready = select(maxfd + 1, &set, NULL, NULL, NULL);
        if(nready <= 0)
        {
            continue;
        }
        if(FD_ISSET(tfd, &set))
        {
            uint64_t es;
            int r = read(tfd, &es, sizeof(es));
            if(r <= 0)
            {
                break;
            }
            printf("r = %d\n", r);
        }
        if(FD_ISSET(kfd, &set))
        {
            char buf[1024] = {};
            int r;
lab:
            r = read(kfd, buf, 1024);
            if(r <= 0)
            {
                if(r == -1 && errno == EINIR)
                {
                    goto lab;
                }
                break;
            }
            printf("buf = [%s]\n", buf);
        }
    }
}
#endif


