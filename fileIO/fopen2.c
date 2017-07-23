#include <stdio.h>
#include <string.h>
#include <errno.h>
#include <stdlib.h>

int
main(int argc, char **argv)
{
	FILE *file;
	FILE *file2;
	char *c;
	int ret;
	int count;
	if (argc < 3) {
		fprintf(stderr, "too few arguments\n");
		exit(1);
	}
	printf("Hello,world\n");
	file=fopen(argv[1], "r");
	if (file == NULL) {
		fprintf(stderr, "open file: %s\n", strerror(errno));
	}
	file2=fopen(argv[2], "w");
	if (file == NULL) {
		fprintf(stderr, "open file2: %s\n", strerror(errno));
	}
#if 0
	while((ret=fgetc(file))!= EOF) {
		fputc(ret, file2);
	}
#endif
	c=(char *)malloc(4096);
	do {
		count=fread(c,1,4096,file);
		fwrite(c,1,count,file2);
		
	}while(!feof(file));

	ret=fclose(file2);
	if (ret != 0) {
		perror("fclose(file2)");
		exit(0);
	}
	ret=fclose(file);
	if (ret != 0) {
		perror("fclose(file)");
		exit(0);
	}
	return 0;
}
