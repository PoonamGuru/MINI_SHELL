#include"minishell.h"

process *  chld = NULL;
int    Pid_t = -1;
char cur_wd[100];
int flag = 0;
   
int main()
{
    char env_var[4]= "PS1";
    char  old_wd[100] , buffer[200] , time[50];
    char prev_wd[50];
    char ** arg;
    char ** pipe_arg;

   int status = -1; 
    char  buffer_dup[50];
    short space = 0 , p_count = 0;

    /*get the current wrking directory*/
    getcwd(cur_wd , 100);
    strcpy(old_wd , cur_wd);



    megenta();
    puts("----------------------------------------------------------------------------------------------------------------------\n\n");
    reset();
    green();
    puts("\t\t\t\t\t Welcome to MINI SHELL VERSION");
    reset();
    megenta();
    puts("\n\n----------------------------------------------------------------------------------------------------------------------");
    reset();

    signal(SIGINT, signal_handler);
    signal(SIGTSTP, signal_tstp);

    while(1)
    {	
    
	    green();
	    printf("\n%s:> ",cur_wd);
	    reset();
	//read the input from the user

	fgets(buffer , 200 , stdin);
	buffer[strlen(buffer) - 1] = '\0';
	strcpy(buffer_dup , buffer);
	

		arg = multiple_string(buffer_dup);   // convert the sting to multiple string

//	printf("buffer : %s\n",buffer);
	/*pipelie*/
	if(search_pipe(buffer) == 1)
	{
	    space = 0 , p_count = 0;

	    extract_the_string(buffer, &space, &p_count ); 
//	    printf("space = %d\npipes = %d\n", space , p_count); 
	    pipe_arg =  array_of_string(buffer , space);
	    create_pipe(pipe_arg ,  p_count );

	}

	else
	{
	    /*change the prompt*/
	    if(buffer[0] == 'P'&& buffer[1] == 'S' && buffer[2] == '1')
	    {
	       change_prompt( buffer,   cur_wd);
	       printf("\n%s:>",cur_wd);
	    }

	    
	   


	    //current working direcotry
	    else if(strcmp(buffer , "pwd") == 0)
	    {   
		getcwd(cur_wd , 50);
		printf("\n%s\n",cur_wd);
	    }

	    //exit from the mini shell
	    else if(strcmp(buffer,"exit") ==0)
	    { 
		exit(1);
	    }

	    //cd command
	    else if(str_space_cmp(buffer , "cd") == 0)
	    {
		status = change_dir(buffer , cur_wd);
	    }
	    //jobs list 
	    else if(strcmp(buffer,"jobs") == 0)
		status = list_jobs();

	    //fg command
	    else if(buffer[0] == 'f' && buffer[1] == 'g')
		status = fore_ground_prcess(arg);

	    //bg coomand
	    else if(buffer[0] == 'b' && buffer[1] == 'g')
		status = back_ground_process(arg);


	    else
	    {
		status = execute_command(arg);
	    }


//	    arg = multiple_string(buffer);   // convert the sting to multiple string
	    //special varaible
	    if(strcmp(arg[0] , "echo") == 0)
	    {

		/*previous command return value*/
		if(strcmp(arg[1], "$?") == 0)
		{
		    printf("%d\n" , status);
		}


		else if(strcmp(arg[1] , "$SHELL") == 0)
		{
		    puts(old_wd);
		}

		else if(strcmp(arg[1] , "$$") == 0)
		{
		    printf("%d\n", getpid());
		}

	    }

	    if(flag == 1)
		insert_job(buffer);

	    flag = 0;

	}



//	green();
	//printf("\n%s:>",getcwd(cur_wd,50));
///	printf("\n%s:>",cur_wd);
///	reset();

    }

    return 0;
}



int change_dir(char * buffer, char * cur_wd)
{
    char * buf;
    static    char prev_wd[50];
    int i = 0;
    int status = 0;

    /*home directory*/
    if((strcmp(buffer,"cd") == 0) || ( strcmp(buffer, "cd ") == 0))
    {
	strcpy(prev_wd , getcwd(NULL , 50));
	status = chdir("/home/poonam");
	getcwd(cur_wd , 50);
	return status ;
    }

    else
    {
	while(buffer[i] != ' ') i++;
	i++;

	/*home directory*/
	if(strcmp(buffer+i , "~") == 0)
	{
	    strcpy(prev_wd , getcwd(NULL , 50));
	    status = chdir("/home/poonam");
	getcwd(cur_wd , 50);
	    return status ;
	}

	/*home directory*/
	else if(strcmp(buffer+i , ".") == 0)
	{
	    strcpy(prev_wd , getcwd(NULL , 50));
	    getcwd(cur_wd, 50);
	    status = chdir(cur_wd);
	    return status ;
	}

	/*previous directory*/
	else if(strcmp(buffer+i , "-") == 0)
	{
	    status = chdir(prev_wd);
	    getcwd(cur_wd , 50);
	    return status ;
	}

	/*other directory*/
	else
	{
	    strcpy(prev_wd , getcwd(NULL , 50));
	    if((status = chdir(buffer+i)) == -1)
	    {
		//perror("chdir");
		return status ;
	    }
	    getcwd(cur_wd , 50);
	}

    }
}





void change_prompt(char * buffer, char *  cur_wd)
{

    //char env_var[4] = "PS1";

    int i = 4, j = 0;

	if(!(buffer[3] == ' ' || buffer[5] == ' ' || buffer[4] == ' ' ))
	{
	    if(buffer[3] == '=')
	    {

		while(buffer[i] != '\0')
		{
		    cur_wd[j] = buffer[i];
		    i++;
		    j++;
		}
		cur_wd[j] = '\0';
	    }
	}
            printf("%s\n", cur_wd);


}


int str_space_cmp(char * dest , char * src)
{

    short int i = 0 , j = 0;


    while(src[i] != '\0' )
    {
	if(dest[i] == src[i])
	{
	    i++;
	}

	else
	{
	    return -1;
	}
    }

    return 0;
}

