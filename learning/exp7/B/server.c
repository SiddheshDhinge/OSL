#include <stdio.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <sys/types.h>

int main()
{
	int id = shmget(123, 100, 0666 | IPC_CREAT);
	
	if(id == -1)
	{
		printf("Creating segment failed!\n");
		return 0;
	}

	char *addr = (char*) shmat(id, NULL, 0);

	if(addr == (void*) -1)
	{
		printf("Attaching to segment Failed!\n");
		return 0;
	}
	
	printf("Attached To : %p\n", addr);
	while(1)
	{
		printf("Enter String : ");
		fgets(addr, 100, stdin);
		printf("Segment Contents : %s", addr);
	}
	return 0;
}

