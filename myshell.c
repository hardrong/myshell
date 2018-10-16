#include<unistd.h>
#include<sys/wait.h>
#include<stdio.h>
#include<ctype.h>
#include<stdlib.h>
#include<string.h>
#include<sys/types.h>
#include<sys/stat.h>
#include<fcntl.h>
char *argv[8];
int argc = 0;
int flag;
int mark;
int count;
void do_parse(char *buf)
{
  int i;
  int status = 0;
  flag = 0;
  mark = 0;
  for(argc=i=0;buf[i];i++)
  {
     if(buf[i] == '>' && !flag )
     {
       flag = 1;
       count = argc;
     }
     else if(buf[i] == '<' && !mark)
     {
       mark = 1;
       count = argc;
     }
    if(!isspace(buf[i]) && status == 0)
    {
      argv[argc++] = buf+i;
      status = 1;
    }
    else if(isspace(buf[i]))
    {
      status = 0;
      buf[i] = 0;
  }
  }
  argv[argc] = NULL;
}
void do_execute(void)
{
  int st;
  int fd;
  pid_t pid =fork();
  if(pid == -1)
  {
    exit(EXIT_FAILURE);
    
  }
  else if(pid > 0)
  {
    wait(&st);
  }
  else if(pid == 0)
  {
  if(flag)
  {
    argv[count] = NULL;
    fd =  open(argv[count+1],O_WRONLY|O_CREAT,0664);
    close(1);
    dup2(fd,1);  
  }
  else if(mark)
  {
    fd = open(argv[count+1],O_WRONLY|O_WRONLY,0664);
    argv[count] =NULL;
    close(0);
    dup2(fd,0);
  }
  execvp(argv[0],argv);
if(flag)
  {
    close(fd);
   // open("/dev/pts/0",O_WRONLY);
  }
else if(mark)
{
  close(fd);
}
   }  
}
int main()
{
  char buf[1024];
  do
  {
    memset(buf,0,1024);
    printf("[gxr@localhost code]#");
    fflush(stdout);
    size_t read_size = read(1,buf,1024);
    if(read_size)
    {
    do_parse(buf);
    do_execute();
    } 
  }while(buf[0] != 'q');
  return 0;
}
