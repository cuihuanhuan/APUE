#include <stdio.h>
#include <pthread.h>
#include <sched.h>

pthread_mutex_t cntr_mutex = PTHREAD_MUTEX_INITIALIZER;
pthread_cond_t cntr_cond = PTHREAD_COND_INITIALIZER;

long protVariable = 0L;

void *producer(void *arg) {
	int i;
	for (i=0;i<10000;i++) {
		pthread_mutex_lock(&cntr_mutex);
		printf("Producer:make %d, product:%d\n", i,protVariable);
		protVariable+=i;	
		pthread_mutex_unlock(&cntr_mutex);
		pthread_cond_broadcast(&cntr_cond);
	}
	pthread_exit(NULL);
}
void *consumor(void *arg) {
	int no;
	no=*(int*)arg;
	pthread_detach(pthread_self());
	while(1) {
		pthread_mutex_lock(&cntr_mutex);
		if (protVariable > 0) {
			protVariable--;
			printf("Consumer[%d]:eat %d\n", no,protVariable);
		}else {
			printf("Consumer[%d]: waiting\n",no);
			pthread_cond_wait(&cntr_cond, &cntr_mutex);
		}
		pthread_mutex_unlock(&cntr_mutex);
	}
	pthread_exit(NULL);

}

#define consumers_amount 10

int
main(int argc, char **argv)
{

	pthread_t pthread;
	pthread_t consumers[consumers_amount];
	int ret;
	int i;
	int n[consumers_amount];

	/*create produceor*/
	ret=pthread_create(&pthread,NULL,producer,NULL);
	if (ret!=0) {
		perror("pthread_create");
	}
	/*create consumers*/
	for(i=0;i<consumers_amount;i++) {
		n[i]=i;
		pthread_create(&consumers[i],NULL, consumor, &n[i]);
		if (ret!=0) {
			perror("pthread_create");
		}
	}	
	/*wait for produceor*/
	ret=pthread_join(pthread,NULL);

	printf("protVariable:%ld",protVariable);
	while(protVariable>0);


	for(i=0;i<consumers_amount;i++) {
		pthread_cancel(consumers[i]);
	}	

	return 0;
}
