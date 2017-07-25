#include <stdio.h>
#include <string.h>
#include <unistd.h>


int
main(int argc, char **argv)
{
	pid_t parent;
	pid_t child;
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
		printf("I'm waiting\n");
		wait(&status);
		printf("I'm going to finished\n");
		break;
		
	}
	printf("I'm %s\n",name);
	return 0;
}
