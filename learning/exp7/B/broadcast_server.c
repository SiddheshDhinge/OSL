#include <stdio.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <sys/types.h>
#include <semaphore.h>
#include <unistd.h>
#include <string.h>
#define clients 3

struct semStruct
{
	sem_t semArr[clients];
};

int main()
{
	int fpid = fork();

	if(fpid != 0)
	{
		// writer
		int id1 = shmget(1000, sizeof(struct semStruct), 0666 | IPC_CREAT);
		int id2 = shmget(1001, 100, 0666 | IPC_CREAT);
	
		if(id1 == -1 || id2 == -1)
		{
			printf("Creating segment failed!\n");
			return 0;
		}

		struct semStruct *sem = (struct semStruct*) shmat(id1, NULL, 0);
		char* addr = (char*) shmat(id2, NULL, 0);

		if(addr == (void*) -1 || sem == (void*) -1)
		{
			printf("Attaching to segment Failed!\n");
			return 0;
		}

		printf("Attached To : %p\n", addr);
		printf("Semaphore at : %p\n", sem);
	
		for(int i=0;i<clients;i++)
		{
			if(sem_init(&sem->semArr[i], 1, 0) != 0)
			{
				printf("Error initialization of semaphore..\n");
				return 0;
			}
		}
		
		printf("Enter Message : ");
		while(1)
		{
			char s[100];
			fgets(addr, 100, stdin);
			strcpy(s, addr);
			
			s[strcspn(s, "\n")] = '\0';
				
			for(int i=0;i<clients;i++)
			{
				sem_post(&sem->semArr[i]);
			}
			
			if(strcmp(s, "e") == 0)
				break;
		}
		
		printf("Server : Writer Shutting down ...\n");
		for(int i=0;i<clients;i++)
		{
			if(sem_destroy(&sem->semArr[i]) != 0)
			{
				printf("Error Destroying semaphore..\n");
				return 0;
			}
		}

		if(shmdt(addr) == -1 || shmdt(sem) == -1)
		{
			printf("Error in Detaching Segment.\n");
		}
		
		if(shmctl(id1, IPC_RMID, NULL) == -1 || shmctl(id2, IPC_RMID, NULL) == -1)
		{
			printf("Error in removing segment.\n");
		}
	}
	else
	{
		// reader
		int id1 = shmget(2000, sizeof(sem_t), 0666 | IPC_CREAT);
		int id2 = shmget(2001, 100, 0666 | IPC_CREAT);
	
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

			char s[100];
			strcpy(s, addr);
			
			if(strcmp(s, "e") == 0)
				break;

			printf("Client %s", addr);
		}
		printf("Server : Reader Shutting Down...[Client Down]\n");

		if(sem_destroy(sem) != 0)
		{
			printf("Error Destroying semaphore..\n");
			return 0;
		}
		
		if(shmdt(addr) == -1 || shmdt(sem) == -1)
		{
			printf("Error in Detaching Segment.\n");
		}
		
		if(shmctl(id1, IPC_RMID, NULL) == -1 || shmctl(id2, IPC_RMID, NULL) == -1)
		{
			printf("Error in removing segment.\n");
		}
	}
	return 0;
}

