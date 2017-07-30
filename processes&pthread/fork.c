#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>


int
main(int argc, char **argv)
{
	pid_t pid;
	int i;
	int status;
	char name[10] = {'\0'};
	switch(pid=fork()) {
	case 0:
		strcpy(name,"Child");
		printf("Child process:\n");
		for (i=0;i<10;i++) {
			printf("Child process: Hello!\n");
			sleep(1);
		}
		exit(58);
		break;
	case -1:
		perror("fork");
		break;
	default:
		strcpy(name,"Parent");
		printf("Parent process:\n");
		for (i=0;i<10;i++) {
			printf("Parent process: Hi!\n");
		}
		printf("I'm parent and waiting\n");
		wait(&status);
		printf("I have recv child's return value: %d\n",WEXITSTATUS(status));
		break;
		
	}
	printf("I'm %s\n",name);
	return 0;
}
