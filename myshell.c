#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<unistd.h>
#include<sys/wait.h>
#include<sys/types.h>
#include<sys/stat.h>
#include<fcntl.h>
#include<ctype.h>
int flag;
int mark;
void do_parse(char *buf,char* argv[]) {
      if(buf==NULL)
      {
              return;
                  
      }
          if(argv==NULL)
          {
                    return;
                        
          }
              int i;
              int argc=0;
              int status=0;
           for(i=0;buf[i];i++)
            {
             if(!isspace(buf[i]) &&status==0 )
               {
               argv[argc++]=buf+i;
                 status=1;                                         
                }else if( isspace(buf[i]))
                 {
                      status=0;
                      buf[i]='\0';                                     
                 }
                                       
            }
           argv[argc]=NULL;
                            
}

int has_pipe(char* argv[])
{
     int i=1;
       //Start form 1 because before '|' should have command.
              while(argv[i]!=NULL)
                    {
                          
                      // if(strcmp(argv[i],"|")==0)
                       // {
                        //  argv[i]=NULL;
                       //   return i+1;
                          
                       // }
                      // if(strcmp(argv[i],">") == 0)
                      // {
                       //  argv[i] = NULL;
                       // flag =1;
                       // return i+1;
                      // }
                       if(strcmp(argv[i],"<") == 0)
                       {
                         argv[i] = NULL;
                         mark = 1;
                        
                         return i+1;
                       }
                          i++;           
                        return 0;
                    }     
}
int main()
{
char* argv[16];
  char buf[1024]={0};
   char* tmp1[8];
char* tmp2[8];
int fd[2];
int ret;
int fd1;
do
{ 
  flag = 0;
  mark = 0;
  printf("[myshell~]");
  fflush(stdout);
 // read(1,buf,1024);  
  scanf("%[^\n]%*c",buf);
  do_parse(buf,argv);                                                              
  ret=has_pipe(argv);
  // 管道实现
  // 要想实现管道，必须调用两个exec函数，所以要有子进程和孙子进程
  // 把命令分出来，让子进程调用pipe函数
  if(ret && !flag && !mark)
  {   
    int i=0;
    int j=ret;
    while(argv[i]!=NULL)
    {
      tmp1[i]=argv[i];
      i++;                                              
    }
    tmp1[i]=NULL;
    i=0;       
    while(argv[j]!=NULL)
    {
      tmp2[i++]=argv[j++];                                                                           
    }       
    tmp2[i]=NULL;
    pid_t pid_p=fork(); 
    if(pid_p==-1)
    {
      perror("pid_p");
      exit(EXIT_FAILURE);

    }
    else if(pid_p==0)
    {
      if(pipe(fd)==-1)
      {        
        perror("pipe");
        exit(EXIT_FAILURE);
      }
      pid_t pid_s=fork();        
      if(pid_s==-1)
      {
        perror("pid_s");
        exit(EXIT_FAILURE);

      }
      else if(pid_s==0)
      {
        close(fd[0]);         
        dup2(fd[1],1);   
        execvp(tmp1[0],tmp1); 
      }
      else                        
      { 
        close(fd[1]);       
        dup2(fd[0],0);               
        execvp(tmp2[0],tmp2);                    
        
      }
    }
      else{        
      
        wait(NULL);           
        
      }
      
      
    }
          else {  
            pid_t pid=fork();
            if(pid==-1)
          
            {
              perror("pid");
              exit(EXIT_FAILURE);

            }
            else if(pid==0)
            {
              //输出重定向
                   if(flag)
                   {
                     fd1 = open(argv[ret],O_WRONLY|O_CREAT,0664);
                       close(1); 
                     dup2(fd1,1);
                   }
               //输入重定向   
                    if(mark)
                   {
                    // close(0);
                     fd1 =open(argv[ret],O_RDWR|O_CREAT,0644);
                     //close(0);
                     dup2(fd1,0);
                   }
            int a =  execvp(argv[0],argv);
            if(a == -1)
            {
              perror("ececvp");
            }
              if(flag||mark)
              {
                 close(fd1);
              }
              

            }else{
              wait(NULL);                                               
            }            
          }
          memset(buf,0,1024);
}while(buf[0] != 'q');
}
