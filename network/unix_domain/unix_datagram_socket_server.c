#include <stdio.h>
#include <sys/types.h>          /* See NOTES */
#include <sys/socket.h>
#include <sys/un.h>
#include <stdlib.h>
#include <unistd.h>

#define SOCKNAME "/tmp/sock_dgram_test"
#define BUFFER_SIZE 128

int
main(int argc, char **argv)
{
	int sockfd;
	int sockpeer;
	int ret;
	int readsize;
	char buffer[BUFFER_SIZE];

	struct sockaddr_un my_sockaddr;
	struct sockaddr_un peer_sockaddr;
	socklen_t sockaddr_len;
	ssize_t recvsize;
	sockfd=socket(AF_UNIX, SOCK_DGRAM, 0);
	if (sockfd == -1) {
		perror("socket");
		exit(1);
	}

	memset(&my_sockaddr, 0, sizeof(struct sockaddr_un));
	my_sockaddr.sun_family = AF_UNIX;
	strcpy(my_sockaddr.sun_path, SOCKNAME);
	ret=bind(sockfd, (struct sockaddr *)&my_sockaddr, (socklen_t)sizeof(struct sockaddr_un));
	if (ret == -1) {
		perror("bind");
		exit(1);
	}

	for(;;) {
		recvsize=recvfrom(sockfd, buffer, BUFFER_SIZE, 0, (struct sockaddr *)&peer_sockaddr, &sockaddr_len);
		printf("recvfrom: %s\n", buffer);
		recvsize=sendto(sockfd, "Welcome King server!\n",22, 0, (struct sockaddr *)&peer_sockaddr, sockaddr_len);
		if (recvsize == -1) {
			perror("sendto");
			continue;
		}
		printf("1sendto\n");
		buffer[0]='A';
		recvsize=sendto(sockfd, buffer, recvsize, 0, (struct sockaddr *)&peer_sockaddr, sockaddr_len);
		if (recvsize == -1) {
			perror("sendto");
			continue;
		}
		printf("2sendto\n");

	}
	remove(SOCKNAME);
	
	
	return 0;
}
