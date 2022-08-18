#include <stdio.h>
#include <stdbool.h>

struct process
{
    int at, bt;
};

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
    bool flag = false;
    int t_exe = 0;

    while(clock < total_time)
    {
        if(flag && t_exe < arr[exe].bt)
        {
            t_exe++;
            continue;
        }
        else
        {
            t_exe = 0;
        }
        for(int i=0;i<p;i++)
        {
            if(arr[i].at <= clock )
            {   
                if(exe == -1)
                {
                    exe = i;
                    flag = true;
                }
                else
                {           
                    if(arr[exe].bt > arr[i].bt )
                        exe = i;
                }
            }
        }
        gantt[clock] = exe;
        clock++;
    }

    for(int i=0;i<total_time;i++)
    {
        printf("%d", gantt[i] + 1);
    }
    printf("\n");
}
//4 0 7 2 4 4 1 5 4