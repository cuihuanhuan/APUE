#include <stdio.h>
#include <sys/types.h>
#include <dirent.h>
#include <string.h>
#include <stdlib.h>
       #include <sys/types.h>
       #include <sys/stat.h>
       #include <unistd.h>






int
main(int argc, char **argv)
{	
	DIR *p;
	struct dirent *dir=NULL;
	struct stat buf;
	char path[256]={0};
	int ret;

	if (argc < 2) {
		fprintf(stderr, "too few arguments");
		exit(0);
	}
	p=opendir(argv[1]);
	while((dir=readdir(p))!=NULL) {
		strcat(path,dir->d_name);
		ret=stat(path,&buf);
		if (ret == -1) {
			perror("stat");
		}
		printf("%ld\t%s\n",buf.st_size,dir->d_name);
		path[0]='\0';
		if (!strcmp(dir->d_name,"file8")) {
			remove(dir->d_name);	
		}
	}
	closedir(p);
	
	return 0;
}
