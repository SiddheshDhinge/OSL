#include <stdio.h>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>

#define randdelay 7
#define p 5

sem_t lock[p];

void philosopherFunction(int id)
{
	while(1)
	{
		printf("PHILOSOPHER %d: Hungry.\n", id);
		
		if(id % 2==0)
		{
			sem_wait(&lock[(id+1) % p]);
			sem_wait(&lock[id]);
		}
		else
		{
			sem_wait(&lock[id]);
			sem_wait(&lock[(id+1) % p]);
		}
		
		printf("PHILOSOPHER %d: Eating.\n", id);
		
		sem_post(&lock[(id+1) % p]);
		sem_post(&lock[id]);
		
		printf("PHILOSOPHER %d: Thinking\n", id);
		sleep(rand() % randdelay);
	}
}

int main()
{
    pthread_t philosopher[p];
    
    for(int i=0;i<p;i++)
    {
    	int res = sem_init(&lock[i], 0, 1);
    	if(res!=0)
    	{
    		perror("Semaphore Initialization Failed.\n");
    		return -1;
    	}
    }
    
    for(int i=0;i<p;i++)
    {
    	int res = pthread_create(&philosopher[i], NULL, (void *)philosopherFunction, i);
    	if(res!=0)
    	{
    		perror("Thread Creation Failed.\n");
    		return -1;
    	}
    }
    
    
    for(int i=0;i<p;i++)
    {
    	int res = pthread_join(philosopher[i], NULL);
    	if(res!=0)
    	{
    		perror("Thread Joining Failed.\n");
    		return -1;
    	}
    }
    
    return 0;
}
