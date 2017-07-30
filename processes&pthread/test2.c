#include <stdio.h>
int w;
int w1;
int w2;
int
main(int argc, char **argv)
{
	while(1) {
		if(w==0) {
			printf("W=%d,address:%p\n",w,&w);
		}
		sleep(1);
	}
	return 0;
}
