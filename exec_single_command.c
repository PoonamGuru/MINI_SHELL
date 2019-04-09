#include"minishell.h"
extern process chld;
extern int Pid_t;
extern int flag;
char ** multiple_string(char * buffer)
{
    short i , j , l, k;

    char **arg;

    //replace space with '\0'

    for(i = 0, k = 0; buffer[i] != '\0' ; i++)
    {
	if(buffer[i] == ' ')
	{
	    k++;
	    buffer[i] = '\0';
	}

    }


    /*create a 2d array of string*/

    arg = malloc((k + 2) * sizeof(char *));
    for(i = 0, j = 0; i < k+1 ; i++)
    {
	arg[i] = malloc(strlen(buffer+j) +1);

	/*store '\0' seperated string to arg*/

	for(l = 0; buffer[j] != '\0'; j++, l++)
	    arg[i][l] = buffer[j];

	arg[i][l] = '\0';
	j++;
//	puts(arg[i]);

    }

    arg[i] = NULL;

//    for(i = 0; arg[i] != NULL ; i++)
//	puts(arg[i]);

    return arg;
}
    







int  execute_command(char ** arg)
{

    int status;

    Pid_t = fork();


    if(Pid_t) // parent
    {
//	printf("%d\n",flag);

	waitpid(Pid_t ,&status, WUNTRACED);

//	if(WIFEXITED(status))
//	{
//	    printf("%d\n" , WEXITSTATUS(status));
//	    return WEXITSTATUS(status);
//	}
    //return status;
//	wait(NULL);

   }


    else // child
    {

       status = execvp(arg[0] , arg);
       if(status == -1)
	   perror("status");
    }



}

