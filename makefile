a.out : color.o exec_single_command.o minishell.o pipe.o signal_handl.o jobs.o  fg_bg.o
	gcc color.o exec_single_command.o minishell.o pipe.o signal_handl.o jobs.o fg_bg.o

minishell.o : minishell.c
	      gcc -c minishell.c

color.o : color.c
	gcc -c color.c
exec_single_command.o :  exec_single_command.c
			gcc -c  exec_single_command.c

pipe.o : pipe.c 
	gcc -c pipe.c

signal_handl.o : signal_handl.c
	gcc -c signal_handl.c

jobs.o : jobs.c
	gcc -c jobs.c

fg_bg.o : fg_bg.c
	  gcc -c fg_bg.c

clean: 
	rm *.o *.out





