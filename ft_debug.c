int	main()
{
	int	x;

	x = 4;
	__asm__(
			"int $0x03"
	       );
}

//gdb ./a.out
//(gdb) run
//(gdb) disas
