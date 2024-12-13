#include <sys/types.h>
#include <unistd.h>
#include <stdio.h>

int	main(void)
{
	pid_t	pid;

	printf("Processo normal...\n");
	printf("Forking...\n");
	sleep(5);
	pid = fork();
	if (pid == 0)
		printf("Eu sou o processo filho meu PID: %d\n", pid);
	else
		printf("Eu sou o processo pai meu PID: %d\n", pid);
	sleep(5);
	return (0);
}

//pstree
//ps -ef
