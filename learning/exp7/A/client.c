#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <errno.h>
#include <stdbool.h>
#include <string.h>

int findWords(char *s)
{
	int ans = 0;
	int i;
	for(i=1;s[i] != '\0'; i++)
	{
		bool f1 = s[i-1] != ' ' && s[i-1] != '.';
		bool f2 = s[i] == ' ' || s[i] == '.';
		
		if(f1 && f2)
			ans++;
	}
	
	if((s[i-1] != ' ' && s[i-1] != '.') & (i > 1 && s[0] != '\0'))
		ans++;
		
	return ans;
}

int findSentences(char *s)
{
	int ans = 0;
	int i;
	for(i=0;s[i] != '\0'; i++)
	{
		if(s[i] == '.')
			ans++;
	}
	if(i == 0)
		return 0;
		
	if(s[i-1] == '.')
		return ans;
		
	return ans+1;
}

int main()
{
	char *fifo1 = "fifo1";
	char *fifo2 = "fifo2";
	char msg[100];
	
	while(1)
	{
		int fd1 = open(fifo1, O_RDONLY);
		if(fd1 == -1)
		{
			printf("Error opening FIFO 1");
			return 0;
		}
		
		read(fd1, msg, 100);
		printf("Server : %s", msg);
		
		msg[strcspn(msg, "\n")] = '\0';
		int w = findWords(msg);
		int s = findSentences(msg);
		
		if(close(fd1) == -1)
		{
			printf("Error Closing FIFO 1");
			return 0;
		}
		
		int fd2 = open(fifo2, O_WRONLY);
		if(fd2 == -1)
		{
			printf("Error opening FIFO 2");
			return 0;
		}
		
		sprintf(msg, "Words : [%d] | Sentences : [%d]\n", w, s);
		write(fd2, msg, 100);
		
		if(close(fd2) == -1)
		{
			printf("Error Closing FIFO 2");
			return 0;
		}
	}

	return 0;
}
