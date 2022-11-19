#include <stdio.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <sys/types.h>
#include <semaphore.h>

int main()
{
	int id1 = shmget(123, sizeof(sem_t), 0666 | IPC_CREAT);
	int id2 = shmget(124, 100, 0666 | IPC_CREAT);
	
	if(id1 == -1 || id2 == -1)
	{
		printf("Creating segment failed!\n");
		return 1;
	}

	sem_t *sem = (sem_t*) shmat(id1, NULL, 0);
	char* addr = (char*) shmat(id2, NULL, 0);

	if(addr == (void*) -1 || sem == (void*) -1)
	{
		printf("Attaching to segment Failed!\n");
		return 1;
	}

	printf("Attached To : %p\n", addr);
	printf("Semaphore at : %p\n", sem);
	
	while(1)
	{
		sem_wait(sem);
		printf("Segment Contents : %s", addr);
	}


	if(sem_destroy(sem) != 0)
	{
		printf("Error initialization of semaphore..\n");
		return 0;
	}

	shmdt(addr);
	shmdt(sem);
	
	return 0;
}

