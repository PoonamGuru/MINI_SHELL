#include "minishell.h"
int search_pipe(char * buffer)
{
    int i = 0;
    while(buffer[i] != '\0')
    {
	if(buffer[i] == '|')
	    return 1;
	i++;
    }

    return 0;
}

void extract_the_string(char * buffer, short * space, short * p_count)
{

    short i = 0 , k = 0 ,j;

    /*no of white space*/
    while(buffer[i] != '\0')
    {
	if(buffer[i] == ' ')
	{
	    (*space)++;
	}

	if(buffer[i] == '|')
	{
	    (*space)++;

	    if((buffer[i - 1] != ' ') && (buffer[i+1] != ' '))
		(*space) += 2;

	    else if(buffer[i-1] != ' ' || buffer[i+1] != ' ')
		(*space)++ ;

	    (*p_count)++;
	}
	i++;
    }

    (*space)++;
}

char ** array_of_string(char * buffer , short space )
{

    short i = 0 , k = 0 ,j , l;
    char * token;
    char ** arg;
    /*create a array of pointers*/

    arg = malloc((space) * sizeof(char *));

    token = strtok(buffer , " ");

    while(token != NULL)
    {
	//puts(token);
	arg[i] = malloc(strlen(token) + 1);

	if(token[0] != '|')
	{
	    for(j = 0, l = 0; token[j] != '\0'; j++)
	    {
		arg[i][l] = token[j];
		l++;
	    }

	    arg[i][l] = '\0';
	}

	else if(token[0] == '|')
	{
	    arg[i] = NULL;
	}
	i++;
	token = strtok(NULL, " ");

    }
    arg[i] = NULL;



    return arg;

}

void create_pipe(char ** arg , short p_count)
{
    int i;
    int j = 0 ;
    int pid;
    int fd[2];
    int fd_in = 0;
    for( i = 0; i < p_count + 1 ; i++)
    {

	pipe(fd);
	if(  (pid = fork()))
	{

	    waitpid(pid , NULL ,0);
	    close(fd[1]);
	    fd_in = fd[0];


	    //	    printf("%d is terminated\n", pid);
	}
	else
	{
	    //	    printf("%d child created\n" , i);
	    printf("%s\n", arg[j]);


	    dup2(fd_in , 0);
	    if(i != p_count)
	    {
		dup2(fd[1] , 1);
	    }

	    close(fd[0]);
	    execvp(arg[j] , arg+j);

	    exit(0);
	}


	while(arg[j] != NULL) j++;
	j++;

    }
}





