#include <stdio.h>
#include <pthread.h>
#include "queue.h"
#include <semaphore.h>
#include <stdlib.h>
#include <unistd.h>

sem_t mutex, full, empty;
void consumer()
{
	while(1)
	{
		sem_wait(&full);
		sem_wait(&mutex);
		
		printf("CONSUMER : %d\n", removeElement());
		
		sem_post(&empty);
		sem_post(&mutex);
		sleep(rand() % 5);
	}
}
void producer()
{
	while(1)
	{
		sem_wait(&empty);
		sem_wait(&mutex);
		
		int x = rand() % 10;
		printf("PRODUCER : %d\n", x);
		insertElement(x);
		
		sem_post(&full);
		sem_post(&mutex);
		
		sleep(rand() % 10);
	}
}
int main()
{
	pthread_t producerThread, consumerThread;
	
	sem_init(&mutex, 0, 1);
	sem_init(&full, 0, 0);
	sem_init(&empty, 0, 5);
	
	pthread_create(&producerThread, NULL, (void *) producer, NULL);
	pthread_create(&producerThread, NULL, (void *) consumer, NULL);
	
	pthread_join(producerThread, NULL);
	pthread_join(producerThread, NULL);
	
	sem_destroy(&mutex);
	sem_destroy(&full);
	sem_destroy(&empty);
	
	return 0;	
}
