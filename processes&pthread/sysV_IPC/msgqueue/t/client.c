#include "header.h"

static int clientId;

void removeQueue(void)
{
	msgctl(clientId, IPC_RMID, NULL);
}


int
main(int argc, char **argv)
{
	int serverId;
	int n;
	struct requestMsg msg;
	struct responesMsg resp;
	int times;

	serverId = msgget(SERVER_KEY, S_IWUSR);
	if (serverId == -1) {
		perror("msgget");
		exit(1);
	}
	clientId = msgget(IPC_PRIVATE, IPC_CREAT|IPC_EXCL|0600);
	if (clientId == -1) {
		perror("msgget client queue");
		exit(1);
	}
	atexit(removeQueue);

	msg.mtype=1;
	msg.clientId = clientId;
	strcpy(msg.pathname,argv[1]);
	n = msgsnd(serverId, &msg, 260, 0);
	if (n == -1) {
		perror("msgsnd");
		exit(1);
	}

	n = msgrcv(clientId, &resp, BUF_SIZE, 0, 0);
	if (n == -1) {
		perror("msgrcv");
		exit(1);
	}
	if (resp.mtype == RESP_MT_FAILURE) {
		fprintf(stderr, "%s", resp.data);
		msgctl(clientId, IPC_RMID, NULL);
		exit(1);
	}
	printf("mtype=%d:\n",resp.mtype);
	for(times=1;resp.mtype==RESP_MT_DATA;times++) {
		n = msgrcv(clientId, &resp, BUF_SIZE, 0, 0);
		if (n == -1) {
			perror("msgrcv");
			exit(1);
		}
		printf("James2:\n");
		fprintf(stderr, "%s", resp.data);
	}
	return 0;
}
