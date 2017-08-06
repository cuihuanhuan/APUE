#include <stdio.h>

#include <sys/stat.h>
int
main(int argc, char **argv)
{
	mkfifo("james", 0666);
	return 0;
}
