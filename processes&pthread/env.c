#include <stdio.h>

extern char **environ;

int
main(int argc, char **argv)
{
	char **ep;
	int i=0;
	printf("I'm ./a.out\n");
	while(i<argc) {
		puts(argv[i++]);
	}
#if 0
	for (ep=environ; *ep != NULL; ep++) {
		puts(*ep);
	}
#endif
	return 0;
}
