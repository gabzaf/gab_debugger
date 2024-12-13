#include <stdio.h>
#include <signal.h>
#include <unistd.h>

void	simple_handler(int sig)
{
	printf("\n");
	printf("Hello SIGINT\n");
}

int	main()
{
	struct sigaction sig_handler = { simple_handler };

	sigaction(SIGINT, &sig_handler, NULL);
	sleep(100);
	return (0);
}

//kill -l -> show me every signal and their numbers
//Run a.out. Open another terminal and search for the a.out pid with ps ax | grep a.out, then kill -2 <pid>
