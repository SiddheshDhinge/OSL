#include <stdio.h>
#include <pthread.h>
#include <semaphore.h>
#include <stdlib.h>
#include <unistd.h>

sem_t mutex, writerSem;
int readerCount = 0;
int catalog = 50;

void reader()
{
	while(1)
	{
		sem_wait(&mutex);
		readerCount++;
		if(readerCount == 1)
			sem_wait(&writerSem);
		sem_post(&mutex);
	
		printf("READER : Catalog is - %d\n", catalog);
	
		sem_wait(&mutex);
		readerCount--;
		if(readerCount == 0)
			sem_post(&writerSem);
		sem_post(&mutex);

		printf("READER : Going busy\n");
		sleep(rand() % 5);
	}
}

void writer()
{
	while(1)
	{
		sem_wait(&writerSem);
	
		int x = rand() % 100;
		printf("WRITER : new catalog - %d\n", x);
		catalog = x;
		
		sem_post(&writerSem);
		
		printf("WRITER : Going busy\n");
		sleep(rand() % 5);
	}
}

int main()
{
	sem_init(&mutex, 0, 1);
	sem_init(&writerSem, 0, 1);
	
	int n = 3;
	pthread_t readers[n];
	pthread_t writers[n];
	
	for(int i=0;i<n;i++)
	{
		pthread_create(&readers[i], NULL, (void*)reader, NULL);
		pthread_create(&writers[i], NULL, (void*)writer, NULL);
	}
	printf("Threads started.\n");
	
	for(int i=0;i<n;i++)
	{
		pthread_join(readers[i], NULL);
		pthread_join(writers[i], NULL);
	}
	
	sem_destroy(&mutex);
	sem_destroy(&writerSem);
	
	return 0;
}

