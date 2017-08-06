#include <stdio.h>
#include <signal.h>

int
main(int argc, char **argv)
{
	printf("%lld\n",getpid());
	signal(SIGINT, SIG_IGN);
	signal(SIGQUIT, SIG_IGN);
	while(1)pause();
	return 0;
}
