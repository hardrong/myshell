#include<stdio.h>
#include<sys/stat.h>
#include<sys/types.h>
#include<fcntl.h>
#include<stdlib.h>
#include<string.h>
#include<unistd.h>
int main()
{
  umask(0);
  if(mkfifo("mypipe",0664)<0)
  {
    return 0;
  }
   int rfd = open("mypipe",O_RDONLY);;
   if(rfd < 0)
   {
     return 0;
   }
   char buf[1024];
   while(1)
   {
     buf[0] = 0;
     printf("please wait...\n");
       int s = read(rfd,buf,sizeof(buf)-1);
     
       if(s > 0)
       {
         buf[s-1] = 0;
         printf("client says:%s\n",buf);
         if(strcmp(buf,"quit")==0)
           return 0;
       } 
       else if(s == 0)
       {
         printf("clinet quit,eixt now!\n");
         exit(EXIT_SUCCESS);
       }
        else 
        {
          return 0;
        }
   }
   close(rfd);
  return 0;
}
