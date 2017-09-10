#include <stdio.h>
       #include <sys/types.h>          /* See NOTES */
       #include <sys/socket.h>
 
       #include <sys/socket.h>
       #include <netinet/in.h>
       #include <arpa/inet.h>
#include <stdlib.h>


int Socket(int domain, int type, int protocol)
{
	int sockfd;
	sockfd = socket(domain, type, protocol);
	if (sockfd == -1) {
		perror("Socket");
		exit(1);
	}
	return sockfd;
}
int Bind(int sockfd, int domain, const char *addr, const char *port)
{
	int ret;
	struct sockaddr_in serveraddr;
	serveraddr.sin_family = AF_INET;
	inet_aton(addr, &serveraddr.sin_addr);
	serveraddr.sin_port = htons(atoi(port));


	ret = bind(sockfd, (struct sockaddr *)&serveraddr, (socklen_t)sizeof(struct sockaddr_in));
	if (ret == -1) {
		perror("Bind");
		exit(1);
	}
	return ret;
}

int Listen(int sockfd, int backlog)
{
	int ret;
	ret = listen(sockfd, backlog);
	if (ret == -1) {
		perror("listen");
		exit(1);
	}
}

int Connect(int sockfd, char *addr, char *port)
{
	int ret;
	struct sockaddr_in serveraddr;
	serveraddr.sin_family = AF_INET;
	inet_aton(addr, &serveraddr.sin_addr);
	serveraddr.sin_port = htons(atoi(port));


	ret = connect(sockfd, (struct sockaddr *)&serveraddr, sizeof(struct sockaddr_in));
	if (ret == -1) {
		perror("Connect");
		exit(1);
	}
	return ret;
}
int inetListen(int domain, int type, char *addr, char *port, int backlog)
{
	int sockfd;
	sockfd = Socket(AF_INET, SOCK_STREAM, 0);
	Bind(sockfd, AF_INET, addr, port);
	Listen(sockfd, SOMAXCONN);
	return sockfd;
}
int inetConnect(int domain, int type, char *addr, char *port)
{
	int sockfd;
	sockfd = Socket(AF_INET, SOCK_STREAM, 0);
	Connect(sockfd, addr, port);

	return sockfd;
}

int Select(int maxfd1, fd_set *rfds, fd_set *wfds, fd_set *efds, struct timeval * timeout)
{
	int retval;

	retval = select(maxfd1, rfds, wfds, efds, timeout);
	if (retval == -1) {
		perror("Select");
		exit(1);
	}
	return retval;

}

int Accept(int sockfd, struct sockaddr *addr, socklen_t *addrlen)
{
	int peerfd;
	peerfd = accept(sockfd, addr, addrlen);
	if (peerfd == -1) {
		perror("Accept");
		exit(1);
	}
}

int Write(int peerfd, char *buffer, size_t size)
{
	int retval;
	retval = write(peerfd, buffer, size);
	if (retval == -1) {
		perror("Write");
		exit(1);
	}
	if (retval != size) {
		perror("Write");
		exit(1);
	}
	return retval;
}
