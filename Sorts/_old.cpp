#include <stdio.h>
#include <algorithm>
#include <stdbool.h>

#include "Timer.h"

void Bubble(int* arr, int n)
{
	int i, j;
	bool IsSwapped;

	for (i = 0; i < n - 1; i++)
	{
		IsSwapped = false;
		for (j = 0; j < n - i - 1; j++)
		{
			if (arr[j] > arr[j + 1])
			{
				std::swap(arr[j], arr[j + 1]);
				IsSwapped = true;
			}
		}
		if (IsSwapped == false)

			break;
	}
}

void Print(int arr[], int size)
{
	int i;
	for (i = 0; i < size; i++)
		printf("%d ", arr[i]);
}

// Driver program to test above functions
int main()
{
	Timer t
		;
	int arr[] = { 90, 82, 70, 66, 54, 43, 34, 23, 14, 9 };
	int n = sizeof(arr) / sizeof(arr[0]);

	Bubble(arr, n);
	printf("Sorted array: \n");
	Print(arr, n);
	return 0;
}
