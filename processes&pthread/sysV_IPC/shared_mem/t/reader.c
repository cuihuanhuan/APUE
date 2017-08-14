#include "shm.h"

int
main(int argc, char **argv)
{
	int semid;
	int shmid;
	struct shm_buffer *w;

	semid = semget(SEM_KEY, 0, 0);
	if (semid == -1) {
		perror("semget");
		exit(1);
	}
	shmid = shmget(SHM_KEY, 0, 0);
	if (shmid == -1) {
		perror("shmget");
		exit(1);
	}
	w = (struct shm_buffer *)shmat(shmid, NULL, 0);
	for(;;) {
		reserveSem(semid, READER);
		printf("%d,%s\n", w->cnt, w->data);
		if (!strncmp(w->data, "quit", 4)) {
			break;
		}
		releaseSem(semid, WRITER);
	}
	shmdt(w);
	releaseSem(semid, WRITER);


	return 0;
}
