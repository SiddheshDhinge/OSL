#include <stdio.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <sys/types.h>
#include <semaphore.h>
#include <unistd.h>
#include <string.h>

int main()
{
	int fpid = fork();

	if(fpid == 0)
	{
		// writer
		int id1 = shmget(100, sizeof(sem_t), 0666 | IPC_CREAT);
		int id2 = shmget(101, 100, 0666 | IPC_CREAT);
	
		if(id1 == -1 || id2 == -1)
		{
			printf("Creating segment failed!\n");
			return 0;
		}

		sem_t *sem = (sem_t*) shmat(id1, NULL, 0);
		char* addr = (char*) shmat(id2, NULL, 0);

		if(addr == (void*) -1 || sem == (void*) -1)
		{
			printf("Attaching to segment Failed!\n");
			return 0;
		}

		printf("Attached To : %p\n", addr);
		printf("Semaphore at : %p\n", sem);
	
		if(sem_init(sem, 1, 0) != 0)
		{
			printf("Error initialization of semaphore..\n");
			return 0;
		}

		printf("Enter Message : ");
		while(1)
		{
			fgets(addr, 100, stdin);
			sem_post(sem);
		}


		if(sem_destroy(sem) != 0)
		{
			printf("Error initialization of semaphore..\n");
			return 0;
		}

		shmdt(addr);
		shmdt(sem);
		
		shmctl(id1, IPC_RMID, NULL);
		shmctl(id2, IPC_RMID, NULL);

	}
	else
	{
		// reader
		int id1 = shmget(200, sizeof(sem_t), 0666 | IPC_CREAT);
		int id2 = shmget(201, 100, 0666 | IPC_CREAT);
	
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

		if(sem_init(sem, 1, 0) != 0)
		{
			printf("Error initialization of semaphore..\n");
			return 0;
		}

		while(1)
		{
			sem_wait(sem);
			printf("Client : %s", addr);
		}


		if(sem_destroy(sem) != 0)
		{
			printf("Error initialization of semaphore..\n");
			return 0;
		}

		shmdt(addr);
		shmdt(sem);
	
	}
	return 0;
}

