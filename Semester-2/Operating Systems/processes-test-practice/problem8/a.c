#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h> 
#include "common.h"
#include <string.h>

int main(int argc, char** argv){
	int a2b, b2a;
	if(mkfifo(myfifo1, 0600) < 0){
		perror("error myfifo1\n");
		exit(1);
	}
	if(mkfifo(myfifo2, 0600)<0){
		perror("error myfifo1\n");
		exit(1);
	}
	a2b = open(myfifo1, O_WRONLY);
	b2a = open(myfifo2, O_RDONLY);
	if(a2b<0 || b2a<0){
		perror("error opening fifos\n");
		exit(1);
	}
	int total_size = 0;
	for(int i=1;i<argc;i++){
		write_to_fd(a2b, argv[i]);
		//printf(argv[i]);
		total_size += strlen(argv[i]);
	}
	int stopArg = -1;
	write(a2b, &stopArg, sizeof(int));
	int cl;
	int total = 0;
	char * concatenated;
	concatenated = malloc(total_size + 1);
	for(int i=1;i<argc;i++){
		read(b2a, &cl, sizeof(int));
		read_from_fd(b2a, concatenated + total, cl);
		total+= cl;
	}
	concatenated[total] = 0;
	printf(concatenated);
	close(a2b);
	close(b2a);
	unlink(myfifo1);
	unlink(myfifo2);
}
