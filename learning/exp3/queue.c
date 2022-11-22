#include <stdio.h>
#include <stdbool.h>
#define n 5

int front = -1;
int rear = -1;
int queue[n];

bool fullQueue()
{
	if((rear +1) %n == front)
		return true;
	return false;
}

bool emptyQueue()
{
	if(front == -1 && rear == -1)
		return true;
	return false;
}

bool insertEle(int x)
{
	if(fullQueue())
	{
		return false;
	}
	
	rear = (rear +1) % n;
	queue[rear] = x;
	
	if(front == -1)
	{
		front = 0;
	}
	
	return true;
}

int removeEle()
{
	if(emptyQueue())
	{
		return -1;
	}
	
	int x = queue[front];
	queue[front] = 0;
	
	if(front == rear)
	{
		front = -1;
		rear = -1;
	}
	else
	{
		front = (front +1)%n;
	}

	return x;	
}

void printQueue()
{
	for(int i=0;i<n;i++)
	{
		printf("%2d ", queue[i]);
	}
	printf("\n");
}
/*
int main()
{
	insertEle(10);
	printQueue();
	insertEle(20);
	printQueue();
	insertEle(30);
	printQueue();
	insertEle(40);
	printQueue();
	insertEle(50);
	printQueue();
	insertEle(5);
	printQueue();
	insertEle(6);
	printQueue();
	insertEle(7);
	printQueue();
	removeEle();
	printQueue();
	removeEle();
	printQueue();
	removeEle();
	printQueue();
	removeEle();
	printQueue();
	removeEle();
	printQueue();
	removeEle();
	printQueue();
	removeEle();
	printQueue();
	removeEle();
	printQueue();
	insertEle(20);
	printQueue();
	insertEle(30);
	printQueue();
	insertEle(20);
	printQueue();
	insertEle(30);
	printQueue();
	removeEle();
	printQueue();
	insertEle(2);
	printQueue();
	insertEle(34);
	printQueue();
	insertEle(4);
	printQueue();
	insertEle(5);
	printQueue();
}
*/
