#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>

pthread_rwlock_t lck;

void* r1(void* a) {
	sleep(2);
	printf("r1 waiting\n");
	pthread_rwlock_rdlock(&lck);
	printf("r1...\n");
	sleep(1);
	printf("r1 unlocks\n");
	pthread_rwlock_unlock(&lck);

	return NULL;
}

void* r2(void* a) {
	sleep(2);
	printf("r2 waiting\n");
	pthread_rwlock_rdlock(&lck);
	printf("r2...\n");
	sleep(1);
	printf("r2 unlocks\n");
	pthread_rwlock_unlock(&lck);

	return NULL;
}

void* w1(void* a) {
	sleep(2);
	printf("w1 waiting\n");

	pthread_rwlock_wrlock(&lck);
	printf("w1...\n");
	sleep(1);
	printf("w1 unlocks\n");
	pthread_rwlock_unlock(&lck);

	return NULL;
}

void* w2(void* a) {
	sleep(2);
	printf("w2 waiting\n");

	pthread_rwlock_wrlock(&lck);
	printf("w2...\n");
	sleep(1);
	printf("w2 unlocks\n");
	pthread_rwlock_unlock(&lck);

	return NULL;
}

int main(){
	pthread_rwlock_init(&lck, NULL);

	pthread_t t1, t2, t3, t4;
	pthread_create(&t1, NULL, r1, NULL);
	pthread_create(&t2, NULL, r2, NULL);
	pthread_create(&t3, NULL, w1, NULL);
	pthread_create(&t4, NULL, w2, NULL);

	pthread_join(t1, NULL);
	pthread_join(t2, NULL);
	pthread_join(t3, NULL);
	pthread_join(t4, NULL);
}
