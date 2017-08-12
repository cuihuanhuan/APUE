#include "header.h"

static void
XXXX1(int sig)
{
	int savedErrno;
	/* SIGCHLD handler */
	savedErrno = errno;
	/* waitpid() might change 'errno' */
	while (waitpid(-1, NULL, WNOHANG) > 0)
		continue;
	errno = savedErrno;
}

static void
serveRequest(struct requestMsg *msg)
{
	/*I'm child*/
	int fd;
	struct responesMsg resp;
	int n;
	/*open file*/
	fd = open(msg->pathname, O_RDONLY);
	if (fd == -1) {
		sprintf(resp.data,"%s\n",strerror(errno));
		resp.mtype = RESP_MT_FAILURE;
		n=msgsnd(msg->clientId, &resp, BUF_SIZE, 0);
		if (n == -1) {
			perror("msgsnd:return msg failed");
			exit(1);
		}
	}
	/*read data*/
	while(n=read(fd, resp.data, BUF_SIZE-1)) {
		if (n == -1) {
			perror("read");
			exit(1);
		}
		resp.data[n] = '\0';
		resp.mtype = RESP_MT_DATA;
		/*send data to client*/
		n = msgsnd(msg->clientId, &resp, BUF_SIZE, 0);
		if (n == -1) {
			perror("msgsnd send msg failed");
			exit(1);
		}
	}

	/*send end of file*/
	resp.mtype = RESP_MT_END;
	msgsnd(msg->clientId, &resp, BUF_SIZE, 0);
}

int
main(int argc, char **argv)
{
	int msgid;
	struct requestMsg msgbuffer;
	struct sigaction sa;
	int n;
	pid_t pid;
	/*create message queue*/
	msgid = msgget(SERVER_KEY, IPC_CREAT|IPC_EXCL|0660);
	if (msgid == -1) {
		perror("msgget: create message queue");
		exit(1);
	}

	sigemptyset(&sa.sa_mask);
	sa.sa_handler=XXXX1;
	sa.sa_flags = SA_RESTART;
	sigaction(SIGCHLD, &sa, NULL);

	for(;;) {
		if (n=msgrcv(msgid, &msgbuffer, 260, 0, 0) == -1) {
			perror("msgrcv");
			continue;
		}
		pid=fork();
		switch(pid) {
		case 0:/*I'm in child process*/
			serveRequest(&msgbuffer);
			break;
		case -1:
			perror("fork");
			break;
		default:
			;
		}
	}
	return 0;
}
