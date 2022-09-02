#include <stdio.h>
int main(int argc, char *argv[])
{
    printf("PRINTING CHILD : STARTED\n");

    printf("PRINTING CHILD : REVERSE ORDER IS : ");
    for (int i = 1; i < argc; i++)
    {
        printf("%s ", argv[i]);
    }
    printf("\n");
    return 0;
}