#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>

int main(int argc, char** argv) {
	int n;
	printf("enter the number n");
	scanf("%d", &n);
	for(int i=0;i<n;i++){
		int pid = fork();
		if(pid==0){
			printf("PID=%d, PPID=%d\n", getpid(), getppid());
			break;
		}else{
			printf("PID=%d, ch PID=%d\n", getpid(), pid);
		}
	}
	for(int i=0;i<n;i++){
		wait(0);
	}
	return 0;
}
