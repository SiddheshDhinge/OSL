#include <stdio.h>

void merge(int arr[], int beg, int mid, int end)
{
	int n1 = mid - beg;
	int n2 = end - mid +1;
	int left[n1], right[n2];
	
	int k = beg;
	
	for(int i=0;i<n1;i++)
		left[i] = arr[k++];
	for(int i=0;i<n2;i++)
		right[i] = arr[k++];
		
		
	k = beg;
	int i = 0;
	int j = 0;
	
	
	while(i < n1 && j < n2)
	{
		if(left[i] < right[j])
		{
			arr[k] = left[i++];
		}
		else
		{
			arr[k] = right[j++];
		}
		k++;
	}
	
	while(i < n1)
	{
		arr[k++] = left[i++];
	}
	while(j < n2)
	{
		arr[k++] = right[j++];
	}
}

void mergeSort(int arr[], int beg, int end)
{
	if(beg < end)
	{
		int mid = (beg + end) / 2;
		
		mergeSort(arr, beg, mid);
		mergeSort(arr, mid +1, end);
		
		merge(arr, beg, mid+1, end);
	}
}

int main()
{
	int n = 10;
	int arr[10] = {7,6,10,4,1,8,5,2,3,9};
	
	mergeSort(arr, 0, n-1);
	
	for(int i=0;i<n;i++)
	{
		printf("%d ", arr[i]);
	}
	printf("\n");
	
	return 0;
}
