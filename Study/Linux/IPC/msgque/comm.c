
#include "comm.h"

static int commMegQueue(int flag)
{
    //key_t ftok( const char* fname, int id )
    key_t msgkey = ftok(PATHNAME, IPCKEY);
    if(msgkey < 0)
    {
        perror("ftok");
        return -1;
    }
    //go to here, msgkey gain succeed
    //int msgget(key_t key, int msgflag)
    int msgid = msgget(msgkey, flag); 
    if(msgid < 0)
    {
        perror("msgget");
        return -1;
    }
    //go to here, msgid gain succeed
    return msgid;
}


int creatMsgQueue()
{
    return commMegQueue(IPC_EXCL|IPC_CREAT|0666);
}
int getMsgQueue()
{
    return commMegQueue(IPC_CREAT);
}
int destoryMsgQueue(int msgid)
{
    //int msgctl ( int msgqid, int cmd, struct msqid_ds* buf );
    if(msgctl(msgid, IPC_RMID, NULL) < 0)
    {
        perror("msgctl");
        return -1;
    }
    //go to here, destoryMsgQueue succeed
    return 0;
}
int sendMsg(int msgid, int who, char* msg)
{
    //int msgsnd(int msqid, const void* msgp, size_t msgsz, int msgflg);
    struct msgbuf mybuf;
    mybuf.mtype = who;
    strcpy(mybuf.mtext, msg);
    if(msgsnd(msgid, (void*)&mybuf, sizeof(mybuf.mtext), 0) < 0)
    {
        perror("msgsnd");
        return -1;
    }
    return 0;
}
int recvMsg(int msgid, int recvType, char out[])
{
    //ssize_t msgrcv(int msqid, void* msgp, size_t msgsz, long msgtyp, int msgflg);
    struct msgbuf mybuf;
    if(msgrcv(msgid, (void*)&mybuf, sizeof(mybuf.mtext), recvType, 0) < 0)
    {
        perror("msgrcv");
        return -1;
    }
    //go to here, msgrcv succeed
    strcpy(out, mybuf.mtext);
    return 0;
}
