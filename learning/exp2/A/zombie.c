#include <unistd.h>
#include <stdio.h> 
#include <sys/types.h>
#include <sys/wait.h>

int main()
{
	int id = fork();

	if(id == 0)
	{
		// child
		printf("CHILD : Entered\n");
		printf("CHILD : Parent ID - %d\n", getppid());
		printf("CHILD : My ID - %d\n", getpid());
		
		sleep(5);
		
		printf("CHILD : Became Zombie\n");
		printf("CHILD : Parent ID - %d\n", getppid());
		printf("CHILD : My ID - %d\n", getpid());
		printf("CHILD : Waiting for Parent\n");
	}
	else
	{
		// parent

		printf("PARENT : Entered\n");
		printf("PARENT : Parent ID - %d\n", getppid());
		printf("PARENT : My ID - %d\n", getpid());
		printf("PARENT : Busy with work\n");
		
		sleep(15);
		
		printf("PARENT : Completed Work\n");
		printf("PARENT : Exitting\n");
	
		wait(NULL);
	
	}

	return 0;
}
