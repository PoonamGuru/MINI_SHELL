#include"minishell.h"

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

    }

    arg[i] = NULL;

//    for(i = 0; arg[i] != NULL ; i++)
//	puts(arg[i]);

    return arg;
}
    







int  execute_command(char ** arg)
{

    int pid , status;

    pid = fork();


    if(pid) // parent
    {
	wait(NULL);
    }


    else // child
    {

       status = execvp(arg[0] , arg);
       if(status == -1)
	   perror("status");
    }


    return status;
}

