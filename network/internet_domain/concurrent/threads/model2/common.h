#ifndef _COMMON_H
#define _COMMON_H
typedef struct {
	pthread_t thread_tid;
	long thread_count;
}my_Thread;
my_Thread *tptr;
#define MAXNCLI 32
int clifd[MAXNCLI], iget, iput;
pthread_mutex_t clifd_mutex;
pthread_cond_t clifd_cond;
#endif
