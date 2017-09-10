#include <stdio.h>
       #include <sys/types.h>          /* See NOTES */
       #include <sys/socket.h>

       /* According to POSIX.1-2001, POSIX.1-2008 */
       #include <sys/select.h>

       /* According to earlier standards */
       #include <sys/time.h>
       #include <sys/types.h>
       #include <unistd.h>
#include <stdlib.h>
       /* According to POSIX.1-2001, POSIX.1-2008 */
       #include <sys/select.h>

       /* According to earlier standards */
       #include <sys/time.h>
       #include <sys/types.h>
       #include <unistd.h>
#include <string.h>

#define MAXLINE 256
#define FDARRAY_NR 2

int
main(int argc, char **argv)
{
	int sockfd;
	fd_set rfds;
	fd_set wfds;
	fd_set efds;
	struct timeval timeout;
	int retval;
	char buffer[MAXLINE];
	char readbuffer[MAXLINE];

	struct sockaddr_storage clientaddr;
	socklen_t clientaddrlen;
	int peerfd;

	if (argc < 3) {
		fprintf(stderr, "Usage: %s <host> <port>", argv[0]);
		exit(1);
	}


	
	sockfd = inetListen(AF_INET, SOCK_STREAM, argv[1], argv[2], SOMAXCONN);

	for(;;) {
		peerfd = Accept(sockfd, (struct sockaddr *)&clientaddr, &clientaddrlen);

		while(1) {
				int nwrite;
				int nread;
				fgets(readbuffer, MAXLINE, stdin);
				nwrite=strlen(readbuffer);
				/*we assume send data always available*/
				Write(peerfd, readbuffer, strlen(readbuffer)+1);
				nread = read(peerfd, buffer, MAXLINE);
				if (nread == -1) {
					perror("read");
					exit(1);
				}
				if (nread == 0) {
					fprintf(stderr,"Client over and out!");
					break;
				}
				buffer[nread] = '\0';
				printf("Peer:%s\n", buffer);
		}
	}
	return 0;
}
