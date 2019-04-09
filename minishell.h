#ifndef MINISHELL_H
#define MINISHELL_H

#include<stdio.h>
#include <unistd.h>
#include<string.h>
#include <time.h>
#include<stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include<signal.h>


typedef struct process_t
{
  int pid; 
    int status;
    short indx;
    char proc_name[30];
    struct process_t * next;
}process;



void change_prompt(char * buffer, char *  cur_wd);
char * get_time(void);
void blue();
void reset();
void red();
void megenta();
void green();

int search_pipe(char * buffera);
int str_space_cmp(char * dest , char * src);
void str_after_space_cpy(char *buffer , char * buf);
int change_dir(char * bufferi, char * cur_wd);
char ** multiple_string(char * buffer);
char ** array_of_string(char * buffer , short space );
void extract_the_string(char * buffer, short * space, short * p_count);
void create_pipe(char ** arg , short p_count);
void signal_handler(int arg);
void signal_tstp(int arg); 
void signal_chld(int arg , siginfo_t * info , void * ptr);
int execute_command(char ** arg);

int  insert_job(char * buffer);
int list_jobs(void);
int delete_job( int pid );

int  fore_ground_prcess(char ** arg);
int  back_ground_process(char ** arg);
#endif
