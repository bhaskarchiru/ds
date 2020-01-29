/*
 * Sort a k-sorted array.
 */

#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <assert.h>

#define LEFT(x)		((x << 1) + 1)
#define RIGHT(x)	((x << 1) + 2)
#define PARENT(x)	((x & 1) ? (x >> 1) : (x >> 1) - 1)

typedef struct heap {
	int	*data;
	int	size;
	int	capacity;
} heap_t;

heap_t *
init_heap(int capacity)
{
	heap_t	*heap = malloc(sizeof(heap_t));

	heap->data = malloc(sizeof(int) * capacity);
	heap->capacity = capacity;
	heap->size = 0;
	return heap;
}

void
deinit_heap(heap_t *heap)
{

	free(heap->data);
	free(heap);
	return;
}

static void
swap(int *a, int *b)
{
	int c = *a;

	*a = *b;
	*b = c;
	return;
}

void
insert_minheap(heap_t *heap, int num)
{
	int	idx;

	heap->data[heap->size++] = num;
	idx = heap->size - 1;
	while(PARENT(idx) >= 0) {
		if(heap->data[PARENT(idx)] > heap->data[idx]) {
			swap(&heap->data[PARENT(idx)], &heap->data[idx]);
		} else {
			break;
		}
		idx = PARENT(idx);
	}
	return;
}

int
extract_min(heap_t *heap)
{
	int	result;
	int	idx = 0, nidx, lidx, ridx;

	if(heap->size == 0) {
		assert(0);
	}
	result = heap->data[0];
	swap(&heap->data[0], &heap->data[heap->size - 1]);
	heap->size--;
	while(idx < heap->size) {
		nidx = idx;
		if(LEFT(idx) < heap->size &&
			heap->data[LEFT(idx)] < heap->data[idx]) {
			nidx = LEFT(idx);
		}
		if(RIGHT(idx) < heap->size &&
			heap->data[RIGHT(idx)] < heap->data[nidx]) {
			nidx = RIGHT(idx);
		}
		if(idx != nidx) {
			swap(&heap->data[idx], &heap->data[nidx]);
		} else {
			break;
		}
		idx = nidx;
	}
	return result;
}

int
peek(heap_t *heap)
{

	return heap->data[0];
}

void
sort_ksort(int *arr, int n, int k)
{
	int	i, j;
	heap_t	*heap;

	/*
	 * This is O(1)
	 */

	heap = init_heap(k);

	/*
	 * This is O(k)
	 */

	for(i = 0; i < k; i++) {
		insert_minheap(heap, arr[i]);
	}

	/*
	 * This is O((n - k)logk)
	 */

	for(j = 0, i = k; i < n; i++, j++) {
		if(arr[i] < peek(heap)) {
			arr[j] = arr[i];
		} else {
			arr[j] = extract_min(heap);
			insert_minheap(heap, arr[i]);
		}
	}

	for(; j < n; j++) {
		arr[j] = extract_min(heap);
	}
	deinit_heap(heap);
	return;
}

int
main(int argc, char *argv[])
{
	//int k = 3, arr[] = {6, 5, 3, 2, 8, 10, 9};
	int k = 4, arr[] = {10, 9, 8, 7, 4, 70, 60, 50};
	int i, n = sizeof(arr)/sizeof(arr[0]);

	sort_ksort(arr, n, k);
	for(i = 0; i < n; i++) {
		printf(" %d ", arr[i]);
	}
	printf("\n");
	return 0;
}
