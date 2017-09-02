#include <stdio.h>
       #include <sys/types.h>          /* See NOTES */ 
       #include <sys/socket.h> 
  
       #include <sys/socket.h> 
       #include <netinet/in.h> 
       #include <arpa/inet.h> 

#define MAXLINE 	256

       /* According to POSIX.1-2001, POSIX.1-2008 */
       #include <sys/select.h>

       /* According to earlier standards */
       #include <sys/time.h>
       #include <sys/types.h>
       #include <unistd.h>
#include <string.h>
#include <stdlib.h>

int
main(int argc, char **argv)
{
	int peerfd;
	fd_set rfds;
	fd_set wfds;
	fd_set efds;
	struct timeval timeout;
	int retval;
	char buffer[MAXLINE];
	char readbuffer[MAXLINE];

	struct sockaddr_storage clientaddr;
	socklen_t clientaddrlen;

	if(argc < 3) {
		fprintf(stderr, "Usage: %s <host> <port>", argv[0]);
		exit(1);
	}
	FD_ZERO(&rfds);
	FD_ZERO(&wfds);
	FD_ZERO(&efds);

	timeout.tv_sec = 30;
	timeout.tv_usec = 0;

	peerfd = inetConnect(AF_INET, SOCK_STREAM, argv[1], argv[2]);
	for(;;) {
		FD_ZERO(&rfds);
		FD_ZERO(&wfds);
		FD_ZERO(&efds);
		timeout.tv_sec = 30;
		timeout.tv_usec = 0;
		FD_SET(STDIN_FILENO, &rfds);
		FD_SET(peerfd, &rfds);
		retval = Select(peerfd+1, &rfds, &wfds, &efds,    &timeout);
		if (FD_ISSET(STDIN_FILENO, &rfds)) {
			int nwrite;
			fgets(readbuffer, MAXLINE, stdin);
			strlen(readbuffer);
			/*we assume send data always available*/
			Write(peerfd, readbuffer, strlen(readbuffer)+1);
		}
		if (FD_ISSET(peerfd, &rfds)) {
			int nread;
			nread = read(peerfd, buffer, MAXLINE);
			if (nread == -1) {
				perror("read");
				exit(1);
			}
			if (nread == 0) {
				fprintf(stderr,"Bye!");
				exit(1);
			}
			buffer[nread] = '\0';
			printf("Peer:%s\n", buffer);
		}
	}
	return 0;
}
