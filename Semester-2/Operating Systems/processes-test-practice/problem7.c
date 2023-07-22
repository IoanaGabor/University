#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

int main(int argc, char** argv){
	int a_to_b[2], b_to_a[2];
	int number = 0;
	if(pipe(a_to_b)<0){
		perror("error on first pipe\n");
		exit(1);
	}
	if(pipe(b_to_a)<0){
                perror("error on second pipe\n");
		exit(1);
        }

	int status_a = fork();
	if(status_a<0){
		printf("error at creating child process a\n");
		exit(1);
	}else if(status_a == 0){
		printf("a here");
		close(a_to_b[0]);
		close(b_to_a[1]);
		srandom(getpid());
		number = random()%10+1;
		write(a_to_b[1], &number, sizeof(int));
		printf("a sent number %d\n", number);
		while(1){
		
			if(read(b_to_a[0], &number, sizeof(int))<0){
				perror("a: error on read\n");
			}else{
				printf("a receiver number %d\n", number);
				if(number == 10){
					printf("stop");
					break;
				}
			}
			number = random() %10 + 1;
			write(a_to_b[1], &number, sizeof(int));	
			printf("a sent number %d\n", number);
			if(number == 10){
				break;
			}
		}
		close(a_to_b[1]);
		close(b_to_a[0]);
		exit(0);
	}
        int status_b = fork();
        if(status_b<0){
                printf("error at creating child process a\n");
                exit(1);
        }else if(status_b == 0){
		printf("b here");
	        close(a_to_b[1]);
                close(b_to_a[0]);
		srandom(getpid());
		while(1){

                        if(read(a_to_b[0], &number, sizeof(int))<0){
                                perror("b: error on read\n");
                        }else{
                                printf("b receiver number %d\n", number);
                                if(number == 10){
                                        printf("stop\n");
                                        break;
                                }
                        }
                        number = random() %10 + 1;
                        write(b_to_a[1], &number, sizeof(int));
			printf("b sent number %d\n", number);
                        if(number == 10){
                                break;
                        }

                }

                close(a_to_b[0]);
                close(b_to_a[1]);
                exit(0);
        }
	close(a_to_b[0]);
	close(a_to_b[1]);
	close(b_to_a[0]);
	close(b_to_a[1]);
	wait(0);
	wait(0);
}
