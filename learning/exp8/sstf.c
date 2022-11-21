#include <stdio.h>
#define INT_MAX 1e5

int abs(int a)
{
	if(a < 0)
		return -a;
	return a;
}

void display(int from[], int to[], int n)
{
	printf("%10s|%10s|%10s|\n", "FROM", "TO", "DIST");
	int totalseek = 0;
	for(int i=0;i<n;i++)
	{
		printf("%10d|", from[i]);
		printf("%10d|", to[i]);
		totalseek += abs(from[i] -to[i]);
		printf("%10d|\n", abs(from[i] -to[i]));
	}
	
	printf("%32d|\n", totalseek);
}

int main()
{
	int n;
	printf("Enter number of track requests : ");
	scanf("%d", &n);

	int arr[n];
	printf("Enter track requests : ");
	for(int i=0;i<n;i++)
	{
		scanf("%d", &arr[i]);
	}
	int head;
	printf("Enter head position : ");
	scanf("%d", &head);

	
	int from[n];
	int to[n];

	for(int i=0;i<n;i++)
	{
		int mn = abs(head - arr[0]);
		int mn_idx = 0;
		for(int j=0;j<n;j++)
		{
			int dist = abs(arr[j] - head);

			if(mn > dist)
			{
				mn = dist;
				mn_idx = j;
			}
		}
		
		from[i] = head;
		to[i] = arr[mn_idx];
		
		head = arr[mn_idx];
		arr[mn_idx] = INT_MAX;
	}
	
	display(from, to, n);
	
	return 0;
}

/*
5
100
199
10
20
30
50
*/
