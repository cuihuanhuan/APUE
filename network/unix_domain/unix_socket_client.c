#include <stdio.h>
#include <sys/types.h>          /* See NOTES */
#include <sys/socket.h>
#include <sys/un.h>
#include <stdlib.h>

#define SOCKNAME "/tmp/socktest"
#define BUFFER_SIZE 128

int
main(int argc, char **argv)
{
	int sockfd;
	int sockpeer;
	int ret;
	char buffer[BUFFER_SIZE];
	struct sockaddr_un my_sockaddr;
	sockfd=socket(AF_UNIX, SOCK_STREAM, 0);
	if (sockfd == -1) {
		perror("socket");
		exit(1);
	}
	memset(&my_sockaddr, 0, sizeof(struct sockaddr_un));
	my_sockaddr.sun_family = AF_UNIX;
	strcpy(my_sockaddr.sun_path, SOCKNAME);

	ret=connect(sockfd, (struct sockaddr *)&my_sockaddr, sizeof(struct sockaddr_un));
	if (ret == -1) {
		perror("connect");
		exit(1);
	}
	for(;;) {

		read(sockfd, buffer, 22);
		printf("%s\n", buffer);
		scanf("%s", buffer);
		if (write(sockfd, buffer, strlen(buffer)) != strlen(buffer)) {
			perror("write");
			close(sockpeer);
			continue;
		}
		if (!strncmp(buffer, "quit", 4)) {
			break;
		}
	}
	close(sockpeer);
	return 0;
}
