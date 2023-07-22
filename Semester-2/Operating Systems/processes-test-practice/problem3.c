#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

int main(int argc, char** argv){
	int n = atoi(argv[1]);
	int* numbers;
	numbers = malloc(sizeof(int)*n);
	int ptoch[2], chtop[2];
	pipe(ptoch);
	pipe(chtop);
	int status = fork();
	if(status<0){
		printf("error at fork");
		exit(1);
	}else if(status == 0){
		close(ptoch[1]);
		close(chtop[0]);
		if(read(ptoch[0],&n, sizeof(int)) <= 0){
			printf("error at read");
			free(numbers);
			exit(1);
		}
		int sum = 0;
		for(int i=0;i<n;i++){
			if(read(ptoch[0],&numbers[i], sizeof(int)) <= 0){
				close(ptoch[0]);
				printf("error at read!");
				free(numbers);
				exit(1);
			}
			printf("%d ", numbers[i]);
			sum += numbers[i];
		}
		int average = sum / n;
		write(chtop[1], &average, sizeof(int));
		close(chtop[1]);
		close(ptoch[0]);
		free(numbers);
		exit(0);
	}else{
		close(ptoch[0]);
		close(chtop[1]);
		for(int i=0;i<n;i++){
			numbers[i] = rand() % 30;
		}
		write(ptoch[1], &n, sizeof(int));
		for(int i=0;i<n;i++){
			write(ptoch[1], &numbers[i], sizeof(int));
		}
		int average;
		if(read(chtop[0],&average, sizeof(int)) <= 0){
			printf("error at read");
			exit(1);
		}
		printf("average %d", average);
		close(chtop[0]);
		close(ptoch[1]);
	}
	free(numbers);
	wait(0);
}
