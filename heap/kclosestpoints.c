
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>

#define PARENT(x)	((x & 1) ? (x >> 1) : (x >> 1) - 1)
#define LEFT(x)		((x << 1) + 1)
#define RIGHT(x)	((x << 1) + 2)

typedef struct heapnode {
	int	x;
	int	y;
	double	distance;	
} heapnode_t;

typedef struct heap {
	heapnode_t	*data;
	int		size;
	int		capacity;
} heap_t;

heap_t *
init_heap(int capacity)
{
	heap_t	*h = calloc(1, sizeof(heap_t));
	h->capacity = capacity;
	h->data = calloc(1, sizeof(heapnode_t) * h->capacity);
	return h;
}

void
deinit_heap(heap_t *heap)
{

	free(heap->data);
	free(heap);
	return;
}

void
swap(heapnode_t *hn1, heapnode_t *hn2)
{
	heapnode_t	hn;
	memcpy(&hn, hn1, sizeof(heapnode_t));
	memcpy(hn1, hn2 ,sizeof(heapnode_t));
	memcpy(hn2, &hn, sizeof(heapnode_t));
	return;
}

heapnode_t *
extract_max(heap_t *h)
{
	int		idx, nidx, lidx, ridx;
	heapnode_t	*result;

	if(h->size == 0) {
		return NULL;
	}
	swap(&h->data[0], &h->data[h->size - 1]);
	result = &h->data[h->size - 1];
	h->size--;
	idx = 0;
	while(idx < h->size) {
		nidx = idx;
		lidx = LEFT(idx);
		ridx = RIGHT(idx);
		if(lidx < h->size &&
			h->data[lidx].distance > h->data[nidx].distance) {
			nidx = lidx;
		}
		if(ridx < h->size &&
		   h->data[ridx].distance > h->data[nidx].distance) {
		   	nidx = ridx;
		}
		if(idx != nidx) {
			swap(&h->data[idx], &h->data[nidx]);
		} else {
			break;
		}
		idx = nidx;
	}
	return result;
}

void
insert(heap_t *h, int x, int y, double distance)
{
	int		idx;
	heapnode_t	*hn, *phn;

	hn = &h->data[h->size];
	hn->x = x;
	hn->y = y;
	hn->distance = distance;
	h->size++;
	idx = h->size - 1;
	while(PARENT(idx) >= 0) {
		hn = &h->data[idx];
		phn = &h->data[PARENT(idx)];
		if(phn->distance < hn->distance) {
			swap(hn, phn);
		} else {
			break;
		}
		idx = PARENT(idx);
	}
	return;
}

heapnode_t *
peek(heap_t *h)
{

	return &h->data[0];
}

/*
 * Euclidean distance of this point from origin.
 */

double
calc_distance(int x, int y)
{

	return sqrt(x * x + y * y);
}

/*
 * Return an array of arrays of size *returnSize.
 * The sizes of the arrays are returned as *returnColumnSizes array.
 * Note: Both returned array and *columnSizes array must be malloced,
 * assume caller calls free().
 */

int **
kClosest(int points[][2], int pointsSize, int *pointsColSize, int K,
	 int *returnSize, int ** returnColumnSizes)
{
	int		x, y;
	int		*columns;
	int		**results, i;
	heap_t		*heap;
	double		distance;
	heapnode_t	*hn;

	heap = init_heap(K);
	for(i = 0; i < K; i++) {
		x = points[i][0];
		y = points[i][1];
		distance = calc_distance(x, y);
		insert(heap, points[i][0], points[i][1], distance);
	}
	for(i = K; i < pointsSize; i++) {
		x = points[i][0];
		y = points[i][1];
		distance = calc_distance(x, y);
		hn = peek(heap);
		if(hn->distance > distance) {
			(void)extract_max(heap);
			insert(heap, x, y, distance);
		}
	}
	*returnSize = K;
	results = (int **)calloc(1, sizeof(int *) * K);
	columns = (int *)calloc(1, sizeof(int) * K);
	for(i = 0; i < K; i++) {
		results[i] = (int *)calloc(1, sizeof(int) * 2);
		columns[i] = 2;
	}
	for(i = 0; i < K; i++) {
		hn = extract_max(heap);
		results[i][0] = hn->x;
		results[i][1] = hn->y;
	}
	*returnColumnSizes = columns;
	deinit_heap(heap);
	return results;
}

int
main(int argc, char *argv[])
{
	//int	points[][2] = {{3, 3}, {5, -1}, {-2, 4}};
	//int	points[][2] = {{6, 10}, {-3, -3}, {-2, 5}, {0, 2}};
	int	points[][2] = {{-5, 4}, {-3, 2}, {0, 1}, {-3, 7}, {-2, 0},
				{-4, 6}, {0, -5}};

	int	colsize = 2;
	int	*colsizes;
	int	**results, resultsz = 0, ii;

	results = kClosest(points, 7, &colsize, 6, &resultsz, &colsizes);
	for(ii = 0; ii < resultsz; ii++) {
		printf("[%d %d]\t", results[ii][0], results[ii][1]);
	}
	printf("\n");
	for(ii = 0; ii < resultsz; ii++) {
		free(results[ii]);
	}
	free(results);
	free(colsizes);
	return 0;
}
