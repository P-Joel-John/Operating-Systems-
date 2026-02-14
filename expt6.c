//combining using fork() AND wait() system calls
#include<stdio.h>
#include<stdlib.h>
#ifdef _WIN32
#include<windows.h>
#else
#include<sys/types.h>
#include<sys/wait.h>
#include<unistd.h>
#endif
int main(){
      pid_t pid;
      pid=fork();
      if (pid==0){//CHILD
                       printf("PCCSL407 ");
       }
      else if (pid>0){//parent
                       wait(NULL);
                       printf("operating systems lab\n");
       }    
return 0;
}

