#include <stdio.h>
void line(int n)
{
	for (int i = 0; i < n; i++)
		printf("=");
	printf("\n");
}

int abs(int a)
{
    if(a < 0)
        return -a;
    return a;
}

int main()
{
	int p;
	printf("Enter number of processes : ");
	scanf("%d", &p);
	p = abs(p);

	int at[p], bt[p];

	int total_time = 0;
	printf("Enter arrival and Burst time\n");
	for (int i = 0; i < p; i++)
	{
		printf("Process %d : ", i + 1);
		scanf("%d", &at[i]);
		scanf("%d", &bt[i]);
		
		at[i] = abs(at[i]);
		bt[i] = abs(bt[i]);

		total_time += bt[i];
	}

	int clock = 0;
	int queue[total_time];

	int exe = -1;

	while (clock != total_time)
	{
		exe = -1;
		for (int i = 0; i < p; i++)
		{
			if (clock >= at[i] && bt[i] > 0)
			{
				if (exe == -1)
				{
					exe = i;
				}
				else if (bt[exe] > bt[i])
				{
					exe = i;
				}
			}
		}
		if (exe != -1)
		{
			while(bt[exe] > 0)
			{
				queue[clock] = exe;
				bt[exe]--;
				clock++;
			}
		}
		else
		{
			queue[clock] = exe;
			clock++;
		}
	}

	line(2 * total_time);
	for (int i = 0; i < total_time; i++)
	{
		printf("%d ", queue[i] + 1);
	}
	printf("\n");
	line(2 * total_time);

	int ct[p], tat[p], wt[p];

	for (int i = 0; i < p; i++)
	{
		int tbt = 0;
		int tstart = -1;
		int last = -1;
		for (int j = 0; j < total_time; j++)
		{
			if (queue[j] == i)
			{
				tbt++;
				last = j;
				if (tstart == -1)
					tstart = j;
			}
		}

		ct[i] = last + 1;
		tat[i] = ct[i] - at[i];
		wt[i] = tat[i] - tbt;
	}

	line(55);
	printf("%10s|%10s|%10s|%10s|%10s|\n", "Process No", "A. T.","C. T.","T. A. T.","W. T.");
	for (int i = 0; i < p; i++)
	{
		printf("%10d|%10d|%10d|%10d|%10d|\n", i+1, at[i], ct[i], tat[i], wt[i]);
	}
	line(55);

	double avg_tat = 0, avg_wt = 0;
	for (int i = 0; i < p; i++)
	{
		avg_tat += tat[i];
		avg_wt += wt[i];
	}

	avg_tat = avg_tat / p;
	avg_wt = avg_wt / p;

	printf("Average Turn Around Time : %f\n", avg_tat);
	printf("Average Waiting Time : %f\n", avg_wt);

	return 0;
}

//5 8 2 3 8 0 15 16 4 10 11
//4 0 7 2 4 4 1 5 4

/*OUTPUT -
Enter number of processes : 4
Enter arrival and Burst time
Process 1 : 0 7
Process 2 : 2 4
Process 3 : 4 1
Process 4 : 5 4
================================
1 1 2 2 3 2 2 4 4 4 4 1 1 1 1 1
================================
=======================================================
Process No|     A. T.|     C. T.|  T. A. T.|     W. T.|
         1|         0|        16|        16|         9|
         2|         2|         7|         5|         1|
         3|         4|         5|         1|         0|
         4|         5|        11|         6|         2|
=======================================================
Average Turn Around Time : 7.000000
Average Waiting Time : 3.000000


Enter number of processes : 5
Enter arrival and Burst time
Process 1 : 8 2
Process 2 : 3 8
Process 3 : 0 15
Process 4 : 16 4
Process 5 : 10 11
================================================================================
3 3 3 2 2 2 2 2 1 1 2 2 2 5 5 5 4 4 4 4 5 5 5 5 5 5 5 5 3 3 3 3 3 3 3 3 3 3 3 3
================================================================================
=======================================================
Process No|     A. T.|     C. T.|  T. A. T.|     W. T.|
         1|         8|        10|         2|         0|
         2|         3|        13|        10|         2|
         3|         0|        40|        40|        25|
         4|        16|        20|         4|         0|
         5|        10|        28|        18|         7|
=======================================================
Average Turn Around Time : 14.800000
Average Waiting Time : 6.800000
*/

// 5 9 4 3 4 0 8 1 6 12 6
