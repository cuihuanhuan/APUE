#include <stdio.h>
#include <signal.h>

void abc(int sig)
{
	/*non-safe*/
	printf("Hello,world\n");
}

int
main(int argc, char **argv)
{
	signal(SIGUSR2, abc);
	printf("%lld\n",getpid());
	while(1) {
		getchar();
	}
	return 0;
}
