#include "shm.h"

int
main(int argc, char **argv)
{
	int semid;
	int shmid;
	struct shm_buffer *p;
	semid=semget(SEM_KEY, 2, IPC_CREAT|IPC_EXCL|0600);
	if (semid == -1) {
		perror("semget");
		exit(1);
	}
	shmid=shmget(SHM_KEY, sizeof(struct shm_buffer), IPC_CREAT|IPC_EXCL|0600);
	if (shmid == -1) {
		perror("shmget");
		exit(1);
	}
	initSemAvailable(semid, WRITER);
	initSemInUse(semid, READER);
	p=(struct shm_buffer *)shmat(shmid, NULL, 0);
	for(;;) {
		reserveSem(semid, WRITER);
		fgets(p->data, 1020, stdin);
		p->cnt=strlen(p->data);
		if (!strncmp(p->data, "quit", 4)) {
			break;
		}
		releaseSem(semid, READER);
	}
	/*signal to reader quit*/
	releaseSem(semid, READER);
	/*make sure READER is exited*/
	reserveSem(semid, WRITER);
	shmdt(p);
	/*delete sem and shm*/
	shmctl(shmid, IPC_RMID, 0);
	semctl(semid, IPC_RMID, 0);
	return 0;
}
