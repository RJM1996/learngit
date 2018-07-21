
#include"comm.h"

int main()
{
    int msgid = creatMsgQueue();
    char buf[1024];
    while(1)
    {
        buf[0] = 0;
        if(recvMsg(msgid, CLIENT_TYPE, buf) == 0)
        {
            printf("-----------------------\n");
            printf("client say: %s", buf);
            printf("-----------------------\n");
            if(strcmp(buf, "bye") == 0)
            {
                printf("bye!\n");
                break;
            }
        }

        printf("I say:");
        fflush(stdout);
        ssize_t s = read(0, buf, sizeof(buf));
        if(s > 0)
        {
            buf[s-1] = 0;
            if (sendMsg(msgid, SERVER_TYPE, buf) == 0);
            if(strcmp(buf, "quit") == 0)
            {
                printf("Bye!\n");
                break;
            }
        }
    }

    destoryMsgQueue(msgid);

    return 0;
}
