#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <stdlib.h>
#include <fcntl.h>
#define CLIENT_FIFO_NAME "./client.%ld"
#define SERVER_FIFO_NAME "./server_fifo"
struct request
{
	pid_t pid;
	int people;
};
struct respones
{
	int seqnum;
};
int
main(int argc, char **argv)
{
	int serverfd;
	int serverfd_w;
	int clientfd;
	struct request *req;
	struct respones *resp;
	int n;
	char client_name[20];
	int i=1;
	n=mkfifo(SERVER_FIFO_NAME, 0666);
	serverfd = open(SERVER_FIFO_NAME, O_RDONLY);
	serverfd_w = open(SERVER_FIFO_NAME, O_WRONLY);
	printf("finish open server fifo\n");
	req=(struct request*)malloc(sizeof(struct request));
	resp=(struct respones*)malloc(sizeof(struct respones));
	for(;;) {
		n = read(serverfd, req, sizeof(struct request));
		if (n != sizeof(struct request)) {
			printf("read failed\n");
			continue;
		}
		sprintf(client_name,CLIENT_FIFO_NAME, req->pid);
		clientfd=open(client_name, O_WRONLY);
		resp->seqnum = i;
		i++;
		n=write(clientfd, resp, sizeof(struct respones));
		if (n != sizeof(struct respones)) {
			perror("send respones failed");
			continue;
		}
	}
	return 0;
}
