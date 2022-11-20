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
	int clientID;
	printf("Enter Client ID : ");
	scanf("%d", &clientID);
	fgetc(stdin);

	int fpid = fork();

	if(fpid != 0)
	{
		// writer
		int id1 = shmget(2000, sizeof(sem_t), 0666 | IPC_CREAT);
		int id2 = shmget(2001, 100, 0666 | IPC_CREAT);
	
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
		
		printf("Enter Message : \n");
		while(1)
		{
			char s[100];
			fgets(s, 100, stdin);
			s[strcspn(s, "\n")] = '\0';
			
			if(strcmp(s, "e") == 0)
			{
				strcpy(addr, s);			
				sem_post(sem);
				break;
			}
			sprintf(addr, "[%d] : %s\n", clientID, s);
			sem_post(sem);
		}
		printf("Client : Writer Shutting down ...\n");
		
		if(shmdt(addr) == -1 || shmdt(sem) == -1)
		{
			printf("Error in Detaching Segment.\n");
		}
	}
	else
	{
		// reader
		int id1 = shmget(1000, sizeof(struct semStruct), 0666 | IPC_CREAT);
		int id2 = shmget(1001, 100, 0666 | IPC_CREAT);
	
		if(id1 == -1 || id2 == -1)
		{
			printf("Creating segment failed!\n");
			return 1;
		}

		struct semStruct *sem = (struct semStruct*) shmat(id1, NULL, 0);
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
			sem_wait(&sem->semArr[clientID]);

			char s[100];
			strcpy(s, addr);
			s[strcspn(s, "\n")] = '\0';
			
			if(strcmp(s, "e") == 0)
				break;

			printf("Server : %s", addr);
		}
		printf("Client : Reader Shutting Down...[Server Down]\n");

		if(shmdt(addr) == -1 || shmdt(sem) == -1)
		{
			printf("Error in Detaching Segment.\n");
		}
		
	}
	return 0;
}

