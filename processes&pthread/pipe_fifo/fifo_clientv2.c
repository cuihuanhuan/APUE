#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdlib.h>


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
	int clientfd;
	struct request *req;
	struct respones *resp;
	char client_name[20];
	int n;
	serverfd = open(SERVER_FIFO_NAME, O_WRONLY);
	if (serverfd == -1) {
		perror("open server_fifo");
		exit(1);
	}
	/*make the name of fifo*/
	printf("make name of client fifo.\n");
	sprintf(client_name,CLIENT_FIFO_NAME, getpid());
	if(mkfifo(client_name, 0666) == -1) {
		perror("mkfifo");
		exit(1);
	}
	

	printf("make request to..server.\n");
	/*make a request*/
	req=(struct request*)malloc(sizeof(struct request));
	req->pid = getpid();
	req->people = 1;

	/*send this request*/
	printf("write..to..server.\n");
	n=write(serverfd, req, sizeof(struct request));
	if (n != sizeof(struct request)) {
		perror("send request failed");
		exit(1);
	}
	free(req);

	printf("open name of client fifo.\n");
	clientfd=open(client_name, O_RDONLY);
	if(clientfd == -1) {
		perror("open client failed");
		exit(1);
	}

	resp=(struct respones*)malloc(sizeof(struct respones));
	printf("read..from server.\n");
	n=read(clientfd, resp, sizeof(struct respones));
	if (n != sizeof(struct respones)) {
		perror("receive respones failed");
		exit(1);
	}
	printf("%d\n",resp->seqnum);

	return 0;
}
