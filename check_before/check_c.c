#include<stdio.h>
#include<sys/types.h>
#include<unistd.h>
#include <sys/wait.h>


int main(int argc , char ** argv)
{
    int pid = fork();

    if(pid== 0) //child
    {

	execvp(argv[1] , argv);
    }


    else  //parent
    {
	while(1)
	    puts("poonam");
    }
}

