#include <stdio.h>
       #include <sys/types.h>          /* See NOTES */
       #include <sys/socket.h>
 
       #include <sys/socket.h>
       #include <netinet/in.h>
       #include <arpa/inet.h>
#include <stdlib.h>
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

