#include <stdio.h>
#include <signal.h>

void sigcont(int sig)
{
	printf("SIGCONT\n");
	printf("SIGCONT\n");
}

int
main(int argc, char **argv)
{
	printf("%lld\n",getpid());
	signal(SIGINT, sigcont);
	while(1)pause();
	printf("Over!\n");
	return 0;
}
