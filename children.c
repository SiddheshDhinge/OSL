#include <stdio.h>
#include <unistd.h>

int main(int argc, char *argv[])
{
    printf("IN REVERSING CHILD\n");
/* 
    for (int i = 1; i < argc; i++)
    {
        printf("%s\n", argv[i]);
    }
 */
    char *newArgs[argc];
    int j = 0, n = argc -1;
    for (int i = n; i > 0; i--)
    {
        newArgs[j++] = argv[i];
    }
    newArgs[n] = NULL;
    char *envp[] = {NULL};
    char *cmd = "./children2";
    
    if(execve(cmd, newArgs, envp) == -1)
    {
        printf("REVERSING CHILD FAILED EXECVE\n");
    }

    return 0;
}