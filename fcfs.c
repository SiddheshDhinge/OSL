#include <stdio.h>

struct process
{
    int pid, at, bt;
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

        arr[i].pid = i;
        total_time += arr[i].bt;
    }

    for(int i = 0;i<p;i++)
    {
        for(int j = 0;j<p-i-1;j++)
        {
            if(arr[j].at > arr[j+1].at)
            {
                struct process temp = arr[j+1];
                arr[j+1] = arr[j];
                arr[j] = temp;
            }
        }
    }

    int gantt[total_time];

    int clock = 0;

    for(int i = 0;i<p;i++)
    {
        for(int j = 0;j<arr[i].bt;j++)
        {
            gantt[clock] = arr[i].pid;
            clock++;
        }
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

    return 0;
}

//4 0 7 2 4 4 1 5 4
//5 8 2 3 8 0 15 16 4 10 11