#include <stdio.h>
       #include <sys/types.h>
       #include <signal.h>

#define MYSIG 15606 
int
main(int argc, char **argv)
{
	int ret;
	int i;
	for (i=0;i<22000010;i++) {
		ret=kill(MYSIG,SIGUSR1);
		if(ret == -1) {
			perror("kill");
			exit(1);
		}
	}
	kill(MYSIG,SIGINT);
	return 0;
}
