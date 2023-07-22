#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <fcntl.h>
#include "common.h"

int main(int argc, char** argv){
	int a2b, b2a;
	mkfifo(myfifo1, 0600);
	mkfifo(myfifo2, 0600);
	a2b = open(myfifo1, O_WRONLY);
	b2a = open(myfifo2, O_RDONLY);
	srandom(getpid());
	int number = random() % 10 + 1;
	if(read(a2b, &number, sizeof(int)) < 0){
		perror("invalid read in process a\n");
	}
	printf("a read: %d", number);
	while(1){
		number = random() % 10 + 1;
		if(write(a2b, &number, sizeof(int)) < 0){
			perror("invalid write in process a\n");
		}else if(number == 10){
			break;
		}
		if(read(b2a, &number, sizeof(int)) < 0){
			perror("invalid read in process a\n");
		}else if(number == 10){
			printf("received 10");
			break;
		}
		printf("a read: %d", number);

	}
	close(a2b);
	close(b2a);
	unlink(myfifo1);
	unlink(myfifo2);
	exit(0);
}
