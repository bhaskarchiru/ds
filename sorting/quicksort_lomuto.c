#include <stdio.h>
#include <stdlib.h>

void
swap(int *a, int *b)
{
	int	c;

	c = *a;
	*a = *b;
	*b = c;
	return;
}

int
partition(int *arr, int low, int high)
{
	int	pivot;
	int	i, j;

	pivot = arr[high];
	i = low;
	for(j = low; j < high; j++) {
		if(arr[j] < pivot) {
			swap(&arr[i], &arr[j]);
			i++;
		}
	}
	swap(&arr[i], &arr[high]);
	return i;	
}

void
quicksort(int *arr, int low, int high)
{
	int	pivotidx;

	if(low < high) {
		pivotidx = partition(arr, low, high);
		quicksort(arr, low, pivotidx - 1);
		quicksort(arr, pivotidx + 1, high);
	}
	return;
}

#if 0
 i = 0, j = 0, pivot = 11  13, 8, 1, 4, 2, 14, 6, 3, 7, 0, 17, 9, 5, 11
 i = 0, j = 1, pivot = 11  8, 13, 1, 4, 2, 14, 6, 3, 7, 0, 17, 9, 5, 11
 i = 1, j = 2, pivot = 11  8, 1, 13, 4, 2, 14, 6, 3, 7, 0, 17, 9, 5, 11
 i = 2, j = 3, pivot = 11  8, 1, 4, 13, 2, 14, 6, 3, 7, 0, 17, 9, 5, 11
 i = 3, j = 4, pivot = 11  8, 1, 4, 2, 13, 14, 6, 3, 7, 0, 17, 9, 5, 11
 i = 4, j = 5, pivot = 11  8, 1, 4, 2, 13, 14, 6, 3, 7, 0, 17, 9, 5, 11
 i = 4, j = 6, pivot = 11  8, 1, 4, 2, 6, 13, 14, 3, 7, 0, 17, 9, 5, 11
 i = 5, j = 7, pivot = 11  8, 1, 4, 2, 6, 3, 13, 14, 7, 0, 17, 9, 5, 11
 i = 6, j = 8, pivot = 11  8, 1, 4, 2, 6, 3, 7, 13, 14, 0, 17, 9, 5, 11
 i = 7, j = 9, pivot = 11  8, 1, 4, 2, 6, 3, 7, 0, 13, 14, 17, 9, 5, 11
 i = 8, j =10, pivot = 11  8, 1, 4, 2, 6, 3, 7, 0, 13, 14, 17, 9, 5, 11
 i = 9, j =11, pivot = 11  8, 1, 4, 2, 6, 3, 7, 0, 9, 13, 14, 17, 5, 11
 i =10, j =12, pivot = 11  8, 1, 4, 2, 6, 3, 7, 0, 9, 5, 13, 14, 17, 11

8, 1, 4, 2, 6, 3, 7, 0, 9, 5, 11, 13, 14, 17
#endif

int
main(int argc, char *argv[])
{

	int	ii, n, arr[] = {13, 8, 1, 4, 2, 14, 6, 3, 7, 0, 17, 9, 5, 11};

	n = sizeof(arr)/sizeof(arr[0]);
	quicksort(arr, 0, n - 1);
	for(ii = 0; ii < n; ii++) {
		printf(" %d ", arr[ii]);
	}
	printf("\n");
	return 0;
}
