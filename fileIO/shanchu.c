#include <stdio.h>

int
main(int argc, char **argv)
{
	if (argc < 2) {
		fprintf(stderr, "too few arguments");
	}
	remove(argv[1]);
	return 0;
}
