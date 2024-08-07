#include<stdio.h>
#include<pthread.h>
#include<semaphore.h>
sem_t sem;
void* threadfunc(void* arg){
	sem_wait(&sem);
	printf("thread %d is in critical position\n",((int*)arg));
	sem_post(&sem);
	return NULL;
}
int main(){
	pthread_t threads[3];
	int ids[3]={1,2,3};
	for(int i=0;i<3;i++)
		pthread_create(&thread[i], NULL,threadfunc,&ids[i]);
	for(int i=0;i<3;i++)
		pthread_join(&thread[i],NULL);
	sem_destroy(&sem);
	return 0;
}
