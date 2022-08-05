#include <stdio.h>

int main()
{
	int x = 1;
	printf("\nMain Parent: %d\n", getppid());
	
	int id = fork();
	
	if(id == 0)
	{
		printf("\nEntered child\n");
		printf("\nParent ID: %d\n", getppid());
		printf("\nChilds ID: %d\n", getpid());
		
		x = x + 10;
		sleep(20);
		
		printf("\nback in child\n");
		printf("\nNow Child is Orphan\n");
		printf("\nParent ID: %d\n", getppid());
		printf("\nOrphan Childs ID: %d\n", getpid());
		printf("\nx = %d\n", x);
		printf("\nOrphan Child is Exiting\n");
	}
	else
	{
		printf("\nEntered parent\n");
		printf("\nParent ID: %d\n", getpid());
		
		x = x+ 50;
		sleep(10);
		
		printf("\nback in parent\n");
		printf("\nx = %d\n", x);
		printf("\nParent is Exiting\n");
	}
	return 0;
}
