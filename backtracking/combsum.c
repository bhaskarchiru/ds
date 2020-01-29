#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct alist {
	int	**arrays;
	int	*arraysizes;
	int	size;
	int	capacity;
} alist_t;

alist_t *
arraylist_init(int capacity)
{
	alist_t *alist;

	alist = (alist_t *)calloc(1, sizeof(alist_t));
	alist->arrays = (int **)calloc(1, sizeof(int *) * capacity);
	alist->capacity = capacity;
	alist->arraysizes = (int *)calloc(1, sizeof(int) * capacity);
	alist->size = 0;
	return alist;
}

void
arraylist_deinit(alist_t *alist)
{
	int	ii;

	if(alist->arraysizes) {
		free(alist->arraysizes);
	}
	for(ii = 0; ii < alist->size; ii++) {
		if(alist->arrays[ii]) {
			free(alist->arrays[ii]);
		}
	}
	free(alist->arrays);
	free(alist);
	return;
}

void
arraylist_add(alist_t *alist, int *arr, int arrsize)
{
	int	ii;
	int	*dst;

	if(alist->size + 1 == alist->capacity) {
		alist->capacity <<= 1;
		alist->arrays = realloc(alist->arrays,
					sizeof(int *) * alist->capacity);
		alist->arraysizes = realloc(alist->arrays,
					    sizeof(int) * alist->capacity);
	}
	dst = alist->arrays[alist->size] = calloc(1, sizeof(int) * arrsize);
	for(ii = 0; ii < arrsize; ii++) {
		dst[ii] = arr[ii];
	}
	alist->arraysizes[alist->size] = arrsize;
	alist->size++;
	return;
}

void
doCombinationSum(int *start, int *end, int target, alist_t *alist,
		 int *run, int idx, int *runszp)
{
	int	ii, num, runsz = *runszp;

	if(start >= end) {
		return;
	}
	if(*start > target) {
		return;
	}
	if(target < 0) {
		return;
	}

	/*
	 * At each element we've two choices:
	 *  - Either If the first element is a divisor of target, then just add
	 * such a result.
	 */

	num = target / *start;
	if(idx + num + 1 == runsz) {
		runsz += num + 1;
		run = realloc(run, sizeof(int) * runsz);
		*runszp = runsz;
	}
	for(ii = 0; ii < num; ii++) {
		run[idx + ii] = *start;
	}
	if(target % (*start) == 0) {
		arraylist_add(alist, run, idx + num + 1);
		return;
	}
	doCombinationSum(start++, end, target % (*start),
			 alist, run, idx, runszp);
	run[idx] = *start;
	doCombinationSum(start++, end, target - *start,
			 alist, run, idx + 1, runszp);
	return;
}

void
reset(int *a, int sz)
{
	int	ii;

	for(ii = 0; ii < sz; ii++) {
		a[ii] = 0;
	}
	return;
}

/*
 * Return an array of arrays of size *returnSize.
 * The sizes of the arrays are returned as *returnColumnSizes array.
 * Note: Both returned array and *columnSizes array must be malloced,
 *       assume caller calls free().
 */

int **
combinationSum(int *candidates, int candidatesSize, int target,
		int *returnSize, int **returnColumnSizes)
{
	int	i, *run, asz;
	int	**result;
	alist_t	*alist;

	alist = arraylist_init(8);
	run = (int *)calloc(1, sizeof(int) * 8);
	asz = 8;
	for(i = 0; i < candidatesSize; i++) {
		if(candidates[i] <= target) {
			doCombinationSum(candidates + i, candidates + candidatesSize,
					 target, alist, run, 0, &asz);
		}
		reset(run, asz);
	}
	*returnSize = alist->size;
	result = (int **)calloc(1, sizeof(int *) * alist->size);
	for(i = 0; i < alist->size; i++) {
		result[i] = alist->arrays[i];
		alist->arrays[i] = NULL;
	}
	*returnColumnSizes = alist->arraysizes;
	alist->arraysizes = NULL;
	arraylist_deinit(alist);
	return result;
}

int
main(int argc, char *argv[])
{
	int	candidates[] = {2, 3, 5};
	int	target = 8;

	int	n, *columnsizes;
	int	*result, **results, resultsz, ii, jj;

	n = sizeof(candidates)/sizeof(candidates[0]);
	results = combinationSum(candidates, n, target, &resultsz, &columnsizes);
	for(ii = 0; ii < resultsz; ii++) {
		result = results[ii];
		for(jj = 0; jj < columnsizes[ii]; jj++) {
			printf("%d ", result[jj]);
		}
		printf("\n");
	}
	return 0;
}
