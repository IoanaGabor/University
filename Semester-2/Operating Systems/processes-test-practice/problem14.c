#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/wait.h>
#include <stdlib.h>
#include <math.h>

int main(int argc, char** argv){
	int pipe_a_to_b[2], pipe_b_to_a[2];
	if(pipe(pipe_a_to_b) < 0){
		perror("pipe failed\n");
	}
	if(pipe(pipe_b_to_a) < 0){
                perror("pipe failed\n");
        }

	int status = fork();
	if(status < 0){
		perror("error at fork\n");
		close(pipe_a_to_b[0]);
		close(pipe_a_to_b[1]);
		close(pipe_b_to_a[0]);
		close(pipe_b_to_a[1]);
		exit(1);
	}else if(status == 0){
		close(pipe_a_to_b[1]);
		close(pipe_b_to_a[0]);
		srandom(getpid());
		int number = random()%901 + 100;
		printf("process B has generated %d\n", number);
		int read_number;
		int ok = 0;
		while(!ok){
			if(read(pipe_a_to_b[0],&read_number, sizeof(int)) < 0){
				perror("read from parent failed\n");		
			}
			printf("B received %d; difference: %d\n", read_number, abs(read_number-number));
			if(abs(read_number- number) < 50){
				ok = 1;
			}
			if(write(pipe_b_to_a[1], &ok, sizeof(int))<0){
				perror("write to parent failed\n");
			}
		}
		close(pipe_b_to_a[1]);
		close(pipe_a_to_b[0]);
		exit(0);
	}else{
		close(pipe_a_to_b[0]);
		close(pipe_b_to_a[1]);
		int ok = 0;
		int generated_number;
		int count = 0;
		srandom(getpid());
		while(!ok){
			generated_number = random()%1001 + 50;
			if(write(pipe_a_to_b[1], &generated_number, sizeof(int))<0){
				perror("write to child failed\n");
			}
			if(read(pipe_b_to_a[0],&ok, sizeof(int)) < 0){
                                perror("read from child failed\n");            
                        }
			count++;
		}
		printf("Process A has generated %d numbers\n", count);
		close(pipe_a_to_b[1]);
		close(pipe_b_to_a[0]);
	}
	wait(0);
	exit(0);
}
