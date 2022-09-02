#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

void swap(int *a, int *b)
{
    int tmp = *a;
    *a = *b;
    *b = tmp;
}

void toString(char *args[], char *cmd, int arr[], int n)
{
    args[0] = cmd;
    for(int i = 1;i<=n;i++)
    {
        char *buffer = malloc(sizeof(char) * 10);
        sprintf(buffer, "%d", arr[i-1]);
        args[i] = buffer;
    }
    args[n+1] = NULL;
}

int main()
{
    printf("PARENT : STARTED\n");
    int arr[10];
    int n = 10;
    printf("PARENT : Enter 10 elements: ");
    for(int i=0;i<n;i++)
    {
        scanf("%d", &arr[i]);
    }

    for(int i=0;i<n-1;i++)
    {
        for(int j = 0;j<n-i-1;j++)
        {
            if(arr[j] > arr[j+1])
            {
                swap(&arr[j], &arr[j+1]);
            }
        }
    }

    printf("PARENT : SORTING COMPLETE\n");

    printf("PARENT : SORTED ELEMENTS : ");
    for(int i=0;i<n;i++)
    {
        printf("%d ", arr[i]);
    }
    printf("\n");

    char cmd[] = "./children";
    char *args[n + 2];
    char *envp[] = {NULL};

    toString(args, cmd, arr, n);

    printf("PARENT : Calling Children...\n");    

    int pid = fork();
    if(pid == 0)
    {
        if(execve(cmd, args, envp) == -1)
        {
            printf("PARENT : FAILED EXECVE\n");
        }
    }
    
    wait(NULL);
    printf("PARENT : EXITTING\n");
    return 0;
}