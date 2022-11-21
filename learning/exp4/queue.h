#include <stdio.h>
#include <stdbool.h>
#define size 5

int queue[size];
int front  = -1;
int rear = -1;

bool fullQueue()
{
	if((rear +1)%size == front)
		return true;
	return false;
}

bool emptyQueue()
{
	if(front == -1 && rear == -1)
		return true;
	return false;
}

bool insertElement(int x)
{
	if(fullQueue())
		return false;

	rear = (rear +1) % size;
	queue[rear] = x;

	if(front == -1)
		front = 0;
	return true;
}

int removeElement()
{
	if(emptyQueue())
		return -1;

	int x = queue[front];
	queue[front] = 0;

	if(front == rear)
	{
		front = rear = -1;
	}
	else
		front = (front +1) % size;


	return x;
}

void printQueue()
{
	printf("Queue : ");
	for(int i=0;i<size;i++)
		printf("%2d ", queue[i]);
	printf("\n");
}
/*
int main()
{
	insertElement(5);
	printQueue();
	insertElement(4);
	printQueue();
	insertElement(3);
	printQueue();
	insertElement(40);
	printQueue();
	insertElement(50);
	printQueue();
	insertElement(60);
	printQueue();
	insertElement(70);
	printQueue();
	removeElement();
	printQueue();
	removeElement();
	printQueue();
	removeElement();
	printQueue();
	insertElement(55);
	printQueue();
	insertElement(44);
	printQueue();
	insertElement(33);
	printQueue();
	removeElement();
	printQueue();
	insertElement(80);
	printQueue();
	removeElement();
	printQueue();
	removeElement();
	printQueue();
	removeElement();
	printQueue();
	removeElement();
	printQueue();
	removeElement();
	printQueue();
	removeElement();
	printQueue();
	removeElement();
	printQueue();
	insertElement(80);
	printQueue();
}
*/
