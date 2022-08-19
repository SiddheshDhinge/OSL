#include <stdio.h>
#include <stdbool.h>

struct process
{
    int at, bt;
};

void line(int n)
{
	for (int i = 0; i < n; i++)
		printf("=");
	printf("\n");
}

int main()
{
    int p;
    printf("Enter no. of processes : ");
    scanf("%d", &p);

    struct process arr[p];

    int total_time = 0;
    printf("Enter Arrival and Burst Time.\n");
    for (int i = 0; i < p; i++)
    {
        printf("Process %d : ", i + 1);
        scanf("%d", &arr[i].at);
        scanf("%d", &arr[i].bt);
        total_time += arr[i].bt;
    }

    int clock = 0;
    int gantt[total_time];

    int exe = -1;
    int t_exe = -1;

    while(clock < total_time)
    {
        if(exe != -1 && t_exe > 0)
        {
            t_exe--;
        }
        else
        {
            if(t_exe == 0)
            {
                arr[exe].bt = 0;
            }
            for(int i =0;i<p;i++)
            {
                if(arr[i].at <= clock)
                {
                    if(exe == -1)
                    {
                        exe = i;
                    }
                    else if((arr[exe].bt > arr[i].bt && arr[i].bt != 0) || arr[exe].bt == 0)
                    {
                        exe = i;
                    }
                }
            }
            t_exe = arr[exe].bt -1;
        }
        gantt[clock] = exe;
        clock++;
    }

    line(2 * total_time);
    for(int i=0;i<total_time;i++)
    {
        printf("%d ", gantt[i] + 1);
    }
    printf("\n");
    line(2 * total_time);

    int ct[p], bt[p], tat[p], wt[p];
    for(int i=0;i<p;i++)
    {
        int total_bt = 0;
        int start = -1;
        int last;
        for(int j = 0;j<total_time;j++)
        {
            if(gantt[j] == i)
            {
                if(start == -1)
                {
                    start = j;
                }
                else
                {
                    last = j;
                }
                total_bt++;
            }
        }
        ct[i] = last +1;
        bt[i] = total_bt;
        tat[i] = ct[i] - arr[i].at;
        wt[i] = tat[i] - bt[i];
    }
    
    double avg_tat = 0, avg_wt = 0;
    line(66);
    printf("%10s|%10s|%10s|%10s|%10s|%10s|\n", "Process No", "A. T.","C. T.", "B. T.", "T. A. T.","W. T.");
    for(int i=0;i<p;i++)
    {
        printf("Process %2d|%10d|%10d|%10d|%10d|%10d|\n", i+1, arr[i].at, ct[i], bt[i], tat[i], wt[i]);
        avg_tat += tat[i];
        avg_wt += wt[i];
    }
    line(66);

    avg_tat/=p;
    avg_wt/=p;
    printf("Average T. A. T. : %f\n", avg_tat);
    printf("Average W. T. : %f\n", avg_wt);
}
//4 0 7 2 4 4 1 5 4