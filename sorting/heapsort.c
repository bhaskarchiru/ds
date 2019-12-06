#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

#define LEFT(x)		\
	(2 * (x) + 1)
#define RIGHT(x)	\
	(2 * (x) + 2)
#define PARENT(x)	\
	((x & 1) ? (x >> 1) : ((x >> 1) - 1))

void
swap(int *a, int *b)
{
	int c;

	c = *a;
	*a = *b;
	*b = c;
	return;
}

void
max_heapify(int *arr, int heap_last_idx)
{

	int	i, largest;

	/*
	 * start from last-node's parent
	 */

	for(i = PARENT(heap_last_idx); i >= 0; i--) {
		largest = i;
		if(LEFT(i) <= heap_last_idx && arr[LEFT(i)] > arr[largest]) {
			largest = LEFT(i);
		}
		if(RIGHT(i) <= heap_last_idx && arr[largest] < arr[RIGHT(i)]) {
			largest = RIGHT(i);
		}
		if(largest != i) {
			swap(&arr[i], &arr[largest]);
		}
	}
	return;
}

int
main(int argc, char *argv[])
{
	int i, n;
	int arr[] = {17, 13, 11, 7, 4, 18, 8, 5, 6, 3, 10, 2, 1};

	/*
	 * Algorithm for heap-sort:
	 *	heap_last_idx = n - 1
	 *  	MAX-HEAPIFY(arr, heap_last_idx)
	 *	
	 *  	for (i = 0; i < n - 1; i++)
	 *		swap(arr[0], a[heap_last_idx - i - 1])
	 *		MAX-HEAPIFY(arr, heap_last_idx - i -2)
	 */

	n = sizeof(arr)/sizeof(arr[0]);

	max_heapify(arr, n - 1);

	printf("After max_heapify:\n");
	for(i = 0; i < n; i++) {
		printf(" %d ", arr[i]);
	}
	printf("\n");

	/*
	 * Now, we've max-heap; maximum element is at root of the  binary tree,
	 * keep swapping it with last element as we progressively shrink 
	 * the logical heap.
	 */

	for(i = 0; i < n - 1; i++) {
		swap(&arr[0], &arr[n - i - 1]);
		max_heapify(arr, n - i - 2);
	}

	printf("After sorting:\n");
	for(i = 0; i < n; i++) {
		printf(" %d ", arr[i]);
	}
	printf("\n");
	return 0;
}
