/*
 * Implementation of bubble sort
 */

#include <stdio.h>
#include <stdlib.h>

void
swap(int *a, int *b)
{
	int c = *a;
	*a = *b;
	*b = c;
	return;
}

void
print_arr(int *arr, int n)
{
	int	i;

	for(i = 0; i < n; i++) {
		printf(" %d ", arr[i]);
	}
	printf("\n");
	return;
}

void
bubblesort(int *arr, int n)
{
	int i, j, swaps = 0;

	for(i = 0; i < n - 1 ; i++) {
		for(j = 1; j < n - i; j++) {
			if(arr[j] < arr[j - 1]) {
				swap(&arr[j], &arr[j - 1]);
				swaps++;
			}
		}
		if(swaps) {
			swaps = 0;
		} else {
			break;
		}
		print_arr(arr, n);
	}
	return;
}

int
main(int argc, char *argv[])
{

	int	arr[] = {7, 1, 4, 8, 2, 9, 10, 3};
	int	i, n;

	n = sizeof(arr)/sizeof(arr[0]);
	printf("Before sorting:\n");
	print_arr(arr, n);
	bubblesort(arr, n);
	printf("After sorting:\n");
	print_arr(arr, n);
	return 0;
}
