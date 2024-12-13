#include <stdio.h>
#include <signal.h>
#include <unistd.h>

void	fatal(const char *err_msg)
{
	fprintf(stderr, "Error: %s\n", err_msg);
}

//Write random random random in a file
void	random_work()
{
	FILE	*temp_files;

	temp_files = fopen("/tmp/foo", "w");
	if (!temp_files)
		fatal("Cant open foo");
	else
	{
		fprintf(temp_files, "%s", "Random random random!\n");
		fclose(temp_files);
	}
}

//Delete created files
void	handler_termination(int sig)
{
	if (access("/tmp/foo", R_OK))
			return ;
	unlink("/tmp/foo");
	write(1, "\n", 1);
	printf("All clean! Closing...\n");
}

int	main()
{
	struct sigaction	interruption_handler;

	interruption_handler.sa_handler = handler_termination;
	sigaction(SIGINT, &interruption_handler, NULL);
	random_work();
	sleep(1000);
	handler_termination(0);
	return (0);
}

//https://en.wikipedia.org/wiki/System_call
//https://en.wikipedia.org/wiki/Inter-process_communication
//https://www.youtube.com/watch?v=UqzPhKbKGQI
//https://www.youtube.com/watch?v=fLS99zJDHOc
//https://www.youtube.com/watch?v=oZeezrNHxVo
