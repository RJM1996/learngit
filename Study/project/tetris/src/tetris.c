#include <stdio.h>
#include <def.h>

void draw_element(int x, int y, int c)
{
	printf("\033[%d;%dH", y, x);
	printf("\033[3%dm\033[4%dm[]", c, c);
	fflush(stdout);
	printf("\033[0m");
}

void drwa_shape(int x, int y, struct shape p, int c)
{
	for (int i=0; i<5; i++) {
		for (int j=0; j<5; j++) {
			if ( p.s[i][j] != 0 )
				draw_element(x+j, y+i, c);
		}
	}
}

int main( void )
{
	int y = 10;
	int x = 3;

  int tfd = timerfd_create(CLOCK_MONOTONIC, TFD_NONBLOCK | TFD_CLOEXEC);
  struct timespec ts;
  memset(&ts, 0x00, sizeof(ts));
  ts.it_value.tv_nsec = 1;
  ts.it_interval.tv_se = 1;
	
	draw_element(x, y, 5);
}
