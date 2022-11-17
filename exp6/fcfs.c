#include <stdio.h>
#include <stdbool.h>

int main()
{
    int frameSize;
    int n;

    printf("Enter Frame Size : ");
    scanf("%d", &frameSize);
    printf("Enter Number of Requests : ");
    scanf("%d", &n);

    int rear = 0;
    int requests[n];
    int pageTable[frameSize];
    int displayMatrix[frameSize][n];
    bool hitMiss[n];

    for(int i=0;i<n;i++)
    {
        hitMiss[i] = false;
        scanf("%d", &requests[i]);
    }

    for(int i=0;i<frameSize;i++)
    {
        pageTable[i] = -1;
    }

    for(int i=0;i<n;i++)
    {
        bool hitFlag = false;
        for(int j=0;j<frameSize;j++)
        {
            if(pageTable[j] == requests[i])
            {
                hitFlag = true;
                hitMiss[i] = true;
                break;
            }
        }
        if(!hitFlag)
        {
            pageTable[rear] = requests[i];
            rear = (rear +1) % frameSize;
        }

        for(int j = 0;j<frameSize;j++)
        {
            displayMatrix[j][i] = pageTable[j];
        }
    }

    double hits = 0, miss = 0;
    for(int i=0;i<n;i++)
    {
        if(hitMiss[i] == 0)
            miss++;
        else 
            hits++;
    }

    printf("%15s |", "Request");
    for(int j =0;j<n;j++)
    {
        printf("%2d |", requests[j]);
    }
    printf("\n");
    for(int i=0;i<frameSize;i++)
    {    
        printf("%15s |", "");
        for(int j =0;j<n;j++)
        {
            if(displayMatrix[i][j] == -1)
                printf("%2s |", "");
            else
                printf("%2d |", displayMatrix[i][j]);
        }
        printf("\n");
    }

    printf("%15s |", "Hit/ Miss");
    for(int j =0;j<n;j++)
    {
        printf("%2d |", hitMiss[j]);
    }
    printf("\n");
    printf("%15s : %f \n", "Hit Rate", (hits/ n));
    printf("%15s : %f \n", "Miss Rate", (miss/ n));

    return 0;
}
/*
3 9 7 0 1 2 3 0 0 3 5
*/