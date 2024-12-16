int	main()
{
	int	x;

	x = 4;
	__asm__(
			"int $0x03"
	       );
}

//__asm__ macro allows assembly code directly on .c file
//gdb ./a.out
//(gdb) run
//(gdb) disas
