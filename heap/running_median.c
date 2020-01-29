/*
 * 295. Find Median from Data Stream
 */

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <limits.h>

/*
 * Initial capacity of heap.
 */

#define HEAP_INITIAL_CAPACITY	8

#define LEFT(X)		((X << 1) + 1)
#define RIGHT(X)	((X << 1) + 2)
#define PARENT(X)	((X & 1) ? (X >> 1) : ((X >> 1) - 1))

enum {
	MAX_HEAP,
	MIN_HEAP
};

typedef struct heap {
	int	*data;
	int	capacity;
	int	size;
	int	typ;	/* 0 - max heap, 1 - min heap */
} heap_t;

typedef bool (cmpfunc_t)(int, int);

heap_t *
init_heap(int typ)
{
	heap_t	*h = malloc(sizeof(heap_t));
	h->capacity = HEAP_INITIAL_CAPACITY;
	h->data = malloc(sizeof(int) * h->capacity);
	h->size = 0;
	h->typ = typ;
	return h;
}

void
deinit_heap(heap_t *heap)
{

	free(heap->data);
	free(heap);
	return;
}

bool
greater(int A, int B)
{

	return A > B;
}

bool
lesser(int A, int B)
{

	return A < B;
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
insert(heap_t *heap, int num)
{
	int		idx;
	cmpfunc_t	*func;

	if(heap->typ == MIN_HEAP) {
		func = lesser;
	} else {
		func = greater;
	}
	if(heap->size == heap->capacity) {
		heap->capacity <<= 1;
		heap->data = realloc(heap->data, sizeof(int) * heap->capacity);
	}
	heap->data[heap->size++] = num;
	idx = heap->size - 1;
	while(PARENT(idx) >= 0) {
		if(func(heap->data[idx], heap->data[PARENT(idx)])) {
			swap(&heap->data[idx], &heap->data[PARENT(idx)]);
		} else {
			break;
		}
		idx = PARENT(idx);
	}
	return;
}

int
peek(heap_t *heap)
{
	if(heap->size == 0) {
		return INT_MIN;
	}
	return heap->data[0];
}

int
extract(heap_t *heap)
{
	int		result, idx, lidx, ridx, nidx;
	cmpfunc_t	*func;

	if(heap->size == 0) {
		return INT_MIN;
	}
	if(heap->typ == MIN_HEAP) {
		func = lesser;
	} else {
		func = greater;
	}
	result = heap->data[0];
	heap->data[0] = heap->data[heap->size - 1];
	heap->size--;
	idx = 0;
	while(idx < heap->size) {
		nidx = idx;
		lidx = LEFT(nidx);
		ridx = RIGHT(nidx);
		if(lidx < heap->size && func(heap->data[lidx], heap->data[nidx])) {
			nidx = lidx;
		}
		if(ridx < heap->size && func(heap->data[ridx], heap->data[nidx])) {
			nidx = ridx;
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
typedef struct {
	heap_t	*minheap;
	heap_t	*maxheap;
	double	median;
} MedianFinder;


/** initialize your data structure here. */

MedianFinder *
medianFinderCreate()
{
	MedianFinder *mf = malloc(sizeof(MedianFinder));
	mf->maxheap = init_heap(0);
	mf->minheap = init_heap(1);
	mf->median = 0;
	return mf;
}

void
rebalance(MedianFinder *obj)
{
	int	top;
	heap_t	*to, *from;

	if(obj->minheap->size > obj->maxheap->size) {
		from = obj->minheap;
		to = obj->maxheap;
	} else {
		from = obj->maxheap;
		to = obj->minheap;
	}
	top = extract(from);
	insert(to, top);
	return;
}

void
medianFinderAddNum(MedianFinder *obj, int num)
{

	/*
	 * If the given number is less than current median, this number will
	 * go into max-heap on the left, otherwise to min-heap.
	 *
	 * After finding a place for the current element, see if the heap
	 * sizes differe by more than 1, if yes, rebalance and re-calculate
	 * the median.
	 */

	if(obj->maxheap->size == 0 && obj->minheap->size == 0) {
		insert(obj->maxheap, num);
		obj->median = num;
		return;
	}
	if(num < (int)obj->median) {
		insert(obj->maxheap, num);
	} else {
		insert(obj->minheap, num);
	}
	if(obj->minheap->size - obj->maxheap->size < -1 ||
	   obj->minheap->size - obj->maxheap->size > 1) {
		rebalance(obj);
	}
	if(obj->minheap->size == obj->maxheap->size) {
		obj->median = (double)peek(obj->minheap) + (double)peek(obj->maxheap);
		obj->median /= 2.0;
	} else if(obj->minheap->size < obj->maxheap->size) {
		obj->median = (double)peek(obj->maxheap);
	} else {
		obj->median = (double)peek(obj->minheap);
	}
	return;
}

double
medianFinderFindMedian(MedianFinder *obj)
{

       return obj->median;
}

void
medianFinderFree(MedianFinder *obj)
{

	deinit_heap(obj->minheap);
	deinit_heap(obj->maxheap);
	free(obj);
	return;
}

int
main(int argc, char *argv[])
{
	int	arr[] = {11, 1, 9, 2, 3, 7, 18, 6, 4, 23, 15};
	int	i, n;
	MedianFinder	*mf;

	mf = medianFinderCreate();
	n = sizeof(arr)/sizeof(arr[0]);
	for(i = 0; i < n; i++) {
		medianFinderAddNum(mf, arr[i]);
		printf("Median: %f\n", medianFinderFindMedian(mf));
	}
	medianFinderFree(mf);
	return 0;
}
