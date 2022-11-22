#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

void sort(int arr[], int n)
{
    for(int i=0;i<n-1;i++)
    {
        for(int j=0;j<n-i-1;j++)
        {
            if(arr[j] > arr[j+1])
            {
                int tmp = arr[j];
                arr[j] = arr[j+1];
                arr[j+1] = tmp;
            }
        }
    }
}
void line(int w)
{
    for(int i=0;i<w;i++)
    {
        printf("%1s", "-");
    }
    printf("\n");
}
void display(int from[], int to[], int n)
{
    line(33);
    printf("%10s|%10s|%10s|\n", "From", "To", "Service");
    line(33);
    int totalMovement = 0;

    for(int i=0;i<n;i++)
    {
        printf("%10d|", from[i]);
        printf("%10d|", to[i]);
        printf("%10d|\n", abs(from[i] - to[i]));

        totalMovement += abs(from[i] - to[i]);
    }
    line(33);
    printf("%32d", totalMovement);
}

void fcfs(int arr[], int n, int head)
{
    int from[n], to[n];

    from[0] = head;
    to[0] = arr[0];
    
    for(int i=1;i<n;i++)
    {
        from[i] = arr[i-1];
        to[i] = arr[i];
    }

    display(from, to, n);
}
void sstf(int arr[], int n, int head)
{
    sort(arr, n);
    
    bool done[n];
    for(int i=0;i<n;i++)
        done[i] = false;

    int from[n];
    int to[n];
    int curPosition = head;

    for(int i=0;i<n;i++)
    {
        int loc;
        for(loc = 0;loc<n;loc++)
        {
            if(arr[loc] > head && done[loc] == false)
            {
                break;
            }
        }

        int prev = loc;
        do
        {
            prev--;
        } while (done[prev] == true && prev >= 0);
        
        if(loc == n)
        {
            done[prev] = true;
            to[i] = arr[prev];
        }
        else
        {
            if(abs(arr[prev] - curPosition) < abs(arr[loc] - curPosition) && prev != -1)
            {
                done[prev] = true;
                to[i] = arr[prev];
            }
            else
            {
                done[loc] =  true;
                to[i] = arr[loc];
            }
        }
        from[i] = curPosition;
        curPosition = to[i];
    }

    display(from, to, n);
}
void scan(int arr[], int n, int head)
{
    int nArr[n+1];
    for(int i=0;i<n;i++)
        nArr[i] = arr[i];
    nArr[n] = 199;
    n++;

    sort(nArr, n);
    
    int from[n], to[n];
    int curPosition = head;
    int loc;
    for(loc=0;loc<n;loc++)
    {
        if(nArr[loc] >= curPosition)
        {
            break;
        }
    }
    int id = 0;
    
    for(int i=loc;i<n;i++, id++)
    {
        from[id] = curPosition;
        to[id] = nArr[i];
        curPosition = to[id];
    }
    for(int i=loc-1;i>=0;i--, id++)
    {
        from[id] = curPosition;
        to[id] = nArr[i];
        curPosition = to[id];
    }

    display(from, to, n);
}
void cscan(int arr[], int n, int head)
{
    int nArr[n+2];
    for(int i=0;i<n;i++)
        nArr[i] = arr[i];
    nArr[n] = 199;
    nArr[n+1] = 0;
    n+=2;

    sort(nArr, n);
    
    int from[n], to[n];
    int curPosition = head;
    int loc;

    for(loc=0;loc<n;loc++)
    {
        if(nArr[loc] >= curPosition)
        {
            break;
        }
    }

    int id = 0;
    for(int i=loc; i<n;i++, id++)
    {
        from[id] = curPosition;
        to[id] = nArr[i];
        curPosition = to[id];
    }

    for(int i=0;i<loc;i++, id++)
    {
        from[id] = curPosition;
        to[id] = nArr[i];
        curPosition = to[id];
    }

    display(from, to, n);
}
void look(int arr[], int n, int head)
{
    sort(arr, n);

    int from[n], to[n];
    int loc;
    for(loc = 0;loc<n;loc++)
    {
        if(arr[loc] >= head)
            break;
    }

    int curPosition = head;
    int id = 0;

    for(int i=loc;i<n;i++, id++)
    {
        from[id] = curPosition;
        to[id] = arr[i];
        curPosition = arr[i];
    }

    for(int i=loc-1;i>=0;i--, id++)
    {
        from[id] = curPosition;
        to[id] = arr[i];
        curPosition = arr[i];
    }

    display(from, to, n);
}
void clook(int arr[], int n, int head)
{
    sort(arr, n);
    
    int from[n], to[n];
    int curPosition = head;
    int loc;
    for(loc =0;loc<n;loc++)
    {
        if(arr[loc] >= curPosition)
        {
            break;
        }
    }

    int id = 0;
    for(int i=loc;i<n;i++, id++)
    {
        from[id] = curPosition;
        to[id] = arr[i];
        curPosition = arr[i];
    }
    for(int i=0;i<loc;i++, id++)
    {
        from[id] = curPosition;
        to[id] = arr[i];
        curPosition = arr[i];
    }

    display(from, to, n);
}

int main()
{
    int n;
    printf("Enter the total number of track requests: ");
    scanf("%d", &n);

    int arr[n];
    printf("Enter the track requests: ");
    for(int i=0;i<n;i++)
    {
        scanf("%d", &arr[i]);
    }

    int head;
    printf("Enter initial postition: ");
    scanf("%d", &head);

    // while(1)
    {
        int arrCopy[n];
        for(int i=0;i<n;i++)
        {
            arrCopy[i] = arr[i];
        }
        printf("1: FCFS\n");
        printf("2: SSTF\n");
        printf("3: SCAN\n");
        printf("4: C-SCAN\n");
        printf("5: LOOK\n");
        printf("6: C-LOOK\n");
        printf("Choice: \n");
        int ch;
        scanf("%d", &ch);

        switch(ch)
        {
            case 1: fcfs(arrCopy, n, head);
                    break;
            case 2: sstf(arrCopy, n, head);
                    break;
            case 3: scan(arrCopy, n, head);
                    break;
            case 4: cscan(arrCopy, n, head);
                    break;
            case 5: look(arrCopy, n, head);
                    break;
            case 6: clook(arrCopy, n, head);
                    break;
            default:
                    printf("Wrong Choice.\n");
        }
    }
}