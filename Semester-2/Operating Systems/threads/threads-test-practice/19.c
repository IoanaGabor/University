#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

int n,m;
int *a;
typedef struct{
	int id;
	int l, r;
	int sum;
} arguments;

void* f(void *ar){
	arguments args = *(arguments*) ar;
	printf("thread %d with l=%d and r=%d starts\n", args.id, args.l, args.r);
	if(args.id>=m/2){
		((arguments*)ar)->sum = a[args.l]+a[args.r];
	}else{
		pthread_t th1, th2;
		arguments args1, args2;
		args1.id = args.id*2;
		args1.l = args.l;
		args1.r = (args.l + args.r)/2;
		args2.id = args.id*2+1;
		args2.r = args.r;
		args2.l = (args.l + args.r)/2+1;
		args1.sum = args2.sum = 0;
		pthread_create(&th1, NULL, f, (void*)&args1);
		pthread_create(&th2, NULL, f, (void*)&args2);

		pthread_join(th1, NULL);
		pthread_join(th2, NULL);
		((arguments*)ar)->sum = args1.sum+args2.sum;
	}
	printf("thread %d ends\n", args.id);
	return 0;
}

int main(int argc, char**argv){
	n = atoi(argv[1]);
	m=1;
	while(m<n){
		m*=2;
	}
	a = malloc(sizeof(int)*m);
	for(int i=0;i<n;i++){
		scanf("%d",&a[i]);
	}
	for(int i=n;i<m;i++){
		a[i] = 0;
	}

	arguments args;
	args.id = 1;
	args.l=0, args.r = m-1;
	args.sum = 0;
	pthread_t firstTh;
	pthread_create(&firstTh, NULL, f, (void*)&args);
	pthread_join(firstTh, NULL);
	printf("the sum is %d", args.sum);
	free(a);
}
