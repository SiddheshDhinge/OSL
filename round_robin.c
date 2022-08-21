#include <stdio.h>
#include "queue.h"

void line(int n)
{
	for (int i = 0; i < n; i++)
		printf("=");
	printf("\n");
}

int main()
{
    int p, tq;
    printf("Enter no of processes: ");
    scanf("%d", &p);

    printf("Enter Time Quantum : ");
    scanf("%d", &tq);

    process arr[p];
    printf("Enter Arrival and Burst Time: ");

    int total_time = 0;
    for(int i=0;i<p;i++)
    {
        printf("Process %d : ",i+1);
        scanf("%d", &arr[i].at);
        scanf("%d", &arr[i].bt);
        arr[i].pid = i;
        total_time += arr[i].bt;
    }

    for(int i=0;i<p;i++)
    {
        for(int j = 0;j<p-i-1;j++)
        {
            if(arr[j].at > arr[j+1].at)
            {
                process temp = arr[j];
                arr[j] = arr[j+1];
                arr[j+1] = temp;
            }
        }
    }


    for(int i=0;i<p;i++)
    {
        printf("Process %d : %d %d %d\n",i+1, arr[i].pid, arr[i].at, arr[i].bt);
    }

    int gantt[total_time];
    int queue_size = total_time / tq;
    init(queue_size);
    int clock = 0;
    int exe;
    int j = 0;
    int cq = tq;

    while(clock < total_time)
    {
        while(arr[j].at <= clock && j < p)
        {
            insert_last(arr[j]);
            j++;
        }

        if(cq > tq)
        {
            cq--;
        }
        else
        {
            cq = tq;
            process tmp = remove_first();
            if(tmp.pid == -1)
            {
                exe = -1;
            }
            else
            {
                exe = tmp.pid;
                tmp.bt--;
                insert_last(tmp);
            }
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

    return 0;
}

//5 4 5 4 0 9 15 7 12 12 8 6

//solve issue of accessing other elements from header ie decerement in steps.