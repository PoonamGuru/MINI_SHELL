#include"minishell.h"


extern process * chld;
extern int Pid_t;
extern int flag;
int  insert_job(char * buffer)
{
    process * temp;
    static short i = 0;

    if(chld == NULL)
    {
	chld = malloc(sizeof(process));
	if(chld == NULL) 
	{
	    fprintf(stderr , "malloc faild to allocate memory\n");
	    return 1;
	}

	else
	{
	    chld->pid = Pid_t;
	    chld->next = NULL;
	    i++;
	    chld->indx = i;
	    strcpy(chld->proc_name , buffer);
	    return 0;
	}
    }

    temp = chld;


    while(temp->next != NULL)
    {
	temp= temp->next;

    }

    temp->next  = malloc(sizeof(process));
    if(temp == NULL) 
    {
	fprintf(stderr , "malloc faild to allocate memory\n");
	return 1;
    }

    else
    {
	temp->next->pid = Pid_t;
	temp->next->next = NULL;
	i++;
	temp->next->indx = i ;
	strcpy(temp->next->proc_name , buffer);
	return 0;
    }


}

int delete_job( int pid)
{
    process * temp = chld;
    process * temp_1 ;

    printf("%d\n", pid);


    if(temp != NULL)
    {
	if(pid == chld->pid)
	{
	    chld = temp->next;
	    free(temp);
	    return 0;
	}
    }


    while(temp->next != NULL) 
    {
	if(temp->next->pid == pid)
	{

	    temp_1 = temp->next;
	    temp->next = temp->next->next;
	    free(temp_1);
	    return 1;
	}
	temp = temp->next;
    }
} 



int list_jobs(void)
{
    process * temp;
    temp = chld;

    if(temp == NULL)
    {
	printf("ERROR : No more jobs\n");
	return 1;
    }

    while(temp != NULL)
    {

	printf("\n[%d]  %d %s\n", temp->indx , temp->pid, temp->proc_name);
	temp = temp->next;
    }

    return 0;

}




