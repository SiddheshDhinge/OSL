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
		sleep(5);
		
		printf("\nback in child\n");
		printf("\nx = %d\n", x);
		
	}
	else
	{
		printf("\nEntered parent\n");
		printf("\nParent ID: %d\n", getppid());
		printf("\nChilds ID: %d\n", getpid());
		
		x = x+ 50;
		
		sleep(1);
		
		printf("\nback in parent\n");
		printf("\nx = %d\n", x);
	}
	
}
