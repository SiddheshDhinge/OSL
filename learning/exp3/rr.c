#include <stdio.h>
#include "queue.h"

struct process
{
	int pid, at, bt;
};

void line(int n)
{
	for(int i=0;i<n;i++)
		printf("-");
	printf("\n");
}
void display(int gantt[], int at[], int total_burst, int n)
{
	printf("\n");
	line(total_burst *2);
	for(int i=0;i<total_burst;i++)
	{
		printf("%d ", gantt[i] +1);
	}
	printf("\n");
	line(total_burst *2);
	
	int t_bt[n];
	int ct[n];
	
	/*

	*/

	line(7*5);
	printf("%5s|%5s|%5s|%5s|%5s|%5s|\n", "ID", "AT", "BT", "CT", "TAT", "WT");
	line(7*5);
	int total_tat = 0;
	int total_wt = 0;
	for(int i=0;i<n;i++)
	{
		printf("%5d|", i+1);
		printf("%5d|", at[i]);
		printf("%5d|", t_bt[i]);
		printf("%5d|", ct[i]);
		
		printf("%5d|", ct[i] - at[i]);		
		printf("%5d|\n", (ct[i] - at[i]) - t_bt[i]);

		total_tat += ct[i] - at[i];
		total_wt += (ct[i] - at[i]) - t_bt[i];
	}
	line(7*5);
	printf("Total TAT : %d\n", total_tat);
	printf("Total WT : %d\n", total_wt);
}

void rr(struct process p, int n, int tq)
{
	int total_time = 0;
	for(int i=0;i<n;i++)
		total_time += p[i].bt;

	int gantt[total_time];
	int exe = -1;
	int clock = 0;
	int tmp_tq = tq;
	
	while(clock < total_time)
	{
		for(int i=0;i<n;i++)
		{
			if(p[i].at <= clock && p[i].bt > 0)
			{
				exe = i;
				break;
			}
		}
		
		if(exe == -1)
			continue;
			
		while(p[exe].bt > 0 && tq > 0)
		{
			gantt[clock] = 
		}
	}
	
	display(gantt, at, total_burst, n);
}

int main()
{
	int n, tq;
	printf("Enter the number of processes : ");
	scanf("%d", &n);

	printf("Enter the Time Quantum : ");
	scanf("%d", &tq);
	
	struct process p[n];
	printf("Enter process AT and BT : ");
	for(int i=0;i<n;i++)
	{
		printf("Process [%d] : ",i+1);
		p[i].pid = i;
		scanf("%d %d", &p[i].at, &p[i].bt);
	}
	
	rr(p, n, tq);
	
	return 0;
}

/*
4
0 7
2 4
4 1
5 4



5
8 2 3 8 0 15 16 4 10 11

================================================================================
3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 2 2 2 2 2 2 2 2 1 1 5 5 5 5 5 5 5 5 5 5 5 4 4 4 4
================================================================================

*/
