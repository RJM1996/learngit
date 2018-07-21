
#include"comm.h"

int main()
{
    int msgid = getMsgQueue();
    char buf[1024];
    while(1)
    {
        buf[0] = 0;
        printf("I say:");
        fflush(stdout);
        ssize_t s = read(0, buf, sizeof(buf));
        if (sendMsg(msgid, CLIENT_TYPE, buf) == 0);

        if(recvMsg(msgid, SERVER_TYPE, buf) == 0)
        {
            printf("----------------------\n");
            printf("server say: %s\n", buf);
            printf("----------------------\n");
        }
        if(strcmp(buf, "bye") == 0)
        {
            printf("I say:");
            fflush(stdout);
            ssize_t s = read(0, buf, sizeof(buf));
            if (sendMsg(msgid, CLIENT_TYPE, buf) == 0);
            break;
        }
    }
    return 0;
}
