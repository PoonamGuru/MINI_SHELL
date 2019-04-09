#include<stdio.h>
#include<stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

int main(char ** argv)
{
    int pid[5];
    int i;

    for(i = 0; i < 5; i++)
    {
       if((pid[i] = fork()))
       {
	    waitpid(pid[i] , NULL , 0);
       puts("terminated");
    }
       else
       {
	   printf("%d i am child \n", i);
	   exit(0);
       }
    }

    for( i = 0; i < 5;i++)
	    waitpid(pid[i] , NULL , 0);
}

