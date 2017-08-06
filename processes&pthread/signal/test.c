#include <stdio.h>
       #include <stdlib.h>

#include <unistd.h>


int
main(int argc, char **argv)
{
	alarm(10);

	printf("Hello\n");
	sleep(3);
	printf("Hello\n");
	sleep(3);
	printf("Hello\n");
	abort();
	sleep(3);
	printf("Hello\n");
	sleep(3);
	printf("Hello\n");
	sleep(3);
	printf("Hello\n");
	sleep(3);
	printf("Hello\n");
	sleep(3);
	printf("Hello\n");
	sleep(3);
	printf("Hello\n");
	sleep(3);
	printf("Hello\n");
	sleep(3);
	printf("Hello\n");
	sleep(3);
	return 0;
}
