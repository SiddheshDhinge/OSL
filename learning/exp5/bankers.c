#include <stdio.h>
#include <stdbool.h>

#define n 6
#define m 4
int need[n][m];
int max[n][m];
int allocation[n][m];
int available[m];

void print()
{
	printf("allocation :\n");
	for(int i=0;i<n;i++)
	{
		for(int j=0;j<m;j++)
			printf("%d ", allocation[i][j]);
		printf("\n");
	}
	printf("max :\n");
	for(int i=0;i<n;i++)
	{
		for(int j=0;j<m;j++)
			printf("%d ", max[i][j]);
		printf("\n");
	}
	printf("Need :\n");
	for(int i=0;i<n;i++)
	{
		for(int j=0;j<m;j++)
			printf("%d ", need[i][j]);
		printf("\n");
	}
	printf("available :\n");
	for(int i=0;i<m;i++)
	{
		printf("%d ", available[i]);
	}
}

bool safe_state()
{
	int work[m];
	bool finish[n];
	int sequence[n];
	
	for(int i=0;i<m;i++)
	{
		work[i] = available[i];
	}
	for(int i=0;i<n;i++)
	{
		finish[i] = false;
	}
	
	for(int t=0;t<n;t++)
	{
		for(int i=0;i<n;i++)
		{
			if(finish[i])
				continue;
				
			bool flag = true;
		
			for(int j=0;j<m;j++)
			{
				if(work[j] < need[i][j])
				{
					flag = false;
				}
			}
		
			if(flag)
			{
				for(int j=0;j<m;j++)
				{
					work[j] += allocation[i][j];
					finish[i] = true;
				}
				sequence[t] = i;
				break;
			}
		}
	}
	
	bool flag = true;
	for(int i=0;i<n;i++)
	{
		flag = flag & finish[i];
	}
	
	if(flag)
	{
		printf("Safe Sequence : ");
		for(int i=0;i<n;i++)
		{
			printf("%d ", sequence[i] +1);
		}
		printf("\n");
	}
	
	return flag;
}

void resource_request()
{
	int p;
	printf("Enter target process : ");
	scanf("%d", &p);
	p--;
	
	int request[m];
	printf("Enter request : ");
	for(int i=0;i<m;i++)
	{
		scanf("%d", &request[i]);
	}
	
	bool flag = true;
	for(int i=0;i<m;i++)
	{
		if(need[p][i] < request[i])
			flag = false;
	}
	
	if(flag == false)
	{
		printf("Request exceeds Need\n");
		return;
	}
	
	flag = true;
	
	for(int i=0;i<m;i++)
	{
		if(available[i] < request[i])
			flag = false;
	}
	
	if(flag == false)
	{
		printf("Request exceeds Available.\n");
		return ;
	}
	
	for(int i=0;i<m;i++)
	{
		available[i] -= request[i];
		need[p][i] -= request[i];
		allocation[p][i] += request[i];
	}

	if(safe_state())
	{
		printf("Resource allocated Successfully.\n");
	}
	else
	{	
		printf("Resource allocation Failed.\n");
		
		for(int i=0;i<m;i++)
		{
			available[i] += request[i];
			need[p][i] += request[i];
			allocation[p][i] -= request[i];
		}
	}
}

int main()
{
	printf("Enter Available :\n");
	for(int i=0;i<m;i++)
	{
		scanf("%d", &available[i]);
	}
	
	printf("Enter Allocation :\n");
	for(int i=0;i<n;i++)
	{
		printf("Process %d : ", i+1);
		
		for(int j=0;j<m;j++)
		{
			scanf("%d", &allocation[i][j]);
		}
	}
	
	printf("Enter Max :\n");
	for(int i=0;i<n;i++)
	{
		printf("Process %d : ", i+1);
		
		for(int j=0;j<m;j++)
		{
			scanf("%d", &max[i][j]);
		}
	}
	
	for(int i=0;i<n;i++)
	{	
		for(int j=0;j<m;j++)
		{
			need[i][j] = max[i][j] - allocation[i][j];
		}
	}
	
	while(1)
	{
		resource_request();
	}
	
	return 0;
}

/*

2 2 2
1 2 3 
3 0 1
2 2 0
1 3 1
0 2 3
4 4 8
7 1 4
4 3 2
7 5 4
2 5 5
2
0 1 0

Seqeunce = 3 5 1 2 4 
Resources Allocated Successfully.

2 2 2
1 2 3
3 0 1
2 2 0
1 3 1
0 2 3
4 4 8 
7 1 4 
4 3 2 
7 5 4
2 5 5 
4
0 0 1
Going into unsafe state. Resource Allocation Aborted.


6 3 5 4
2 0 2 1
0 1 1 1
4 1 0 2
1 0 0 1
1 1 0 0
1 0 1 1
9 5 5 5
2 2 3 3
7 5 4 4
3 3 3 2
5 2 2 1
4 4 4 4
6
3 2 3 3
Going into unsafe state. Resource Allocation Aborted.

6 3 5 4
2 0 2 1
0 1 1 1
4 1 0 2
1 0 0 1
1 1 0 0
1 0 1 1
9 5 5 5 
2 2 3 3
7 5 4 4
3 3 3 2
5 2 2 1
4 4 4 4
6
1 0 1 1
Seqeunce = 2 3 1 4 5 6 
*/
