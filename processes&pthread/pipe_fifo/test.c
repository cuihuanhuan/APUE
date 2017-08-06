#define _GNU_SOURCE
#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>



int
main(int argc, char **argv)
{
	int len;
	int fd[2];
	pipe(fd);
	len=fpathconf(fd[0], _PC_PIPE_BUF);
	printf("pipe_buf_len=%d\n",len);
	len=fcntl(fd[0],F_GETPIPE_SZ);
	printf("pipe_len=%d\n",len);

	return 0;
}
