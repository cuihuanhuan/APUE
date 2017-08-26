#include <stdio.h>
#include <sys/types.h>          /* See NOTES */
#include <sys/socket.h>
#include <sys/un.h>
#include <stdlib.h>
#include <unistd.h>

#define SOCKNAME "/tmp/socktest"
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
	sockfd=socket(AF_UNIX, SOCK_STREAM, 0);
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

	ret=listen(sockfd, 5);
	if (ret == -1) {
		perror("listen");
		exit(1);
	}

	for(;;) {
		sockpeer=accept(sockfd, NULL, NULL);

		write(sockpeer, "Welcome King server!\n",22);
		while((readsize=read(sockpeer, buffer, BUFFER_SIZE))>0) {
			if (!strncmp(buffer, "quit", 4)) {
				close(sockpeer);
				break;
			}
			if (write(STDOUT_FILENO, buffer, readsize) != readsize) {
				perror("write");
				close(sockpeer);
				continue;
			}
			putchar('#');
			fflush(stdout);
		}


		close(sockpeer);
	}
	remove(SOCKNAME);
	
	
	return 0;
}
