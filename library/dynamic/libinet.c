#include <stdio.h>
       #include <sys/types.h>          /* See NOTES */
       #include <sys/socket.h>
 
       #include <sys/socket.h>
       #include <netinet/in.h>
       #include <arpa/inet.h>
#include <stdlib.h>

int Socket(int domain, int type, int protocol);
int Bind(int sockfd, int domain, const char *addr, const char *port);
int Listen(int sockfd, int backlog);
int Connect(int sockfd, char *addr, char *port);


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

