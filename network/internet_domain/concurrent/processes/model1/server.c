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




#define SERVICE_PORT 50001
#define BUFFER_SIZE 128




void *doit(int sockfd)
{
	int peerfd = sockfd;
	char buffer[BUFFER_SIZE] = {0};
	char ipbuffer[INET_ADDRSTRLEN];
	int nwrite;
	int nread;
	struct sockaddr_storage clientaddr;
	socklen_t clientaddrlen;
	int retval = 1;

        strcpy(buffer, "\tWelcome login this server\n");
        int msg_size = strlen("\tWelcome login this server\n");
        if ((nwrite=write(peerfd, buffer, msg_size)) != msg_size) {
            perror("write:send welcome failed");
            shutdown(peerfd, SHUT_RDWR);
	    exit(retval);
        }
        while(1) {
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
    struct mypeer peer_sock;
    pid_t childpid;

    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sockfd == -1) {
        perror("socket");
        exit(1);
    }
    serveraddr.sin_family = AF_INET;
    serveraddr.sin_addr.s_addr = htonl(INADDR_ANY);
    serveraddr.sin_port = htons(SERVICE_PORT);
    if (bind(sockfd, (struct sockaddr *)&serveraddr, sizeof(struct sockaddr_in)) == -1) {
        perror("bind");
        exit(1);
    }
    if (listen(sockfd, 50) == -1) {
        perror("listen");
        exit(1);
    }
    for(;;) {
        clientaddrlen = sizeof(struct sockaddr_storage);
        peer_sock.peerfd = accept(sockfd, (struct sockaddr *)&peer_sock.clientaddr, &peer_sock.clientaddrlen);
        if (peerfd == -1) {
            perror("accept");
            continue;
        }
	
	if ((childpid = fork()) == 0) {
		close(sockfd);
		doit(peer_sock.peerfd);
		exit(0);
	}
	close(peer_sock.peerfd);
    }
    return 0;
}
