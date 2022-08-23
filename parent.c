#include <stdio.h>
#include <unistd.h>

void swap(int *a, int *b)
{
    int tmp = *a;
    *a = *b;
    *b = tmp;
}

int main()
{
    int arr[10];
    int n = 10;
    printf("Enter 10 elements: ");
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

    printf("SORTING COMPLETE\n");

    printf("SORTED ELEMENTS : ")
    for(int i=0;i<n;i++)
    {
        printf("%d ", arr[i]);
    }
    printf("\n");

    char cmd[] = "./children";
    char *args[] = {"children", NULL};
    char *envp[] = {NULL};
    
    if(execve(cmd, args, envp) == -1)
    {
        printf("PARENT FAILED EXECVE\n");
    }

    return 0;
}