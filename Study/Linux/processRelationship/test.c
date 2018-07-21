/*================================================================
  Copyright (C) 2018 Sangfor Ltd. All rights reserved.
# File Name: test.c
# Author: rjm
# mail: rjm96@foxmail.com
# Created Time: 2018年04月25日 星期三 12时06分08秒

================================================================*/

#include <stdio.h> 
#include <unistd.h> 

int main() 
{    
    daemon(0,0);    
    while(1); 
}


//#include <stdio.h>
//#include <unistd.h>
//
//int main()
//{
//    pid_t id = fork();
//    if(id == 0)
//    {
//        //child
//        while(1)
//        {
//            printf("i am child: %d, i am runing\n", getpid());
//            sleep(1);
//        }
//    }
//    else
//    {
//        //father
//        int i = 10;
//        while(i)
//        {
//            printf("i am father: %d\n", getpid());
//            i--;
//            sleep(1);
//        }
//    }
//    return 0;
//}
//
