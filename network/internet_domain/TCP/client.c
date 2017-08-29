       #include <sys/types.h>          /* See NOTES */
       #include <sys/socket.h>
       #include <netinet/in.h>
       #include <netinet/ip.h> /* superset of previous */
#include <string.h>
#include <stdlib.h>
#include <stdio.h>


#define SERVICE_PORT    50001
#define SERVER_IP   "127.0.0.1"
#define BUFFER_SIZE     128


int main(int argc,char **argv)
{
    int sockfd;
    struct sockaddr_in serveraddr;
    int nread;
    int nwrite;
    int msg_size;
    char buffer[BUFFER_SIZE];
    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sockfd == -1) {
        perror("socket");
        exit(1);
    }
    serveraddr.sin_family = AF_INET;
    serveraddr.sin_port = htons(SERVICE_PORT);
    inet_pton(AF_INET, SERVER_IP, &serveraddr.sin_addr.s_addr);

    if (connect(sockfd, (struct sockaddr *)&serveraddr, sizeof(struct sockaddr_in)) == -1) {
        perror("connect");
        exit(1);
    }
        
    nread = read(sockfd, buffer, BUFFER_SIZE);
    if (nread == -1) {
        perror("read");
        exit(1);
    }
    buffer[nread] = '\0';
    printf("%s\n", buffer);
    for(;;) {
        fgets(buffer, BUFFER_SIZE, stdin);
        msg_size = strlen(buffer) + 1;
        nwrite = write(sockfd, buffer, msg_size);
        if (nwrite != msg_size) {
            perror("write");
            exit(1);
        }
        nread = read(sockfd, buffer, BUFFER_SIZE);
        if (nread == -1) {
            perror("read");
            exit(1);
        }
        printf("%s\n",buffer);
    }
    return 0;
}
