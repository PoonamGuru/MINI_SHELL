#include"minishell.h"


extern process chld;
extern char cur_wd[100];

extern int Pid_t;
extern int flag;
void signal_handler(int arg)
{
    if(arg == SIGINT)
    {
	/*if no foreground process*/
	if(Pid_t == -1)
	{
	    puts("");
//	    printf("%s:>",cur_wd);
	    puts(cur_wd);
	    
	}

	/*there is any foreground process*/
	else
	{
	    kill(Pid_t , SIGKILL);
	}
    }

}

/*if ctrl + z is press */
void signal_tstp(int arg)
{
    if(arg == SIGTSTP)
    {
	if(Pid_t == -1)
	{
	    puts("");
	    puts(cur_wd);
	}
	else
	{
	    flag = 1;
	kill(Pid_t , SIGTSTP);
	printf("%d stopped \n ",Pid_t);
	}
    }
}

void signal_chld(int arg , siginfo_t * info , void * ptr)
{
    if(arg == SIGCHLD)
    {

	waitpid(info->si_pid , NULL ,0);
    }

}
