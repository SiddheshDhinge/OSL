#include <stdio.h>
#include <unistd.h>

int main()
{
	int pid = fork();
	
	if(pid == 0)
	{
		printf("CHILD : Child Started\n");
		printf("CHILD : Child Parent ID - %d\n", getppid());
		printf("CHILD : Child ID - %d\n", getpid());
		
		sleep(1);

		printf("CHILD : Child Became Zombie\n");
		printf("CHILD : Child Parent ID - %d\n", getppid());
		printf("CHILD : Child ID - %d\n", getpid());
	}
	else
	{
		printf("PARENT : Parent Started\n");
		printf("PARENT : Parent Parent ID - %d\n", getppid());
		printf("PARENT : Parent ID - %d\n", getpid());
		
		sleep(10);
		
		printf("PARENT : Exitting without calling WAIT\n");
	}
	return 0;
}
