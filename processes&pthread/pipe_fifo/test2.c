#include <stdio.h>

int
main(int argc, char **argv)
{
	char buf[20];
	snprintf(buf,20,"Hello,%d",50);










	printf("%s\n",buf);
	return 0;
}
