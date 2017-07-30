#include <stdio.h>
int a;
int
main(int argc, char **argv)
{
	scanf("%d",&a);
	printf("a=%d\t the address:%p\n",a,&a);
	while(a){
		printf("a=%d\t the address:%p\n",a,&a);
		if (a>=10) {
			a--;
			sleep(1);
		}
		if (a<10) {
			a++;
			sleep(1);
		}
	}
	return 0;
}
