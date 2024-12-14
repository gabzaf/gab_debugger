#include <unistd.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/ptrace.h>

int	main(int ac, char **av)
{
	char	*cmnd;
	char	**args;
	pid_t	child_pid;
	char	in;

	if (ac < 3)
	{
		printf("Usage: %s <command> <args>\n", av[0]);
		return (1);
	}
	cmnd = av[1];
	args = &av[1];
	child_pid = fork();
	if (!child_pid)
	{
		ptrace(PTRACE_TRACEME, NULL, NULL, NULL);
		execv(cmnd, args);
	}
	do
	{
		puts("Iniciar processo ? [y/n]: ");
		in = getchar();
	}
	while (in != 'y');
	ptrace(PTRACE_CONT, child_pid, NULL, NULL);
	return (0);
}
$ ./a.out /bin/ls -la
