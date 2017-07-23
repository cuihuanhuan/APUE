#include <stdio.h>
       #include <unistd.h>
       #include <sys/types.h>
#include <stdlib.h>


int
main(int argc, char **argv)
{
	int ret;
	ret=truncate("helloworld", 100000);
	if (ret == -1) {
		perror("truncate");
		exit(0);
	}
	return 0;
}
