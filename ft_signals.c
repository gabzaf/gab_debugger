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
	if (access("/tmp/foo", R_OK)
			return ;
	unlink("/tmp/foo");
	printf("All clean! Closing...\n");
}

int	main()
{
}
