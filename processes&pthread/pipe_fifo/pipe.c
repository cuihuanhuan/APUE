#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>


int
main(int argc, char **argv)
{
	int fd[2];
	int ret;
	ret=pipe(fd);
	if(ret==-1) {
		perror("pipe");
		exit(1);
	}
	switch(fork()) {
		case -1:
			perror("fork");
			exit(1);
		case 0:
			if (close(fd[0]==-1)) {
				perror("child1:close");
				exit(1);
			}
			if (fd[1]!=STDOUT_FILENO) {
				if(dup2(fd[1],STDOUT_FILENO)==-1) {
					perror("child1:dup2");
					exit(1);
				}
				if(close(fd[1])==-1) {
					perror("child1:close");
					exit(1);
				}
				execlp("ls","ls",(char *)NULL);
				perror("execlp");
				exit(1);
			}
		default:
			break;
	}

	switch(fork()) {
	case -1:
		perror("fork");
		exit(1);
	case 0:
		if (close(fd[1]) == -1) {
			perror("close");
			exit(1);
		}
		if (fd[0] != STDIN_FILENO) {
			if (dup2(fd[0], STDIN_FILENO) == -1) {
				perror("dup2");
				exit(1);
			}
			if (close(fd[0]) == -1) {
				perror("close");
				exit(1);
			}
		}
		execlp("wc","wc","-l", (char *)NULL);
		perror("execlp wc");
		exit(1);
	default:
		break;
	}
	if(close(fd[0]) == -1) {
		perror("close");
		exit(1);
	}
	if(close(fd[1]) == -1) {
		perror("close");
		exit(1);
	}
	if(wait(NULL) == -1) {
		perror("wait 1");
		exit(1);
	}
	if(wait(NULL) == -1) {
		perror("wait 2");
		exit(1);
	}

	exit(EXIT_SUCCESS);

	return 0;
}
