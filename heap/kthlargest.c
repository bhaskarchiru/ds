/*
 * Find kth largest element in given list of elements in O(nlogk) time
 * using minheap.
 */

#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

#define LEFT(X)	((X << 1) + 1)
#define RIGHT(X) ((X << 1) + 2)
#define PARENT(X) ((X & 1) ? (X >> 1) : ((X >> 1) - 1))

typedef struct heap {
	int	*data;
	size_t	size;
	size_t	capacity;
} heap_t;

heap_t *
init_heap(int capacity)
{
	heap_t	*h = malloc(sizeof(heap_t));
	h->data = malloc(sizeof(int) * capacity);
	h->size = 0;
	h->capacity = capacity;
	return h;
}

void
deinit_heap(heap_t *h)
{
	free(h->data);
	free(h);
	return;
}

void
swap(int *a, int *b)
{
	int	c = *a;
	*a = *b;
	*b = c;
	return;
}

void
insert(heap_t *h, int num)
{
	int	idx;

	h->data[h->size++] = num;
	idx = h->size - 1;
	while(PARENT(idx) >= 0) {
		if(h->data[idx] < h->data[PARENT(idx)]) {
			swap(&h->data[idx], &h->data[PARENT(idx)]);
		} else {
			break;
		}
		idx = PARENT(idx);
	}
	return;
}

int
extract(heap_t *h)
{
	int result, idx, lidx, leftidx, rightidx;
	if(h->size == 0) {
		return INT_MIN;
	}
	result = h->data[h->size - 1];
	if(h->size == 1) {
		h->size--;
		return result;
	}
	swap(&h->data[0], &h->data[h->size - 1]);
	h->size--;
	idx = lidx = 0;
	while(idx < h->size) {
		lidx = idx;
		leftidx = LEFT(lidx);
		if(leftidx < h->size && h->data[leftidx] < h->data[lidx]) {
			lidx = leftidx;
		}
		rightidx = RIGHT(idx);
		if(rightidx < h->size && h->data[rightidx] < h->data[lidx]) {
			lidx = rightidx;
		}
		if(lidx != idx) {
			swap(&h->data[lidx], &h->data[idx]);
		} else {
			break;
		}
		idx = lidx;
	}
	return result;
}

int
peek(heap_t *h)
{
	
	if(h->size > 0) {
		return h->data[0];
	}
	return INT_MIN;
}

int
findkthlargest(int *arr, int n, int k)
{
	int	i, result;
	heap_t	*heap;

	if(k > n) {
		return INT_MIN;
	}
	heap = init_heap(k);
	for(i = 0; i < k; i++) {
		insert(heap, arr[i]);
	}
	for(i = k; i < n; i++) {
		if(peek(heap) < arr[i]) {
			(void)extract(heap);
			insert(heap, arr[i]);
		}
	}
	result = peek(heap);
	deinit_heap(heap);
	return result;
}

int
main(int argc, char *argv[])
{
			// 1, 3, 4, 6, 7, 8, 9, 10, 11, 13, 18
	int	arr[] = {9, 1, 3, 7, 6, 4, 18, 13, 11, 10, 8};
	int	n, k;

	n = sizeof(arr)/sizeof(arr[0]);
	k = atoi(argv[1]);
	printf("%dth largest elment in array: %d\n",
		k, findkthlargest(arr, n, k));
	return 0;
}
