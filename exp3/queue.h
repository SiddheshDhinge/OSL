#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>

typedef struct process
{
    int pid, at, bt;
}process;

process *queue;
int front = -1;
int last = -1;
int size;

bool init(int _size)
{
    queue = (process*) calloc(_size, sizeof(process));
    size = _size;
    if(queue == NULL)
        return false;
    return true;
}

bool insert_last(process data)
{
    if ((last + 1) % size == front)
    {
        return false;
    }
    else if(front == -1)
    {
        front = 0;
        last = 0;
        queue[last] = data;
    }
    else
    {
        last = (last + 1) % size;
        queue[last] = data;
    }
    return true;
}

process remove_first()
{
    process data;
    data.pid = -1;
    
	if(front == -1 && last == -1)
		return data;

    data = queue[front];
    if(front == last)
    {   
        front = last = -1;
    }
    else
    {
        front = (front + 1) % size;
    }
    return data;
}

void print()
{
    for(int i = 0;i<size;i++)
    {
        printf("%d %d\n", queue[i].at, queue[i].bt);
    }
    printf("\n");
}
