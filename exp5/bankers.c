#include <stdio.h>
#include <stdbool.h>

#define n 5
#define m 3

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
    for(int k = 0;k<n;k++)
    {
        bool lflag = true;
        for(int i=0;i<n;i++)
        {
            if(finish[i] == true)
                continue;

            bool less = true;

            for(int j=0;j<m;j++)
            {
                if(need[i][j] > work[j])
                    less = false;
            }

            if(less)
            {
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
    scanf(" %d", &pid);
    pid--; // 0 based indexing
    printf("Enter Request vector : ");
    int request[m];
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

    printf("Enter Max Matrix :\n");
    for(int i=0;i<n;i++)
    {
        for(int j=0;j<m;j++)
        {
            scanf("%d", &max[i][j]);
        }
    }

    for(int i=0;i<n;i++)
    {
        for(int j=0;j<m;j++)
        {
            need[i][j] = max[i][j] - allocation[i][j];
        }
    }

    while(1)
    {
        resource_request();
    }
    return 0;
}
/*OUTPUT -
Enter Available Vector :
2 2 2
Enter Allocation Matrix :
1 2 3 
3 0 1
2 2 0
1 3 1
0 2 3
Enter Max Matrix :
4 4 8
7 1 4
4 3 2
7 5 4
2 5 5
Enter process id : 2
Enter Request vector : 0 1 0
Seqeunce = 3 5 1 2 4 
Resources Allocated Successfully.

Enter Available Vector :
2 2 2
Enter Allocation Matrix :
1 2 3
3 0 1
2 2 0
1 3 1
0 2 3
Enter Max Matrix :
4 4 8 
7 1 4 
4 3 2 
7 5 4
2 5 5 
Enter process id : 4
Enter Request vector : 0 0 1
Going into unsafe state. Resource Allocation Aborted.

Enter Available Vector :
6 3 5 4
Enter Allocation Matrix :
2 0 2 1
0 1 1 1
4 1 0 2
1 0 0 1
1 1 0 0
1 0 1 1
Enter Max Matrix :
9 5 5 5
2 2 3 3
7 5 4 4
3 3 3 2
5 2 2 1
4 4 4 4
Enter process id : 6
Enter Request vector : 3 2 3 3
Going into unsafe state. Resource Allocation Aborted.

Enter Available Vector :
6 3 5 4
Enter Allocation Matrix :
2 0 2 1
0 1 1 1
4 1 0 2
1 0 0 1
1 1 0 0
1 0 1 1
Enter Max Matrix :
9 5 5 5 
2 2 3 3
7 5 4 4
3 3 3 2
5 2 2 1
4 4 4 4
Enter process id : 6
Enter Request vector : 1 0 1 1
Seqeunce = 2 3 1 4 5 6 
Resources Allocated Successfully.
*/