#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

int	main(void)
{
	pid_t	pid;
	int	a;
	int	i;
	int	status;
	int	signal;

	printf("Spliting work...\n");
	pid = fork();
	if (!pid)
	{
		a = 0;
		for (i = 0; i <  100000000; i++)
			a += i * 2 + 10 * i;
		return (9);
	}
	printf("Waiting child finish work...\n");
	waitpid(pid, &status, 0);
	if (WIFEXITED(status))
	{
		signal = WEXITSTATUS(status);
		printf("Child exited, status = %s\n", strsignal(signal));
	}
	return (1);
}

//https://notes.shichao.io/apue/ch8/
//https://linux.die.net/man/2/waitpid
//
