#include <stdio.h>
#include <unistd.h>

int main(int argv, char *args[])
{
	printf("CHILD [REV] : Started %d %d\n", getpid(), getppid());
	printf("CHILD [REV] : Received Arguments\n");
	
	for(int i=0; i<argv ;i++)
	{
		printf("ARGS[%d] : %s\n", i, args[i]);
	}
	printf("CHILD [REV] : Reversed Order : ");
	for(int i=argv-1;i>0;i--)
	{
		printf("%s ", args[i]);
	}
	printf("\n");
	printf("CHILD [REV] : Exitting\n");
	return 0;
}
