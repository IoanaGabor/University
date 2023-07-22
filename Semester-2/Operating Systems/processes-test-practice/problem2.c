#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

void solve(int n){
	if(n>0){
		int status = fork();
		if(status<0){
			printf("error on fork");
		}else if(status == 0){
			printf("process with id %d and parent id %d\n", getpid(), getppid());
			solve(n-1);
		}	
	}
	wait(0);
	exit(0);
		
}

int main(int argc, char** argv){
	int n;
	printf("Enter the desired number of processes to be created\n");
	scanf("%d", &n);
	solve(n);
}
