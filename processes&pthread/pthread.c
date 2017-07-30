#include <stdio.h>
#include <pthread.h>

pthread_mutex_t cntr_mutex = PTHREAD_MUTEX_INITIALIZER;

long protVariable = 0L;

void *mythread(void *arg) {
	int i;
	pthread_mutex_lock(&cntr_mutex);
	for (i=0;i<10000;i++) {
		protVariable++;	
	}
	pthread_mutex_unlock(&cntr_mutex);
	pthread_exit(NULL);
}


int
main(int argc, char **argv)
{
	
	pthread_t pthread[100];
	int ret;
	int i;
	for (i=0; i<100; i++) {
		ret=pthread_create(&pthread[i],NULL,mythread,NULL);
		if (ret!=0) {
			perror("pthread_create");
		}
	}
	for (i=0; i<100; i++) {
		ret=pthread_join(pthread[i],NULL);
		if (ret!=0) {
			perror("pthread_create");
		}
	}
	printf("protVariable:%ld",protVariable);

	return 0;
}
