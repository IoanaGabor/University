#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

int n;
int **matrix;
int *sums;

void* compute_sum(void *args){

	int index =*(int*)args;
	printf("Thread with index %d starts\n", index);	
	for(int i=0;i<n;i++){
		sums[index] += matrix[index][i];
	}
	printf("Thread with index %d ends\n", index);	
	return 0;
}

int main(int argc, char** argv){
	FILE* fd = fopen("text.in", "r");
	fscanf(fd, "%d", &n);
	matrix = malloc(sizeof(int*)*n);
	sums = malloc(sizeof(int)*n);
	for(int i=0;i<n;i++){
		matrix[i] = malloc(sizeof(int)*n);
		sums[i] = 0;
		for(int j=0;j<n;j++){
			fscanf(fd, "%d", &matrix[i][j]);
		}
	}
	pthread_t *th;
	th = malloc(sizeof(pthread_t)*n);
	int *args = malloc(sizeof(int*)*n);
	for(int i=0;i<n;i++){
		args[i] = i;
		pthread_create(&th[i], NULL, compute_sum, (void*)&args[i]);		
	}

	for(int i=0;i<n;i++){
		pthread_join(th[i], NULL);
	}
	for(int i=0;i<n;i++){
		printf("row %d sum %d\n", i, sums[i]);
		free(matrix[i]);
	}
	fclose(fd);
	free(args);
	free(matrix);
	free(sums);
	free(th);
}
