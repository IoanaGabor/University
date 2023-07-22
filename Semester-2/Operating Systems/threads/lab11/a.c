#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

int sum = 0;
pthread_mutex_t mtx;
pthread_barrier_t bar;

typedef struct{
	int *a;
	int start, end;
	int index;
} data;

void* f(void *arg){
	data d = *(data*)arg;
	int s = 0;
	for (int i=d.start; i< d.end; i ++ ){
		s+= d.a[i];
	}
	printf("Thread nr %d waits\n",d.index);
	pthread_barrier_wait(&bar);
	printf("Thread nr %d no longer waits\n",d.index);
//	pthread_mutex_lock(&mtx);
	sum += s;
//	pthread_mutex_unlock(&mtx);

//	printf("Thread nr %d, with partial sum %d \n", d.index, s);
	return NULL;
}

int main(){
	int p = 10;
	int n = 20;
	int a[n];
		
	for(int i=0;i<n;i++){
		a[i] = i;
	}

	pthread_t th[p];
	data th_d[p];
	pthread_barrier_init(&bar, NULL, p);
	pthread_mutex_init(&mtx, NULL);

	for(int i=0;i<p;i++){
		th_d[i].a = a;
		th_d[i].start = (n/p)*i;
		th_d[i].end = (n/p)*(i+1);
		th_d[i].index = i;
		pthread_create(&th[i], NULL, f, (void*)&th_d[i]);
	}

	for(int i=0;i<p;i++){
		pthread_join(th[i], NULL);
	}
	pthread_mutex_destroy(&mtx);
	printf("The total sum is %d\n", sum);

	return 0;
}
