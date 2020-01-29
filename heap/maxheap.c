#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <limits.h>

#define INITIAL_CAPACITY	8

/*
 * Implementation of max-heap using array.
 */

#define LEFT(x)		((x << 1) + 1)
#define RIGHT(x)	((x << 1) + 2)
#define PARENT(x)	(((x) & 1) ? ((x) >> 1) : ((x) >> 1) - 1)

typedef bool (cmpfunc_t)(int, int);

typedef struct maxheap {
	int		*data;
	int		size;
	int		capacity;
	cmpfunc_t	*compare;
} maxheap_t;
	
maxheap_t *
maxheap_init(cmpfunc_t	*func)
{
	maxheap_t	*maxh = malloc(sizeof(maxheap_t));

	maxh->size = 0;
	maxh->capacity = INITIAL_CAPACITY;
	maxh->data = malloc(sizeof(int) * maxh->capacity);
	maxh->compare = func;
	return maxh;
}

void
maxheap_deinit(maxheap_t *maxh)
{

	free(maxh->data);
	free(maxh);
	return;
}

int
maxheap_getmin(maxheap_t *maxh)
{

	if(maxh->size > 0) {
		return maxh->data[0];
	}
	return INT_MIN;
}

void
swap(int *a, int *b)
{
	int	c = *a;
	*a = *b;
	*b = c;
	return;
}

int
maxheap_extractmin(maxheap_t *maxh)
{
	int min, lowidx, idx, leftidx, rightidx;
	
	if(maxh->size <= 0) {
		return INT_MIN;
	}

	min = maxh->data[0];
	maxh->data[0] = maxh->data[maxh->size - 1];
	maxh->size--;
	idx = 0;
	while(idx < maxh->size) {
		lowidx = idx;
		leftidx = LEFT(idx);
		rightidx = RIGHT(idx);
		if(leftidx < maxh->size &&
		   maxh->compare(maxh->data[leftidx], maxh->data[lowidx])) {
			lowidx = leftidx;
		}
		if(rightidx < maxh->size &&
		   maxh->compare(maxh->data[rightidx], maxh->data[lowidx])) {
			lowidx = rightidx;
		}
		if(lowidx != idx) {
		   	swap(&maxh->data[lowidx], &maxh->data[idx]);
		} else {
			break;
		}
		idx = lowidx;
	}
	return min;
}

void
maxheap_insert(maxheap_t *maxh, int num)
{
	int	idx;

	if(maxh->size == maxh->capacity) {
		maxh->capacity <<= 1;
		maxh->data = realloc(maxh->data, sizeof(int) * maxh->capacity);
	}
	maxh->data[maxh->size++] = num;
	idx = maxh->size - 1;
	while(PARENT(idx) >= 0) { 
		if(maxh->compare(maxh->data[idx], maxh->data[PARENT(idx)])) {
			swap(&maxh->data[idx], &maxh->data[PARENT(idx)]);
		} else {
			break;
		}
		idx = PARENT(idx);
	}
	return;
}

/*
 * For max-heap, comparator function will return true if A > B
 */

bool
greater(int A, int B)
{

	return A > B;
}

int
main(int argc, char *argv[])
{
	int		arr[] = {9, 4, 7, 13, 3, 6, 5, 2, 14, 11, 1};
	int		i, n;
	maxheap_t	*maxh;

	n = sizeof(arr)/sizeof(arr[0]);
	maxh = maxheap_init(greater);
	for(i = 0; i < n; i++) {
		maxheap_insert(maxh, arr[i]);
		printf("Maximum: %d\n", maxheap_getmin(maxh));
	}
	printf("=========\n");
	for(i = 0; i < n; i++) {
		printf("Maximum: %d\n", maxheap_extractmin(maxh));
	}
	maxheap_deinit(maxh);
	return 0;
}
