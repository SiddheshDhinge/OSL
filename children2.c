#include <stdio.h>
int main(int argc, char *argv[])
{
    printf("IN PRINTING CHILD\n");

    printf("REVERSE ORDER\n");
    for (int i = 1; i < argc; i++)
    {
        printf("%s\n", argv[i]);
    }

    return 0;
}