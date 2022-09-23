#include <stdio.h>
#include <stdbool.h>

#define n 6
#define m 4

int available[m];
int allocation[n][m];
int max[n][m];
int need[n][m];

bool isSafe()
{
    int work[m];
    int sequence[n];
    int finish[n];

    for(int i=0;i<n;i++)
    {
        finish[i] = false;
    }
    for(int i=0;i<m;i++)
    {
        work[i] = available[i];
    }
    printf("init\n");
    for(int k = 0;k<n;k++)
    {
        bool lflag = true;
        for(int i=0;i<n;i++)
        {
            printf("TRY %d\n", i);
            if(finish[i] == true)
                continue;

            bool less = true;

            for(int j=0;j<m;j++)
            {
                printf("%d | %d\n", need[i][j], work[j]);
                if(need[i][j] > work[j])
                    less = false;
            }

            if(less)
            {
                printf("LESS %d\n", i);
                lflag = false;
                for(int j = 0;j<m;j++)
                {
                    work[j] = work[j] + allocation[i][j];
                }
                finish[i] = true;
                sequence[k] = i;
                break;
            }
        }
        if(lflag)
        {
            return false;
        }
    }

    printf("Seqeunce = ");
    for(int i=0;i<n;i++)
    {
        printf("%d ", sequence[i] +1);
    }
    printf("\n");
    return true;
}

void resource_request()
{
    printf("Enter process id : ");
    int pid;
    scanf("%d", &pid);
    pid--; // 0 based indexing
    printf("Enter Reuest vector : ");
    int request[3];
    for(int i=0;i<m;i++)
    {
        scanf("%d", &request[i]);
    }

    for(int i=0;i<m;i++)
    {
        if(need[pid][i] < request[i])
        {
            printf("ERROR : Requested resource must be less than need.\n");
            return;
        }
    }

    for(int i=0;i<m;i++)
    {
        if(available[i] < request[i])
        {
            printf("Process must wait some time till resources are available.\n");
            return;
        }
    }


    for(int i=0;i<m;i++)
    {
        available[i] -= request[i];
        allocation[pid][i] += request[i];
        need[pid][i] -= request[i];
    }

    if(isSafe())
    {
        printf("Resources Allocated Successfully.\n");
    }
    else
    {
        for(int i=0;i<m;i++)
        {
            available[i] += request[i];
            allocation[pid][i] -= request[i];
            need[pid][i] += request[i];
        }

        printf("Going into unsafe state. Resource Allocation Aborted.\n");
    }
}

int main()
{
    printf("Enter Available Vector :\n");
    for(int i=0;i<m;i++)
    {
        scanf("%d", &available[i]);
    }
    printf("Enter Allocation Matrix :\n");
    for(int i=0;i<n;i++)
    {
        for(int j=0;j<m;j++)
        {
            scanf("%d", &allocation[i][j]);
        }
    }

    printf("Enter Need Matrix :\n");
    for(int i=0;i<n;i++)
    {
        for(int j=0;j<m;j++)
        {
            scanf("%d", &need[i][j]);
        }
    }

    while(1)
    {
        resource_request();
    }
    return 0;
}

/*
safe 1 = 
2 2 2
1 2 3
3 0 1
2 2 0
1 3 1
0 2 3
3 2 5
4 1 3
2 1 2
6 2 3
2 3 2 

safe 2
6 3 5 4
2 0 2 1
0 1 1 1
4 1 0 2
1 0 0 1
1 1 0 0
1 0 1 1
7 5 3 4
2 1 2 2
3 4 4 2
2 3 3 1
4 1 2 1
3 4 3 3
*/