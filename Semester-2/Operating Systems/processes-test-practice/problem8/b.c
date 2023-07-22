#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include "common.h"

int main(int argc, char** argv){
        int a2b, b2a;
        a2b = open(myfifo1, O_RDONLY);
        b2a = open(myfifo2, O_WRONLY);
	int length = 0;
	char* current_command;
	if(a2b<0){
		perror("error opening a2b");
		exit(1);
	}
	if(b2a<0){
		perror("error opening b2a");
		exit(1);
	}
        while(1){
		if (read(a2b, &length, sizeof(int)) < 0){
			perror("invalid lenght\n");
		}
		if(length == -1){
			break;
		}
		current_command = malloc(sizeof(char)*(length+1));
		read_from_fd(a2b, current_command, length);
		for(int i=0;i<length;i++){
			if(current_command[i] <= 'z' && current_command[i] >= 'a'){
				current_command[i] += 'A' - 'a';
			}
		}
		current_command[length] = 0;
		write_to_fd(b2a, current_command);
		printf("%s",current_command);
		free(current_command);	
	}
        close(a2b);
        close(b2a);
}
  
