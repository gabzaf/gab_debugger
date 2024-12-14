#include <unistd.h>
#include <stdio.h>

int	main(int argc, char **argv)
{
	char	*cmnd;
	char	**args;

	if (argc < 3)
	{
		printf("Usage: %s <command> <args>\n", argv[0]);
		return (1);
	}
	cmnd = argv[1];
	args = &argv[1];
	printf("First arg => %s\n", args[0]);
	execv(cmnd, args);
	puts("Continua?\n");
	return (0);
}

$ ./exec /bin/ls -lah
