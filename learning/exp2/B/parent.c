#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <stdlib.h>

int main()
{
	
	int n;
	printf("PARENT : Enter size : %d", getpid());
	scanf("%d", &n);
	int arr[n];
	printf("PARENT : Enter %d elements : ", n);
	for(int i=0;i<n;i++)
	{
		scanf("%d", &arr[i]);
	}
	
	
	printf("PARENT : Sorting\n");
	for(int i=0;i<n-1;i++)
	{
		for(int j=0;j<n-i-1;j++)
		{
			if(arr[j] > arr[j+1])
			{
				int tmp = arr[j];
				arr[j] = arr[j+1];
				arr[j+1] = tmp;
			}
		}
	}
	
	printf("PARENT : Sorted : ");
	for(int i=0;i<n;i++)
	{
		printf("%d ", arr[i]);
	}
	printf("\n");
	
	printf("PARENT : Creating Child Process\n");
	int id = fork();
	if(id == 0)
	{
		// child
		printf("CHILD : Started\n");
		char *cmd = "./child";
		char *args[n+2];
		args[0] = cmd;
		for(int i=1;i<=n;i++)
		{
			char *buff = (char *) malloc(sizeof(char) * 5);
			sprintf(buff, "%d", arr[i-1]);
			args[i] = buff;
		}
		args[n+1] = NULL;
		
		printf("CHILD : Calling Execve %d\n", getpid());
		execve(cmd, args, NULL);
	}
	printf("PARENT : Waiting for completion of Child.\n");
	wait(NULL);
	printf("PARENT : Exitting. %d\n", getpid());
	return 0;
}
