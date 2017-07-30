#include <stdio.h>
#include <pthread.h>

#define MAX_OBJECT 100000

struct object {
	pthread_mutex_t lock;
	long long data;
};
struct object A = {
	.lock = PTHREAD_MUTEX_INITIALIZER,
	.data = 0,
};

void *consumer_fun(void *arg)
{
	while(1) {
		pthread_mutex_lock(&A.lock);
		if (A.data > 0) {
			A.data--;
		}
		pthread_mutex_unlock(&A.lock);
		printf("Consumer: %d\n",A.data);
	}
}

void *produceor_fun(void *arg)
{
	int i = 0;
	while(i++<MAX_OBJECT) {
		pthread_mutex_lock(&A.lock);
		A.data++;
		pthread_mutex_unlock(&A.lock);
		printf("Produceor: %d\n",i);
	}	
	pthread_exit(0);
}
int
main(int argc, char **argv)
{
	pthread_t produceor;
	pthread_t consumer[10];
	int i;
	pthread_create(&produceor,NULL,produceor_fun,NULL);
	for(i=0;i<10;i++) {
		pthread_create(&consumer[i],NULL, consumer_fun, NULL);
	}

	/*--------所有的线程都开始工作---------------------*/

	pthread_join(produceor, NULL);

	/*busy wait*/
	while(A.data>0);

	for(i=0;i<10;i++) {
		pthread_cancel(consumer[i]);
	}
	for(i=0;i<10;i++) {
		pthread_join(consumer[i], NULL);
	}

	printf("A.data=%d\n",A.data);

	return 0;
}
