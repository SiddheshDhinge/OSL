#include <stdio.h>
#include <stdbool.h>

void line(int n)
{
	for(int i=0;i<n;i++)
	{
		printf("-");
	}
	printf("\n");
}

void display(int *displayTable, bool hitMiss[], int requests[], int n, int m)
{
	for(int i=0;i<n;i++)
	{
		printf("%2d ", requests[i]);
	}
	printf("\n");
	line(3*n);
	for(int i=0;i<m;i++)
	{
		for(int j=0;j<n;j++)
		{
			int val = *displayTable++;
			if(val == -1)
			{
				printf("%2s ", "");
			}
			else
			{			
				printf("%2d ", val);
			}
		}
		printf("\n");
	}
	line(3*n);
	int hitCount= 0;
	for(int i=0;i<n;i++)
	{
		if(hitMiss[i] == true)
			hitCount++;
		printf("%2s ", (hitMiss[i]==0 ? "M" : "H"));
	}
	printf("\n");
	line(3*n);
	
	
	printf("%10s : %5d\n", "HITS", hitCount);
	printf("%10s : %5d\n", "MISS", n - hitCount);
	printf("%10s : %5f\n", "HIT RATE", (double)hitCount / (double)n);
	printf("%10s : %5f\n", "MISS RATE", (double)(n-hitCount) / (double)n);
}

void opr(int requests[], int n, int m)
{
	int pageTable[m];
	bool hitMiss[n];
	int displayTable[m][n];
	int r = 0;
	
	for(int i=0;i<m;i++)
	{
		pageTable[i] = -1;
	}
	
	for(int i=0;i<n;i++)
	{
		hitMiss[i] = false;
	}
	
	for(int i=0;i<n;i++)
	{
		if(r < m)
		{
			if(i > 0)
			{
				for(int j=0;j<m;j++)
				{
					if(requests[i] == pageTable[j])
					{
						hitMiss[i] = true;
						break;
					}
				}
				
				if(hitMiss[i] == false)
				{
					pageTable[r] = requests[i];
					r++;
				}
			}
			else
			{
				pageTable[r] = requests[i];
				r++;
			}
		}
		else
		{
			for(int j=0;j<m;j++)
			{
				if(requests[i] == pageTable[j])
				{
					hitMiss[i] = true;
					break;
				}
			}
			
			if(hitMiss[i] == false)
			{
				int farthest = 0;
				int farthest_idx = 0;
				for(int ele=0;ele<m;ele++)
				{
					for(int j=i+1;j<n;j++)
					{
						if(pageTable[ele] == requests[j])
						{
							if(farthest < j)
							{
								farthest = j;
								farthest_idx = ele;
							}
							break;
						}
						
						if(j == n-1)
						{
							farthest = j+1;
							farthest_idx = ele;
						}
					}
				}
				
				pageTable[farthest_idx] = requests[i];
			}
		}
		
		for(int j=0;j<m;j++)
		{
			displayTable[m-j-1][i] = pageTable[j];
		}
	}
	
	display(displayTable[0], hitMiss, requests, n, m);
}

void fcfs(int requests[], int n, int m)
{
	int pageTable[m];
	bool hitMiss[n];
	int displayTable[m][n];
	
	for(int i=0;i<m;i++)
	{
		pageTable[i] = -1;
	}
	
	for(int i=0;i<n;i++)
	{
		hitMiss[i] = false;
	}
	
	int frame=0;
	for(int i=0;i<n;i++)
	{
		if(i>0)
		{
			for(int j=0;j<m;j++)
			{
				if(pageTable[j] == requests[i])
				{
					hitMiss[i] = true;
					break;
				}	
			}
			if(hitMiss[i] == false)
			{
				pageTable[frame] = requests[i];
				frame = (frame +1) %m;
			}
		}
		else
		{
			pageTable[frame++] = requests[i];
		}
		
		for(int j=0;j<m;j++)
		{
			displayTable[m-j-1][i] = pageTable[j];
		}
	}
	
	display(displayTable[0], hitMiss, requests, n, m);
}

void lru(int requests[], int n, int m)
{
	int displayTable[m][n];
	int pageTable[m];
	bool hitMiss[n];
	int done[n];
	int frame = 0;
	
	for(int i=0;i<m;i++)
	{
		pageTable[i] = -1;
	}
	
	for(int i=0;i<n;i++)
	{
		hitMiss[i] = false;
		done[i] = false;
	}
	
	for(int i=0;i<n;i++)
	{
		int leastRecentlyUsed = -1;
		for(int j=0;j<i;j++)
		{
			if(done[j] == false)
			{
				if(leastRecentlyUsed == -1)
					leastRecentlyUsed = j;
				else if(requests[j] == requests[i])
					leastRecentlyUsed = j;
			}
		}
		
		if(i < m)
		{
			if(i > 0 && pageTable[leastRecentlyUsed] == requests[i])
			{
				// Already present
				done[leastRecentlyUsed] = true;
				hitMiss[i] = true;
			}
			else
			{
				// Add in new frame
				pageTable[frame++] = requests[i];
			}
		}
		else
		{
			done[leastRecentlyUsed] = true;
			
			if(requests[leastRecentlyUsed] == requests[i])
			{
				// Already present
				hitMiss[i] = true;
			}
			else
			{
				// Find replacement Frame
				for(int j=0; j<m; j++)
				{
					if(pageTable[j] == requests[leastRecentlyUsed])
					{
						pageTable[j] = requests[i];
						break;
					}
				}
			}
		}
		
		for(int j=0;j<m;j++)
		{
			displayTable[j][i] = pageTable[j];
		}
	}
	
	display(displayTable[0], hitMiss, requests, n, m);
}

int main()
{
	int m, n;
	printf("Enter Reference string and frame Size : ");
	scanf("%d %d", &n, &m);
	printf("Enter Reference String : ");
	
	int arr[n];
	for(int i=0;i<n;i++)
	{
		scanf("%d", &arr[i]);
	}
	
	while(1)
	{
		printf("1 : FCFS\n");
		printf("2 : LRU\n");
		printf("3 : OPR\n");
		int ch;
		scanf("%d", &ch);
		switch(ch)
		{
			case 1: fcfs(arr, n, m);
					break;
					
			case 2: lru(arr, n, m);
					break;
					
			case 3: opr(arr, n, m);
					break;
		}
		getchar();
		getchar();
	}
	return 0;
}

/*


20 3
7 0 1 2 0 3 0 4 2 3 0 3 2 1 2 0 1 7 0 1

*/
