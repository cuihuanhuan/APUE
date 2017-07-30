#include <stdio.h>
void abc(void) {
	printf("Output in atexit\n");
}

int
main(int argc, char **argv)
{
	atexit(abc);
	printf("Hello,world\n");
	printf("Hello,world\n");
	printf("Hello,world\n");
	printf("Hello,world\n");
	printf("Hello,world\n");
	printf("Hello,world\n");
	printf("Hello,world\n");
	return 0;
}
