#include <stdio.h>
#include <stdbool.h>

int queue[5];
int front =-1;
int rear =-1;

bool isEmpty()
{
	if(rear == -1 && front == -1)
		return true;
	return false;
}

bool isFull()
{
	if((rear + 1)%5 == front)
		return true;
	return false;
}
bool insert(int x)
{
	if(isFull())
	{
		return false;
	}

	rear = (rear +1) %5;
	queue[rear] = x;
	if(front == -1)
		front = 0;
	return true;
}

int removeitem()
{
	if(isEmpty())
		return -1;
	int x = queue[front];
	if(front == rear)
	{
		front = -1;
		rear = -1;
	}
	else
		front = (front +1)%5;
	return x;
}


void print()
{
	for(int i=0;i<5;i++)
		printf("%d ", queue[i]);
	printf("\n");
}
/*
int main()
{
	print();
	insert(5);
	print();
	insert(1);
	print();
	insert(2);
	print();
	insert(3);
	print();
	insert(4);
	print();
	insert(6);
	print();
	removeitem();
	print();
	removeitem();
	print();
	insert(9);
	print();
	insert(7);
	print();
	removeitem();
	print();
	removeitem();
	print();
	removeitem();
	print();
	removeitem();
	print();
	removeitem();
	print();
	insert(7);
	print();
	insert(8);
	print();

	return 0;
}
*/