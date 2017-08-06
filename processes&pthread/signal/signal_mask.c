#include <stdio.h>
#include <signal.h>
#include <stdlib.h>


int
main(int argc, char **argv)
{
	int ret;
	sigset_t blockSet, prevMask;
	printf("PID:%d\n",getpid());
	sigemptyset(&blockSet);
	sigaddset(&blockSet, SIGINT);
	sigaddset(&blockSet, SIGQUIT);
	ret=sigprocmask(SIG_BLOCK, &blockSet, &prevMask);
	if (ret == -1) {
		perror("sigprocmask");
		exit(1);
	}
	printf("Please try.\n");
	sleep(10);
	if (sigprocmask(SIG_SETMASK, &prevMask, NULL) == -1) {
	//if (sigprocmask(SIG_UNBLOCK, &blockSet, NULL) == -1) {
		perror("sigprocmask");
		exit(1);
	}
	printf("Over.\n");
	return 0;
}
