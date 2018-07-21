
#ifndef _COMM_H_ 
#define _COMM_H_

#include<stdio.h>
#include<stdlib.h>
#include<sys/types.h>
#include<sys/ipc.h>
#include<sys/msg.h>
#include<string.h>

#define CLIENT_TYPE 1
#define SERVER_TYPE 2

#define PATHNAME "."
#define IPCKEY 0x6666

struct msgbuf
{
    long mtype;
    char mtext[1024];
};


static int commMegQueue(int flag);
int creatMsgQueue();
int getMsgQueue();
int destoryMsgQueue(int msgid);
int sendMsg(int msgid, int who, char* msg);
int recvMsgQueue(int msgid, int recvType, char out[]);


#endif  
