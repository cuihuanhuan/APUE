#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <stdio.h>
#include <sys/types.h>          /* See NOTES */
#include <sys/socket.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netinet/ip.h> /* superset of previous */
#include <arpa/inet.h>
#include <pthread.h>

#include "common.h"

static int nthreads;

pthread_mutex_t clifd_mutex = PTHREAD_MUTEX_INITIALIZER;
pthread_cond_t clifd_cond = PTHREAD_COND_INITIALIZER;




#define SERVICE_PORT 50001
#define BUFFER_SIZE 128


void *thread_main(void *arg)
{
	int peerfd;
	char buffer[BUFFER_SIZE] = {0};
	char ipbuffer[INET_ADDRSTRLEN];
	int nwrite;
	int nread;
	struct sockaddr_storage clientaddr;
	socklen_t clientaddrlen;
	int retval = 1;

	pthread_detach(pthread_self());


	while(1) {
		pthread_mutex_lock(&clifd_mutex);
		while(iget == iput) {
			pthread_cond_wait(&clifd_cond, &clifd_mutex);
		}
		peerfd = clifd[iget];
		if (++iget == MAXNCLI) {
			iget = 0;
		}
		pthread_mutex_unlock(&clifd_mutex);
		tptr[(long)arg].thread_count++;

		strcpy(buffer, "\tWelcome login this server\n");
		int msg_size = strlen("\tWelcome login this server\n");
		if ((nwrite=write(peerfd, buffer, msg_size)) != msg_size) {
			perror("write:weclone send failed:");
			shutdown(peerfd, SHUT_RDWR);
			pthread_exit(&retval);
		}

		for(;;) {

			if ((nread = read(peerfd, buffer, BUFFER_SIZE)) == -1) {
				perror("read");
				break;
			}
			if (nread == 0) {
				printf("read EOF break loop\n");
				close(peerfd);
				break;
			}
			printf("Data from %s:%s\n", inet_ntop(AF_INET, 
						&((struct sockaddr_in*)&clientaddr)->sin_addr, 
						ipbuffer, 
						INET_ADDRSTRLEN), 
					buffer);
			snprintf(buffer, BUFFER_SIZE, "%d bytes from %s\n", nread, ipbuffer);
			nwrite = write(peerfd, buffer, strlen(buffer)+1);
			if (nwrite != strlen(buffer)+1) {
				perror("write");
				break;
			}

		}
		close(peerfd);
	}
}
struct mypeer{
	int peerfd;
	struct sockaddr_storage clientaddr;
	socklen_t clientaddrlen;
};
int main(int argc,char **argv)
{
	int sockfd;
	int peerfd;
	struct sockaddr_in serveraddr;
	struct sockaddr_storage clientaddr;
	socklen_t clientaddrlen;
	pthread_t thread;
	struct mypeer peer_sock;
	long i;

	sockfd = socket(AF_INET, SOCK_STREAM, 0);
	if (sockfd == -1) {
		perror("socket");
		exit(1);
	}
	serveraddr.sin_family = AF_INET;
	if (argc == 3) {
		serveraddr.sin_addr.s_addr = htonl(INADDR_ANY);
		serveraddr.sin_port = htons(atoi(argv[1]));
	}else if (argc == 4) {
		inet_pton(AF_INET, argv[1], &serveraddr.sin_addr);
		serveraddr.sin_port = htons(atoi(argv[2]));
	}else {
		fprintf(stderr, "usage: %s [<host>] <port#> <#threads>", argv[0]);
		exit(1);
	}
	if (bind(sockfd, (struct sockaddr *)&serveraddr, sizeof(struct sockaddr_in)) == -1) {
		perror("bind");
		exit(1);
	}
	if (listen(sockfd, 50) == -1) {
		perror("listen");
		exit(1);
	}
	nthreads = atoi(argv[argc-1]);
	tptr = calloc(nthreads, sizeof(my_Thread));
	iget = iput = 0;
	for(i=0; i< nthreads; i++) {
		pthread_create(&tptr[i].thread_tid, NULL, &thread_main, (void*)i);
	}
	for(;;) {
		peer_sock.clientaddrlen = sizeof(struct sockaddr_storage);
		peer_sock.peerfd = accept(sockfd, (struct sockaddr *)&peer_sock.clientaddr, &peer_sock.clientaddrlen);
		if (peerfd == -1) {
			perror("accept");
			continue;
		}
		pthread_mutex_lock(&clifd_mutex);
		clifd[iput] = peer_sock.peerfd;
		if (++iput == MAXNCLI) {
			iput = 0;
		}
		if(iput == iget) {
			break;
		}
		pthread_cond_signal(&clifd_cond);
		pthread_mutex_unlock(&clifd_mutex);
	}
	return 0;
}
