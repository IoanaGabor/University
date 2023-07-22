#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>

int n;
int m;
pthread_mutex_t *mtx;
pthread_barrier_t bar;

void* f(void* arg){
	int id = *(int*)arg;
	printf("thread %d waits\n", id);
	pthread_barrier_wait(&bar);
	printf("thread %d no longer waits\n", id);
	for(int i=0;i<m;i++){
		pthread_mutex_lock(&mtx[i]);
		int nrs = random()%300 + 100;
		printf("thread %d waits at checkpoint %d for %d ms\n",id,i, nrs);
		usleep(nrs*1000);
		printf("thread %d resumes\n", id);
		pthread_mutex_unlock(&mtx[i]);
	}
	printf("thread %d finished\n", id);
}

int main(int argc, char**argv){
	n  = atoi(argv[1]);
	m  = atoi(argv[2]);	
	mtx = malloc(sizeof(pthread_mutex_t)*m);
	pthread_t *th;
	th = malloc(sizeof(pthread_t)*n);
	pthread_barrier_init(&bar, NULL, n);
	int *args = malloc(sizeof(int)*n);
	for(int i=0;i<n;i++){
		args[i] = i;
		pthread_create(&th[i], NULL,f, (void*)&args[i]);
	}
	
	for(int i=0;i<n;i++){
		pthread_join(th[i],NULL);
	}

	free(th);
	free(mtx);
}
