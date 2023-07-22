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
	a2b = open(myfifo1, O_RDONLY);
	b2a = open(myfifo2, O_WRONLY);
	srandom(getpid());
	int number;
	while(1){
		number = random() % 10 + 1;
		if(write(b2a, &number, sizeof(int)) < 0){
			perror("invalid write in process b\n");
		}else if(number == 10){
			break;
		}
		if(read(a2b, &number, sizeof(int)) < 0){
			perror("invalid read in process b\n");
		}else if(number == 10){
			printf("b received 10");
			break;
		}
		printf("b read: %d", number);

	}
	close(a2b);
	close(b2a);
	exit(0);
}
