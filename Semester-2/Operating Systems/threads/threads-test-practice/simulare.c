#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>

typedef struct{
	int id;
	pthread_mutex_t *mtx;
	pthread_barrier_t *barr;
} ceva;

int sum;

int compute(int a){
	if(a%2==0){
		return a;
	}
	return -a;
}

void* f(void *arg){
	ceva args = *((ceva*) arg);
	printf("thread %d waits for others\n", args.id);
	pthread_barrier_wait(args.barr);
	int a,b,c;
	a = rand()%10+1;	
	b = rand()%10+1;	
	c = rand()%10+1;
	printf("thread %d with numbers %d, %d, %d\n", args.id, a, b, c);
	pthread_mutex_lock(args.mtx);
	sum += compute(a);	
	sum += compute(b);	
	sum += compute(c);
	pthread_mutex_unlock(args.mtx);
	return 0;
}

int main(int argc, char**argv){
	int n = atoi(argv[1]);
	pthread_t *th;
	th = malloc(sizeof(pthread_t)*n);
	ceva *args;
	args = malloc(sizeof(ceva)*n);
	pthread_mutex_t mtx;
	pthread_barrier_t barr;
	pthread_mutex_init(&mtx, NULL);
	pthread_barrier_init(&barr, NULL, n);
	for(int i=0;i<n;i++){
		args[i].id = i+1;
		args[i].mtx = &mtx;
		args[i].barr = &barr;
		pthread_create(&th[i], NULL, f, (void*)&args[i]);
	}
	for(int i=0;i<n;i++){
		pthread_join(th[i], NULL);
	}
	printf("sum is %d", sum);
	free(th);
	free(args);
}
