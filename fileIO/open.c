#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdlib.h>
#include <unistd.h>

#define BUFFER_SIZE 2048
char buffer[2048];
int main(int argc, char **argv)
{
	int fd;
	int fd1;
	int count;
	if (argc < 3) {
		dprintf(STDERR_FILENO, "too few arguments");
		exit(0);
	}
	fd = open(argv[1], O_RDONLY);
	if (fd == -1) {
		perror("open");
		exit(0);
	}
	fd1 = open(argv[2], O_WRONLY|O_CREAT|O_TRUNC, 0664);
	if (fd1 == -1) {
		perror("open file2");
		exit(0);
	}
	int n=0;
	do {
		count=read(fd,buffer,BUFFER_SIZE);
		write(fd1,buffer,count);
		if (n % 10 == 0) {
			fsync(fd1);
		}
		n++;
	}while(count);
	close(fd);
	close(fd1);
	return 0;
}
