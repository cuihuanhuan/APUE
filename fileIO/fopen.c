#include <stdio.h>
#include <string.h>
#include <errno.h>
#include <stdlib.h>

int
main(int argc, char **argv)
{
	FILE *file;
	FILE *file2;
	int ret;
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
	while((ret=fgetc(file))!= EOF) {
		fputc(ret, file2);
	}
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
