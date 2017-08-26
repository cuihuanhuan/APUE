#include <stdio.h>
#include <sys/types.h>          /* See NOTES */
#include <sys/socket.h>
#include <sys/un.h>
#include <stdlib.h>

#define MYSOCKNAME "/tmp/sock_dgram_test_client"
#define SOCKNAME "/tmp/sock_dgram_test"
#define BUFFER_SIZE 128

int
main(int argc, char **argv)
{
	int sockfd;
	int sockpeer;
	int ret;
	char buffer[BUFFER_SIZE];
	struct sockaddr_un my_sockaddr;
	struct sockaddr_un server_sockaddr;
	int recvsize;
	if (argc <2 ) {
		fprintf(stderr, "%s <string>", argv[0]);
		exit(0);
	}
	sockfd=socket(AF_UNIX, SOCK_DGRAM, 0);
	if (sockfd == -1) {
		perror("socket");
		exit(1);
	}
	/*server socket*/
	memset(&server_sockaddr, 0, sizeof(struct sockaddr_un));
	server_sockaddr.sun_family = AF_UNIX;
	strcpy(server_sockaddr.sun_path, SOCKNAME);
	/*our socket*/
	memset(&my_sockaddr, 0, sizeof(struct sockaddr_un));
	my_sockaddr.sun_family = AF_UNIX;
	strcpy(my_sockaddr.sun_path, MYSOCKNAME);
	ret=bind(sockfd, (struct sockaddr *)&my_sockaddr,         (socklen_t)sizeof(struct sockaddr_un));
	if (ret == -1) {
		perror("bind");
		exit(1);
	}
	sendto(sockfd, argv[1], strlen(argv[1])+1, 0, (struct sockaddr *)&server_sockaddr, sizeof(server_sockaddr));
	for(;;) {

		recvsize=recvfrom(sockfd, buffer, BUFFER_SIZE, 0, NULL, NULL);
		printf("recvfrom:%s\n",buffer);
		if (recvsize == -1) {
			perror("recvfrom");
			exit(1);
		}
	}
	return 0;
}
