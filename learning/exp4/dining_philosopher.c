#include <semaphore.h>
#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>
#include <unistd.h>

#define n 5
sem_t chopsticks[n];

void philosopher(int *idptr)
{
	while(1)
	{
		int id = *idptr;
		printf("PHILOSOPHER [%d] : Hungry.\n", id);
				
		if(id%2==0)
		{
			sem_wait(&chopsticks[id]);
			sem_wait(&chopsticks[(id +1) %n]);
		}
		else
		{		
			sem_wait(&chopsticks[(id +1) %n]);
			sem_wait(&chopsticks[id]);
		}
		
		printf("PHILOSOPHER [%d] : Eating.\n", id);
		
		sleep(1);
		
		sem_post(&chopsticks[(id +1)%n]);
		sem_post(&chopsticks[id]);
		
		printf("PHILOSOPHER [%d] : Thinking.\n", id);
		
		sleep(rand() % 7);
	}
}

int main()
{
	for(int i=0;i<n;i++)
	{
		sem_init(&chopsticks[i], 0, 1);
	}
	
	pthread_t philospherThreads[n];
	
	for(int i=0;i<n;i++)
	{
		int *id = (int *)malloc(sizeof(int));
		*id = i;
		pthread_create(&philospherThreads[i], NULL, (void *) philosopher, (void *)id);
	}
	
	
	for(int i=0;i<n;i++)
	{
		pthread_join(philospherThreads[i], NULL);
	}
	
	for(int i=0;i<n;i++)
	{
		sem_destroy(&chopsticks[i]);
	}
	
	return 0;
}
