#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

int
main(int argc, char **argv)
{
	pid_t child;
	int status;
	char * argVec[] = {argv[1],NULL};
	if (argc < 2) {
		fprintf(stderr,"too few argument");
		exit(1);
	}
	switch((child=fork())) {
	case 0:
		execve(argv[1],argVec,NULL);
	case -1:
		perror("execve");
		exit(1);
	default:
		wait(&status);
	}
	return 0;
}
