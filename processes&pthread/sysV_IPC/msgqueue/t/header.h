#ifndef __HEADER_H
#define __HEADER_H
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
       #include <string.h>

       #include <sys/types.h>
       #include <sys/ipc.h>
       #include <sys/msg.h>

       #include <sys/types.h>
       #include <sys/stat.h>
       #include <fcntl.h>

       #include <signal.h>

	#include <errno.h>


#define SERVER_KEY 0x41098007

#define MAX_FILENAME 256
#define BUF_SIZE	512

struct requestMsg {
	long mtype;
	char pathname[MAX_FILENAME];
	int clientId;
};

struct responesMsg {
	long mtype;
	char data[BUF_SIZE];
};

#define RESP_MT_FAILURE 1
#define RESP_MT_DATA	2
#define RESP_MT_END	3
#endif
