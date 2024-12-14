#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/ptrace.h>
#include <sys/user.h>
#include <sys/wait.h>

void	display_regs(struct user_regs_struct *regs)
{
	printf("RIP: 0x%x\n", regs->rip);
	printf("RBP: 0x%x\n", regs->rbp);
	printf("RSP: 0x%x\n", regs->rsp);
}

int	main(int ac, char **av)
{
	char			*progName;
	pid_t			child;
	int			status;
	int			options;
	int			signal;
	struct user_regs_struct	regs;
	int			i;

	if (ac < 2)
	{
		fprintf(stderr, "Usage: %s <program_path>\n", av[0]);
		return (1);
	}
	progName = av[1];
	child = fork();
	if (!child)
	{
		ptrace(PTRACE_TRACEME, NULL, NULL, NULL);
		execl(progName, progName, NULL);
	}
	options = 0;
	waitpid(child, &status, 0);
	signal = WSTOPSIG(status);
	if (signal == SIGTRAP)
		printf("Target process %s waiting, ready to start\n", progName);
	printf("Executing 10 instructions\n");
	for (i = 0; i < 10; ++i)
	{
		printf("Step: %d\n", i + 1);
		ptrace(PTRACE_SINGLESTEP, child, NULL, NULL);
		waitpid(child, &status, 0);
		ptrace(PTRACE_GETREGS, child, NULL, &regs);
		display_regs(&regs);
		puts("\n");
	}
	puts("Continuing...\n");
	ptrace(PTRACE_CONT, child, NULL, NULL);
	waitpid(child, &status, 0);
	printf("Child left with: %d\n", WIFEXITED(status));
	return (0);
}
