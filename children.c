#include <stdio.h>
#include <unistd.h>

int main(int argc, char *argv[])
{
    printf("CHILD : STARTED\n");

    printf("CHILD : RECEIVED ARGUEMENTS\n");
    for (int i = 0; i < argc; i++)
    {
        printf("CHILD : args[%d] : %s\n", i, argv[i]);
    }

    char *cmd = "./children2";
    char *newArgs[argc + 1];
    char *envp[] = {NULL};

    newArgs[0] = cmd;

    int j = 1, n = argc -1;
    for (int i = n; i > 0; i--)
    {
        newArgs[j++] = argv[i];
    }

    newArgs[argc] = NULL;
    
    if(execve(cmd, newArgs, envp) == -1)
    {
        printf("CHILD : FAILED EXECVE\n");
    }

    return 0;
}