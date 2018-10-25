#include<stdio.h>
#include<sys/stat.h>
#include<sys/types.h>
#include<fcntl.h>
#include<stdlib.h>
#include<string.h>
#include<unistd.h>

int main()
{
   int wfd = open("mypipe",O_WRONLY);;
   if(wfd < 0)
   {
  //  ERR_EXIT("open");
     return 0;
   }
   char buf[1024];
   while(1)
   {
     printf("please input: ");
     fflush(stdout);
       int s = read(0,buf,sizeof(buf)-1);
     
       if(s > 0)
       {
         buf[s] = 0;
         
       write(wfd,buf,strlen(buf));
       } 
       else
           return 0;
   }
   close(wfd);
  return 0;
}
