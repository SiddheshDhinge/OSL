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

    printf("init\n");
    for(int k = 0;k<n;k++)
    {
        for(int i=0;i<n;i++)
        {
            if(finish[i] = true)
                continue;

            bool less = true;

            for(int j=0;j<m;j++)
            {
                if(need[i][j] > work[j])
                    less = false;
            }

            if(less)
            {
                printf("%d \n", i);
                for(int j = 0;j<m;j++)
                {
                    work[j] = work[j] + allocation[i][j];
                }
                finish[i] = true;
                sequence[k] = i ;
                break;
            }
            else
            {
                return false;
            }
        }
    }

    printf("Seqeunce = ");
    for(int i=0;i<n;i++)
    {
        printf("%d ", sequence[i]);
    }
    printf("\n");
    return true;
}
int main()
{
    printf("available :\n");
    for(int i=0;i<m;i++)
    {
        scanf("%d", &available[i]);
    }
    printf("allocation :\n");
    for(int i=0;i<n;i++)
    {
        for(int j=0;j<m;j++)
        {
            scanf("%d", &allocation[i][j]);
        }
    }

    printf("need :\n");
    for(int i=0;i<n;i++)
    {
        for(int j=0;j<m;j++)
        {
            scanf("%d", &need[i][j]);
        }
    }

    printf("SAFE - %d\n", isSafe());

    return 0;
}

/*
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
*/