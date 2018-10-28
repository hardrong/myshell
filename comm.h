#ifndef __COMM_H__
#define __COMM_H__

#include <stdio.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <string.h>
#include <unistd.h>
#define SERVER_TYPE 1
#define CLIENT_TYPE 2
#define PATHNAME "."
#define PROJ_ID 0x6667

struct msgbuffer
{
  long mtype;
  char mtext[64];
};
int creatMsgQueue();
int getMsgQueue();
int sendMsgQueue(int msgid,int who,char *msg);
int destroyMsgQueue(int msgid);
int recvMsg(int msgid,int recvType,char out[]);

#endif //__COMM_H__
