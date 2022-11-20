#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <errno.h>

int main()
{
	char *fifo1 = "fifo1";
	char *fifo2 = "fifo2";
	char msg[100];

	if(mkfifo(fifo1, 0666) == -1 && errno != EEXIST)
	{
		printf("Fifo 1 Creation Failed..\n");
	}
	
	if(mkfifo(fifo2, 0666) == -1 && errno != EEXIST)
	{
		printf("Fifo 2 Creation Failed..\n");
	}
	
	while(1)
	{
		int fd1 = open(fifo1, O_WRONLY);
		if(fd1 == -1)
		{
			printf("Error opening FIFO 1");
			return 0;
		}
		
		printf("Enter the Message : ");
		fgets(msg, 100, stdin);
		
		write(fd1, msg, 100);
		if(close(fd1) == -1)
		{
			printf("Error Closing FIFO 1");
			return 0;
		}
		
		
		int fd2 = open(fifo2, O_RDONLY);
		if(fd2 == -1)
		{
			printf("Error opening FIFO 2");
			return 0;
		}
		
		read(fd2, msg, 100);
		printf("Client : %s", msg);
		
		if(close(fd2) == -1)
		{
			printf("Error Closing FIFO 1");
			return 0;
		}
	}

	return 0;
}
