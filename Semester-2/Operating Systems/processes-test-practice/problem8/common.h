#pragma once
#include <stdio.h>
#include <string.h>

char* myfifo1 = "./myfifo1";
char* myfifo2 = "./myfifo2";

void write_to_fd(int fd, char* buffer){
	int n = strlen(buffer);
	if(write(fd, &n, sizeof(int)) < 0){
		perror("invalid write of length\n");
	}else{
		if(write(fd, buffer, sizeof(char)*n) < 0){
			perror("invalid write of buffer\n");
		}
	}
}

void read_from_fd(int fd, char* buffer, int size){
	int read_bytes = 0;
	while(read_bytes< size) {
		int k;
		k = read(fd, buffer + read_bytes, sizeof(char)*(size-read_bytes));
		if (k<0){
			perror("invalid read of buffer\n");
			break;
		}else{
			read_bytes += k;
		}
	}
}
