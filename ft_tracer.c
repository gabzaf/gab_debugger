#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include <sys/wait.h>
#include <sys/ptrace.h>
#include <sys/user.h>

void	display_process_info(pid_t pid)
{
	struct user_regs_struct	regs;

	ptrace(PTRACE_GETREGS, pid, NULL, &regs);
	printf("Child %d Registers:\n", pid);
	printf("R15: 0x%x\n", regs.r15);
	printf("R14: 0x%x\n", regs.r14);
	printf("R12: 0x%x\n", regs.r12);
	printf("R11: 0x%x\n", regs.r11);
	printf("R10: 0x%x\n", regs.r10);
	printf("RBP: 0x%x\n", regs.rbp);
	printf("RAX: 0x%x\n", regs.rax);
	printf("RCX: 0x%x\n", regs.rcx);
	printf("RDX: 0x%x\n", regs.rdx);
	printf("RSI: 0x%x\n", regs.rsi);
	printf("RDI: 0x%x\n", regs.rdi);
	printf("RIP: 0x%x\n", regs.rip);
	printf("CS:  0x%x\n", regs.cs);
	printf("EFGLAS: 0x%x\n", regs.eflags);
}

int	exists(char *fpath)
{
	return (access(fpath, F_OK) != -1);
}

void	handle_breakpoint(pid_t pid)
{
	printf("Child %d hits a breakpoint!\n", pid);
}

//given the child pid and address, im gonna get the code that is in that locale. After, im gonna add an instruction on LSB
uint64_t	add_breakpoint(pid_t pid, uint64_t address)
{
	uint64_t	break_opcode;
	uint64_t	code_at;
	uint64_t	breakpoint_code;

	break_opcode = 0xCC;
	code_at = ptrace(PTRACE_PEEKDATA, pid, address, NULL);
	breakpoint_code = (code_at & ~0xFF) | break_opcode;
	ptrace(PTRACE_POKEDATA, pid, address, breakpoint_code);
	return (code_at);
}

int	main(int ac, char **av)
{
	char		*bin_path;
	uint64_t	breakpoint;
	pid_t		pid;
	int		status;
	int		signal;
	char		input[100];
	if (ac < 3)
	{
		fprintf(stderr, "Usage: %s <bin_name> <breakpoint>\n", av[0]);
		return (1);
	}
	bin_path = av[1];
	breakpoint = strtol(av[2], NULL, 16);
	status = 0;
	if (!exists(bin_path))
	{
		fprintf(stderr, "Invalid path!\n");
		return (1);
	}
	puts("Forking...\n");
	pid = fork();
	if (!pid)
	{
		ptrace(PTRACE_TRACEME, 0, NULL, NULL);
		execl(bin_path, bin_path, NULL);
	}
	wait(&status);
	if (WIFEXITED(status))
	{
		fprintf(stderr, "Unable to trace %s\n", bin_path);
		return (1);
	}
	printf("Adding breakpoint on 0x%x\n", breakpoint);
	add_breakpoint(pid, breakpoint);
	ptrace(PTRACE_CONT, pid, NULL, NULL);
	wait(&status);
	while (!WIFEXITED(status))
	{
		signal = WSTOPSIG(status);
		switch(signal)
		{
			case SIGTRAP:
				puts("We just hit a breakpoint!\n");
				break ;
		}
		printf("> ");
		fgets(input, 100, stdin);
		if (!strcmp(input, "infor\n"))
			display_process_info(pid);
		else if (!strcmp(input, "continue\n"))
		{
			ptrace(PTRACE_CONT, pid, NULL, NULL);
			wait(&status);
		}
	}
	printf("Child %d finished...\n", pid);
	return (0);
}

//https://fasterthanli.me/series/making-our-own-executable-packer/part-1
//https://www.tutorialspoint.com/embedded_systems/es_interrupts.htm
//https://en.wikipedia.org/wiki/Breakpoint
//https://wiki.osdev.org/Interrupt_Descriptor_Table#Structure_AMD64
