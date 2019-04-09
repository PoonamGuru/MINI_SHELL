#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

void create_pipe(char ** arg , short p_count , short * p);
void first_command(int * fd , char ** arg);
void last_command(int * fd , char ** arg);
char ** array_of_string(char * buffer , short space ,short * p);
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

int main()
{
    char buffer[50];
    short space = 0, p_count = 0;
    char ** arg;
    short p[6] = {0};
    int i = 0, j = 0;
    fgets(buffer , 50 , stdin);
    buffer[strlen(buffer) - 1 ] = '\0';

    extract_the_string(buffer, &space, &p_count );

    printf("space = %d\npipes = %d\n", space , p_count);

    arg =  array_of_string(buffer , space, p);
#if 0
int fd[2] ;
pipe(fd);
int pid = fork();
if(pid) 
{

    int pid_1 = fork();
    if(pid_1)
    {
	close(fd[0]);
	close(fd[1]);
	wait(NULL);
	wait(NULL);
    }

    else
    {
    close(fd[1]);
    dup2(fd[0] , 0);
    puts(arg[1]);
    if(execvp(arg[p[0]+1] , arg+p[0]+1) == -1)
	perror("execvp");
    }
}


else
{
    close(fd[0]);
    dup2(fd[1], 1);
    execvp(arg[0] , arg+0);

}

#endif





    create_pipe(arg ,  p_count ,  p);
    return 0;
}




char ** array_of_string(char * buffer , short space , short * pipe)
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
	    //	    puts(arg[i]);
	}

	else if(token[0] == '|')
	{
	    arg[i] = NULL;
	    pipe[k] = i;
	    k++;
	}
	i++;
	token = strtok(NULL, " ");

    }
    arg[i] = NULL;



    return arg;

}

void create_pipe(char ** arg , short p_count , short * p)
{
    int i, j = 0;

    int pid[p_count + 1];
    int fd[2];


   // for( i = 0 ; i < p_count ; i++)
	pipe(fd);

    for( i = 0; i < p_count + 1 ; i++)
    {


	if(  (pid[i] = fork()))
	{
	    if(j == 0)
	    {
		for(j = 0; j < 2; j++)
		    close(fd[j]);

		j = 1;
	    
	    }

	    sleep(2);
	    waitpid(pid[i] , NULL ,0);
	    printf("%d is terminated\n", pid[i]);
	}
	else
	{
	    if(i == 0)
	    {


		printf("%d child created\n" , i);
		//first_command(fd[i] , arg);
		first_command(fd , arg);
		puts("furu");
	    }

	    else if( i == p_count)
	    {
		j=0;
		printf("%d child created\n" , i);
		//last_command(fd[j] , arg+p[j]+1);
		printf("%s\n", arg[p[0]+1]);
		last_command(fd , arg+p[0]+1);
		puts("guru");
	    }



	    exit(0);
	}
    }
}



void first_command(int * fd , char ** arg)
{
    close(fd[0]);
    dup2(fd[1], 1);
    execvp(arg[0] , arg+0);

}


void last_command(int * fd , char ** arg)
{
    printf("last command\n");
    close(fd[1]);
    dup2(fd[0] , 0);
    if(execvp(arg[0] , arg+0) == -1)
	perror("execvp");

}

