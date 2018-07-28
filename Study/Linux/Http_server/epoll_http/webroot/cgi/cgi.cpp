#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <strings.h>
#include "cgi.h"

int main()
{
    char* method = NULL;
    char* query_string = NULL;
    char* arg;
    int content_len = -1;
    char buf[1024];
    if(getenv("METHOD") != NULL)
    {
        method = getenv("METHOD");
        if(strcasecmp(method, "GET") == 0)
        {
            if(getenv("QUERY_STRING") != NULL)
            {
                query_string = getenv("QUERY_STRING");
                arg = query_string;
            }
        }
        else
        {
            // post
            if(getenv("CONTENT_LENGTH") != NULL)
            {
                content_len = atoi(getenv("CONTENT_LENGTH"));
                int i = 0;
                for(; i < content_len; i++)
                {
                    read(0, &buf[i], 1);
                }
                buf[i] = '\0';
                arg = buf;
            }
        }
    }

    
    char* pArg = arg;

    if(pArg[0] == 'y')
    {
        Date_cal(arg);
    }
    else
    {
        my_cal(arg);
    }

    return 0;
}
