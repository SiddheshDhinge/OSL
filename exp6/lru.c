#include <stdio.h>
#include <stdbool.h>

int main()
{
    int n, frameSize;
    printf("Enter Frame Size : ");
    scanf("%d", &frameSize);
    printf("Enter Number of Requests : ");
    scanf("%d", &n);

    int requests[n];
    int pageTable[frameSize];
    bool leastUsed[n];
    int displayMatrix[frameSize][n];
    bool hitMiss[n];
    int rear = 0;

    for(int i=0;i<n;i++)
    {
        leastUsed[i] = false;
        hitMiss[i] = false;
        scanf("%d", &requests[i]);
    }

    for(int i=0;i<frameSize;i++)
    {
        pageTable[i] = -1;
    }

    for(int i=0;i<n;i++)
    {
        int leastRecentlyUsed = -1;
        for(int j=0;j<i;j++)
        {
            if(leastUsed[j] == false)
            {
                if(leastRecentlyUsed == -1)
                {
                    leastRecentlyUsed = j;
                }
                else if(requests[j] == requests[i])
                {
                    leastRecentlyUsed = j;
                }
            }
        }

        if(i <= 2)
        {
            if(i > 0 && pageTable[leastRecentlyUsed] == requests[i])
            {
                // Already present A HIT
                leastUsed[leastRecentlyUsed] = true;
                hitMiss[i] = true;
            }
            else
            {
                // Miss Add Process
                pageTable[rear] = requests[i];
                rear++;
            }
        }
        else
        {
            leastUsed[leastRecentlyUsed] = true;
            printf("%2d : marked used : %2d\n", i, leastRecentlyUsed);
            if(pageTable[leastRecentlyUsed] == requests[i])
            {
                // Already present A HIT
                hitMiss[i] = true;
            }
            else
            {
                // Miss Replace process
                int target = requests[leastRecentlyUsed];
                for(int k=0;k<frameSize;k++)
                {
                    if(target == pageTable[k])
                    {
                        pageTable[k] = requests[i];
                    }
                }
            }
        }

        for(int j = 0;j<frameSize;j++)
        {
            displayMatrix[j][i] = pageTable[j];
        }
    }


    for(int i=0;i<frameSize;i++)
    {
        for(int j=0;j<n;j++)
        {
            if(displayMatrix[i][j] == -1)
                printf("%2s |", "");
            else
                printf("%2d |", displayMatrix[i][j]);
        }
        printf("\n");
    }
    return 0;
}
/*
3 9 7 0 1 2 3 0 0 3 5
*/