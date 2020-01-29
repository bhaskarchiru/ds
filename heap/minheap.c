#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

#define INITIAL_CAPACITY	8

/*
 * Implementation of min-heap using array.
 */

#define LEFT(x)		((x << 1) + 1)
#define RIGHT(x)	((x << 1) + 2)
#define PARENT(x)	(((x) & 1) ? ((x) >> 1) : ((x) >> 1) - 1)


typedef struct minheap {
	int	*data;
	int	size;
	int	capacity;
} minheap_t;

minheap_t *
minheap_init(void)
{
	minheap_t	*minh = malloc(sizeof(minheap_t));

	minh->size = 0;
	minh->capacity = INITIAL_CAPACITY;
	minh->data = malloc(sizeof(int) * minh->capacity);
	return minh;
}

void
minheap_deinit(minheap_t *minh)
{

	free(minh->data);
	free(minh);
	return;
}

int
minheap_getmin(minheap_t *minh)
{

	if(minh->size > 0) {
		return minh->data[0];
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
minheap_extractmin(minheap_t *minh)
{
	int min, lowidx, idx, leftidx, rightidx;
	
	if(minh->size <= 0) {
		return INT_MIN;
	}

	min = minh->data[0];
	minh->data[0] = minh->data[minh->size - 1];
	minh->size--;
	idx = 0;
	while(idx < minh->size) {
		lowidx = idx;
		leftidx = LEFT(idx);
		rightidx = RIGHT(idx);
		if(leftidx < minh->size &&
		   minh->data[leftidx] < minh->data[lowidx]) {
			lowidx = leftidx;
		}
		if(rightidx < minh->size &&
		   minh->data[rightidx] < minh->data[lowidx]) {
			lowidx = rightidx;
		}
		if(lowidx != idx) {
		   	swap(&minh->data[lowidx], &minh->data[idx]);
		} else {
			break;
		}
		idx = lowidx;
	}
	return min;
}

void
minheap_insert(minheap_t *minh, int num)
{
	int	idx;

	if(minh->size == minh->capacity) {
		minh->capacity <<= 1;
		minh->data = realloc(minh->data, sizeof(int) * minh->capacity);
	}
	minh->data[minh->size++] = num;
	idx = minh->size - 1;
	while(PARENT(idx) >= 0) { 
		if(minh->data[idx] < minh->data[PARENT(idx)]) {
			swap(&minh->data[idx], &minh->data[PARENT(idx)]);
		} else {
			break;
		}
		idx = PARENT(idx);
	}
	return;
}

int
main(int argc, char *argv[])
{
	int		arr[] = {9, 4, 7, 13, 3, 6, 5, 2, 14, 11, 1};
	int		i, n;
	minheap_t	*minh;

	n = sizeof(arr)/sizeof(arr[0]);
	minh = minheap_init();
	for(i = 0; i < n; i++) {
		minheap_insert(minh, arr[i]);
		printf("Minimum: %d\n", minheap_getmin(minh));
	}
	printf("=========\n");
	for(i = 0; i < n; i++) {
		printf("Minimum: %d\n", minheap_extractmin(minh));
	}
	minheap_deinit(minh);
	return 0;
}
