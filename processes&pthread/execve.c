#include <stdio.h>
#include <unistd.h>


int
main(int argc, char **argv)
{
	char *argVec[]={"./b.out","-l","-s","-a",NULL};
	execve("/bin/ls",argVec,NULL);
	printf("Hello,woooooooooooooooooooorld\n");
	return 0;
}
