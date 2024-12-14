#include <unistd.h>
void main()
{
	write(1, "HACK\n", 5);
}

//strace strace /bin/ls 2>&1 | grep -A2 clone
