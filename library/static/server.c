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

int Socket(int domain, int type, int protocol);
int Bind(int sockfd, int domain, const char *addr, const char *port);
int Listen(int sockfd, int backlog);
int Connect(int sockfd, char *addr, char *port);
int Accept(int sockfd, struct sockaddr *addr, socklen_t *addrlen);
int Write(int peerfd, char *buffer, size_t size);

int inetListen(int domain, int type, char *addr, char *port, int backlog);

int inetConnect(int domain, int type, char *addr, char *port);

int Select(int maxfd1, fd_set *rfds, fd_set *wfds, fd_set *efds, struct timeval * timeout);

int
main(int argc, char **argv)
{
	int sockfd;
	fd_set rfds;
	fd_set wfds;
	fd_set efds;
	struct timeval timeout;
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
			FD_ZERO(&rfds);
			FD_ZERO(&wfds);
			FD_ZERO(&efds);
			timeout.tv_sec = 30;
			timeout.tv_usec = 0;
			FD_SET(STDIN_FILENO, &rfds);
			FD_SET(peerfd, &rfds);

			Select(peerfd+1, &rfds, &wfds, &efds, &timeout);
			if (FD_ISSET(STDIN_FILENO, &rfds)) {
				fgets(readbuffer, MAXLINE, stdin);
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
					fprintf(stderr,"Client over and out!");
					break;
				}
				buffer[nread] = '\0';
				printf("Peer:%s\n", buffer);
			}
		}
	}
	return 0;
}
