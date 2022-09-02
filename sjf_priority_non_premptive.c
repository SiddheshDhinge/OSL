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

	int at[p], bt[p], pri[p];

	int total_time = 0;
	printf("Enter arrival and Burst time and Priority\n");
	for (int i = 0; i < p; i++)
	{
		printf("Process %d : ", i + 1);
		scanf("%d", &at[i]);
		scanf("%d", &bt[i]);
		scanf("%d", &pri[i]);
		
		at[i] = abs(at[i]);
		bt[i] = abs(bt[i]);
		pri[i] = abs(pri[i]);

		total_time += bt[i];
	}
    printf("\n");

	int clock = 0;
	int gantt[total_time];
    int exe = -1;

    while(clock < total_time)
    {
        if(exe != -1)
        {
            bt[exe]--;
            gantt[clock] = exe;
            clock++;

            if(bt[exe] == 0)
                exe = -1;
            continue;
        }
        for(int i=0;i<p;i++)
        {
            if(at[i] <= clock && bt[i] > 0)
            {
                if(exe == -1)
                {
                    exe = i;
                }
                else
                {
                    if(pri[i] < pri[exe])
                    {
                        exe = i;
                    }
                }
            }
        }
        
        bt[exe]--;
        gantt[clock] = exe;
        clock++;
        if(bt[exe] == 0)
            exe = -1;
    }

    line(total_time * 2);
    for(int i=0;i<total_time;i++)
    {
        printf("%d ", gantt[i] +1);
    }
    printf("\n");
    line(total_time * 2);

	return 0;
}

// 5 8 2 3 3 8 5 0 15 4 16 4 1 10 11 2
// 5 5 4 5 0 9 4 15 7 2 12 12 1 8 6 3