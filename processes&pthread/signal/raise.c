#include <stdio.h>
#include <signal.h>
#define _GNU_SOURCE
#include <string.h>

void abc(int sig)
{
	static int a = 0;
	printf("%d:SIGUSR2\n",a);
	a++;
}

int
main(int argc, char **argv)
{
	printf("%s\n",strsignal(9));
	return 0;
}
