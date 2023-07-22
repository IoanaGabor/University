#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>
typedef struct{
	char *word;
	int *td;
	int *tl;
	int *tc;
	pthread_mutex_t *mtx;
} arguments;

void* f(void* arg){
	arguments args = *(arguments*) arg;
	int locald=0, locall=0, localc=0;
	for(int i=0;args.word[i];i++){
		if(args.word[i] <= 'z' && 'a' <= args.word[i]){
			locall++;
		}else if(args.word[i] <= '9' && '0' <= args.word[i]){
			locald++;
		}else{
			localc++;
		}
	}
	pthread_mutex_lock(&args.mtx[0]);
	(*args.tl) += locall;	
	pthread_mutex_unlock(&args.mtx[0]);
	pthread_mutex_lock(&args.mtx[1]);
	(*args.td) += locald;
	pthread_mutex_unlock(&args.mtx[1]);
	pthread_mutex_lock(&args.mtx[2]);
	(*args.tc) += localc;
	pthread_mutex_unlock(&args.mtx[2]);
	return 0;
}

int main(int argc, char**argv){
	pthread_t *th = malloc((argc-1)*sizeof(pthread_t));
	arguments *args = malloc((argc-1)*sizeof(arguments));
	int totald;
	int totall;
       int totalc;
//	totald = malloc(sizeof(int));
//	totall = malloc(sizeof(int));
//	totalc = malloc(sizeof(int));
	totald = 0;
	totall = 0;
	totalc = 0;
	printf("%d", argc);
	pthread_mutex_t *mutexes = malloc(3*sizeof(pthread_mutex_t));
	pthread_mutex_init(&mutexes[0], NULL);
	pthread_mutex_init(&mutexes[1], NULL);	
	pthread_mutex_init(&mutexes[2], NULL);
	for(int i=0;i<argc-1;i++){
		args[i].word = argv[i+1];
		args[i].td = &totald;
		args[i].tl = &totall;
		args[i].tc = &totalc;
		args[i].mtx = mutexes;
		pthread_create(&th[i], NULL, f, (void*)&args[i]);
	}
	for(int i=0;i<argc-1;i++){
		pthread_join(th[i], NULL);
	}
	printf("Total letters %d", totall);
	printf("Total digits %d", totald);
	printf("Total sp char  %d", totalc);
	pthread_mutex_destroy(&mutexes[0]);
	pthread_mutex_destroy(&mutexes[1]);
	pthread_mutex_destroy(&mutexes[2]);
//	free(totald);
//	free(totall);
//	free(totalc);
	free(args);
	free(th);
	free(mutexes);
}
