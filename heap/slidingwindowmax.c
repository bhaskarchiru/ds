/*
 * 239. Sliding Window Maximum
 */

#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

#define LEFT(X)		(X << 1) + 1
#define RIGHT(X)	(X << 1) + 2
#define PARENT(X)	(X & 1) ? (X << 1) : (X << 1) - 1

typedef struct heapnode {
	int	val;	/* Value of this heap node */
	int	idx;	/* Index of this element in array */
} heapnode_t;

typedef struct heap {
	heapnode_t	*data;
	int		*pos;	/* Map of heap node idx => array value idx */
	int		size;
	int		capacity;
} heap_t;

heap_t *
init_heap(int capacity)
{
	heap_t	*h = malloc(sizeof(heap_t));
	h->capacity = capacity;
	h->data = malloc(sizeof(heapnode_t *) * h->capacity);
	h->pos = malloc(sizeof(int) * h->capacity);
	h->size = 0;
	return h;
}

void
deinit_heap(heap_t *heap)
{

	free(heap->data);
	free(heap);
	return;
}

int
insert_heap(heap_t *heap, int num, int idx)
{
	heapnode_t *hnode = &heap->data[heap->size];
	
	hnode->val = num;
	hnode->idx = idx;

}

int *
maxSlidingWindow(int* nums, int numsSize, int k, int* returnSize)
{
	heap_t	*h;


	h = init_capacity(

}

int
main(int argc, char *argv[])
{
	int arr[] = {1,3,-1,-3,5,3,6,7};
	int k = 3;
	int *result = NULL, resultsz, i;

	result = maxSlidingWindow(arr, sizeof(arr)/sizeof(arr[0]), k, &resultsz);
	for(i = 0; i < resultsz; i++) {
		printf(" %d ", result[i]);
	}
	printf("\n");
	return 0;
}
