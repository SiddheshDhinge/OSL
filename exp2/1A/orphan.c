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

/*OUTPUT-
Main Parent: 2691

Entered parent

Parent ID: 7533

Entered child

Parent ID: 7533

Childs ID: 7534

back in parent

x = 51

Parent is Exiting
osboxes@osboxes:~/TE/OSL/exp2/1A$ 
back in child

Now Child is Orphan

Parent ID: 1832

Orphan Childs ID: 7534

x = 11

Orphan Child is Exiting

*/
