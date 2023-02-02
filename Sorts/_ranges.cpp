#include <stdio.h>
#include <algorithm>
#include <ranges>

#include <vector>
#include <list>
#include <map>
#include <array>

#include "Timer.h"

#include <numeric>

template <std::ranges::common_range R>
void Bubble(R& r, int n)
{
	int i, j;
	bool IsSwapped;

	for (i = 0; i < n - 1; i++)
	{
		IsSwapped = false;
		for (j = 0; j < n - i - 1; j++)
		{

			if (r[j] > r[j + 1])
			{
				std::ranges::swap(r[j], r[j + 1]);
				IsSwapped = true;
			}

		}
		if (IsSwapped == false)
			break;
	}
}

template <std::ranges::common_range R>
void Print(R& r, int s)
{
	int i;
	for (i = 0; i < s; i++)
		printf("%c ", r[i]);
	printf("\n");
}

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