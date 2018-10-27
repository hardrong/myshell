#include"comm.h"
static int commMsgQueue(int flags)
{
    key_t _key = ftok(PATHNAME,PROJ_ID);
    if(_key < 0 )
    {
      perror("ftock");
      return -1;
    }
    int msgid = msgget(_key,flags);
    if(msgid < 0)
    {
       perror("msgget");
       return -1;
    }
    return msgid;
}
int creatMsgQueue()
{
  return commMsgQueue(IPC_CREAT|IPC_EXCL|0664);
}
int getMsgQueue()
{
   return commMsgQueue(IPC_CREAT);
}
int sendMsgQueue(int msgid,int who,char *msg)
{
  struct msgbuffer s;
  s.mtype = who;
  strcpy(s.mtext,msg);
   if(msgsnd(msgid,(void*)&s,sizeof(s.mtext),0) < 0)
   {
     perror("msgsnd");
     return -1;
   }

}
int destroyMsgQueue(int msgid)
{
     if(msgctl(msgid,IPC_RMID,NULL) < 0)
     {
       perror("msgctl");
         return -1;
     }
     return 0;
}
int recvMsg(int msgid,int recvType,char out[])
{
    struct msgbuffer buf;
    if(msgrcv(msgid,(void*)&buf,sizeof(buf.mtext),recvType,0) < 0)
    {
      perror("msfrcv");
      return -1;
    }
    strcpy(out,buf.mtext);
    return 0;
}
