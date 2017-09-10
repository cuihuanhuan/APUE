#include <stdio.h>
       #include <poll.h>
#include <limits.h>
#include <errno.h>
#include <stdlib.h>
       #include <sys/socket.h>
       #include <netinet/in.h>
       #include <netinet/ip.h> /* superset of previous */



#define OPEN_MAX 1024
#define MAXLINE 256

int
main(int argc, char **argv)
{
	int sockfd;
	int connfd;
	struct pollfd client[OPEN_MAX];
	int i;
	int maxi;
	int nready;
	int nread;
	struct sockaddr_storage cliaddr;
	int clilen;
	char buffer[MAXLINE];
	sockfd = inetListen(AF_INET, SOCK_STREAM, argv[1], argv[2], SOMAXCONN);
	client[0].fd = sockfd;
	client[0].events = POLLRDNORM;
	for(i=1;i<OPEN_MAX;i++) {
		client[i].fd = -1;
	}
	maxi = 0;
	for(;;) {
		nready = poll(client, maxi + 1, -1);
		if(client[0].revents & POLLRDNORM) {
			clilen = sizeof(cliaddr);
			connfd = Accept(sockfd, (struct sockaddr *)&cliaddr, &clilen);
			for(i=1;i<OPEN_MAX; i++) {
				if (client[i].fd < 0) {
					client[i].fd = connfd;
					break;
				}
			}
			if (i == OPEN_MAX) {
				fprintf(stderr, "max files");
				exit(1);
			}
			client[i].events = POLLRDNORM;
			if(i>maxi) {
				maxi = i;
			}
			if (--nready <= 0)
				continue;
		}
		for(i=1;i<=maxi; i++) {
			if ((connfd = client[i].fd) < 0) {
				continue;
			}
			if(client[i].revents & (POLLRDNORM|POLLERR)) {
				nread = read(connfd, buffer, MAXLINE);
				if (nread == -1) {
					perror("read");
					exit(1);
				}
				else if (errno == ECONNRESET) {
					close(connfd);
					client[i].fd = -1;
				}
				else if (nread == 0) {
					fprintf(stderr,"Client over and out!");
					close(connfd);
					client[i].fd = -1;
				}else {
					write(connfd, buffer, nread);
				}
				if (--nready <= 0) {
					break;
				}

			}
		}
	}
	return 0;
}
