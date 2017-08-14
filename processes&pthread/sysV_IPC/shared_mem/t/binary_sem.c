#include <stdio.h>
       #include <sys/types.h>
       #include <sys/ipc.h>
       #include <sys/sem.h>

union semun {
	int              val;    /* Value for SETVAL */
	struct semid_ds *buf;    /* Buffer for IPC_STAT, IPC_SET */
	unsigned short  *array;  /* Array for GETALL, SETALL */
	struct seminfo  *__buf;  /* Buffer for IPC_INFO
				    (Linux-specific) */
};

int initSemAvailable(int semid, int semnum)
{
	union semun arg;
	arg.val = 1;
	return semctl(semid, semnum, SETVAL, arg);
}

int initSemInUse(int semid, int semnum)
{
	union semun arg;
	arg.val = 0;
	return semctl(semid, semnum, SETVAL, arg);
}

int reserveSem(int semId, int semNum)
{
	struct sembuf sop;
	sop.sem_num = semNum;
	sop.sem_op = -1;
	sop.sem_flg = 0;
	return semop(semId, &sop, 1);
}

int releaseSem(int semId, int semNum)
{
	struct sembuf sop;
	sop.sem_num = semNum;
	sop.sem_op = 1;
	sop.sem_flg = 0;
	return semop(semId, &sop, 1);
	
}
