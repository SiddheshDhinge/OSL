#include <stdio.h>
#include <pthread.h>
#include <stdbool.h>
#include <semaphore.h>
#include "queue.h"
#define randdelay 6
int buffer_size = 4;
sem_t full, empty, mutex;
int buf = 0;

void producerFunction()
{
	printf("PRODUCER : Started\n");
	while(true)
	{
		int x = rand() % 10;
		printf("PRODUCER : Produced Item - %d\n", x);
		sem_wait(&empty);
		sem_wait(&mutex);
		buf++;
		insert(x);
		printf("PRODUCER : Placed Item, Buffer Size - %d\n", buf);
		sem_post(&full);
		sem_post(&mutex);
		sleep(rand() % randdelay);
	}
}
void consumerFunction()
{
	printf("CONSUMER : Started\n");
	while(true)
	{
		sem_wait(&full);
		sem_wait(&mutex);
		buf--;
		int x = removeitem();
		printf("CONSUMER : Removed Item, Buffer Size - %d\n", buf);
		sem_post(&empty);
		sem_post(&mutex);
		printf("CONSUMER : Consumed Item - %d\n", x);
		sleep(rand() % randdelay);
	}
}
int main()
{
	pthread_t producer, consumer;

	int res1 = pthread_create(&producer, NULL, (void *) producerFunction, NULL);
	int res2 = pthread_create(&consumer, NULL, (void *) consumerFunction, NULL);
	int res3 = sem_init(&mutex, 0, 1);
	int res4 = sem_init(&full, 0, 0);
	int res5 = sem_init(&empty, 0, buffer_size);

	if(res1 != 0 || res2 != 0)
	{
		printf("Thread Creation Failed..\n");
		return 1;
	}
	if(res3 != 0 || res4 != 0 || res5 != 0)
	{
		printf("Semaphore Initialization Failed..\n");
		return 1;
	}

	res1 = pthread_join(producer, NULL);
	res2 = pthread_join(consumer, NULL);
	if(res1 != 0 || res2 != 0)
	{
		printf("Thread Join Failed..\n");
		return 1;
	}

	return 0;
}