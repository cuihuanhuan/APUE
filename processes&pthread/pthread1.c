#include <stdio.h>
#include <pthread.h>

int sum=0;

void *mythread(void *arg)
{
	while(sum++<1000);
	return 0;
}
int
main(int argc, char **argv)
{
	pthread_t thread[20];
	int i;
	for(i=0;i<20;i++) {
		pthread_create(&thread[i],NULL,mythread,NULL);
	}
	printf("I'm main thread1\n");
	for(i=0;i<20;i++) {
		pthread_join(thread[i], NULL);
	}
	printf("I'm main thread2\n");
	printf("sum=%d\n",sum);
	return 0;
}
