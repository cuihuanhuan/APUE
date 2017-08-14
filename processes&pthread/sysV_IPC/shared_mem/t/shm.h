#ifndef __SHM_H
#define __SHM_H
       #include <sys/types.h>
       #include <sys/ipc.h>
       #include <sys/sem.h>
#include <stdio.h>
#include <stdlib.h>
       #include <sys/shm.h>
#include <string.h>



#define SEM_KEY	0x4109
#define SHM_KEY	0x0308

#define WRITER	0
#define READER	1

struct shm_buffer {
	int cnt;
	char data[1020];
};

int initSemAvailable(int semid, int semnum);
int initSemInUse(int semid, int semnum);
int reserveSem(int semId, int semNum);
int releaseSem(int semId, int semNum);
#endif
