       #include <sys/types.h>
       #include <unistd.h>
#include<signal.h>
#include<stdio.h>

void signal_handler(int arg)
{
    signal(SIGINT , SIG_DFL);
    return;
}

int main()
{

    int pid = fork();

	signal(SIGINT , signal_handler);

    if(pid)
    {
	sleep(3);
    }

    else
    {
	while(1)
	    printf("hi");
    }

}

