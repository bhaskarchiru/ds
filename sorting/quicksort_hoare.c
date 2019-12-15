#include <stdio.h>
#include <stdlib.h>

/*
 * Quicksort using Hoare's partition scheme.
 */

void
swap(int *a, int *b)
{
	int	c;

	c = *a;
	*a = *b;
	*b = c;
	return;
}

#if 0
pivot = 13, i = -1, j = 14	13, 8, 1, 4, 2, 14, 6, 3, 7, 0, 17, 9, 5, 11
pivot = 13, i = -1, j = 13      13, 8, 1, 4, 2, 14, 6, 3, 7, 0, 17, 9, 5, 11
pivot = 13, i = 0, j = 13	13, 8, 1, 4, 2, 14, 6, 3, 7, 0, 17, 9, 5, 11
swap a[0], a[13] ( 13 and 11 )
pivot = 13, i = 0, j = 12	11, 8, 1, 4, 2, 14, 6, 3, 7, 0, 17, 9, 5, 13
pivot = 13, i = 5, j = 12       11, 8, 1, 4, 2, 14, 6, 3, 7, 0, 17, 9, 5, 13
swap a[5], a[12] ( 14 and 5)
pivot = 13, i = 5, j = 12       11, 8, 1, 4, 2, 5, 6, 3, 7, 0, 17, 9, 14, 13
pivot = 13, i = 5, j = 11	11, 8, 1, 4, 2, 5, 6, 3, 7, 0, 17, 9, 14, 13
pivot = 13, i = 10, j = 11	11, 8, 1, 4, 2, 5, 6, 3, 7, 0, 17, 9, 14, 13
swap a[10], a[11] (17 and 9)
pivot = 13, i = 10, j = 11	11, 8, 1, 4, 2, 5, 6, 3, 7, 0, 9, 17, 14, 13
pivot = 13, i = 10, j = 10	11, 8, 1, 4, 2, 5, 6, 3, 7, 0, 9, 17, 14, 13
pivot = 13, i = 11, j = 10	11, 8, 1, 4, 2, 5, 6, 3, 7, 0, 9, 17, 14, 13

Parititon: [ 11, 8, 1, 4, 2, 5, 6, 3, 7, 0, 9 ] [17, 14, 13]

#endif

partition(int *arr, int low, int high)
{
	int	pivot;
	int	i, j;

	pivot = arr[low];
	i = low - 1;
	j = high + 1;

	while(1) {
		do {
			j--;
		} while(arr[j] > pivot);
		do {
			i++;
		} while(arr[i] < pivot);
		if(i >= j) {
			return j;
		}
		printf("swapping %d %d\n", arr[i], arr[j]);
		swap(&arr[i], &arr[j]);
	}
}

void
quicksort(int *arr, int low, int high)
{
	int	pivotidx;

	if(high -low >= 2) {
		pivotidx = partition(arr, low, high);
		quicksort(arr, low, pivotidx);
		quicksort(arr, pivotidx + 1, high);
	} else if(high - low && arr[low] > arr[high]) {
		swap(&arr[low], &arr[high]);
	}
	return;
}

int
main(int argc, char *argv[])
{

	int	ii, n;
	int	arr[] = {13, 8, 1, 4, 2, 14, 6, 3, 7, 0, 17, 9, 5, 11};
	//int	arr[] = {13, 8};

	n = sizeof(arr)/sizeof(arr[0]);
	quicksort(arr, 0, n - 1);
	for(ii = 0; ii < n; ii++) {
		printf(" %d ", arr[ii]);
	}
	printf("\n");
	return 0;
}
