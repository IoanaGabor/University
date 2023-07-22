#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

int main(int argc, char** argv){
	int a2b[2], b2c[2], c2a[2];
	if(pipe(a2b) < 0){
		perror("failed creating \n");
	}
	if(pipe(b2c) < 0){
		perror("failed creating \n");
	}
	if(pipe(c2a) < 0){
		perror("failed creating \n");
	}

	int status = fork();
	if(status<0){ // A
		perror("failed fork\n");
	}else if(status == 0){
		close(b2c[0]);
		close(b2c[1]);
		close(a2b[0]);
		close(c2a[1]);
		int n;
		scanf("%d", &n);
		write(a2b[1], &n, sizeof(int));
		int number;
		while(n--){
			scanf("%d", &number);		
			write(a2b[1], &number, sizeof(int));
			printf("a sent %d\n", number);
		}
		int sum = 0;
		read(c2a[0], &sum, sizeof(int));
		printf("a received  %d\n", sum);
		close(a2b[1]);
		close(c2a[0]);
		exit(0);
	}
	status = fork();
	if(status<0){ // B
		perror("failed fork\n");
	}else if(status == 0){
		close(b2c[0]);
		close(c2a[0]);
		close(a2b[1]);
		close(c2a[1]);
		int n, number;
		read(a2b[0], &n, sizeof(int));
		printf("b received %d\n", n);
		write(b2c[1], &n, sizeof(int));
		printf("b sent %d\n", n);
		while(n--){
			read(a2b[0], &number, sizeof(int));
			printf("b received  %d\n", number);
			number += random() % 4 + 2;
			write(b2c[1], &number, sizeof(int));
			printf("b sent  %d\n", number);
		}
		close(a2b[0]);
		close(b2c[1]);
	
		exit(0);
	}
	status = fork();
	if(status<0){ // C
		perror("failed fork\n");
	}else if(status == 0){
		close(a2b[0]);
		close(a2b[1]);
		close(c2a[0]);
		close(b2c[1]);
		
		int n, number;
		read(b2c[0], &n, sizeof(int));
		int sum = 0;
		while(n--){
			read(b2c[0], &number, sizeof(int));
			printf("c received  %d\n", number);
			sum += number;
		}
		
		write(c2a[1], &sum, sizeof(int));
		printf("c sent  %d\n", sum);	
		close(b2c[0]);
		close(c2a[1]);
	
		exit(0);
	}
	wait(0);
	wait(0);
	wait(0);
	exit(0);
}
