/*
 * 1130. Minimum Cost Tree From Leaf Values
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX(A, B)	((A) > (B) ? (A) : (B))

/*
 * Memo-ization table - contains 2 2-D arrays
 *   sum[low][high] - Minimum cost tree from leaf values
 *			  in the range low...high
 *   max[low][high] - Maximum of the leaf values in
 *			  the range low...high
 */

typedef struct mct {
	int	*sum;
	int	*max;
	int	nrow;
	int	ncol;
} mct_t;

mct_t *
mct_init(int nrow, int ncol)
{

	mct_t *mct = malloc(sizeof(mct_t));
	mct->nrow = nrow;
	mct->ncol = ncol;
	mct->sum = malloc(sizeof(int) * nrow * ncol);
	mct->max = malloc(sizeof(int) * nrow * ncol);
	memset(mct->sum, -1, sizeof(int) * nrow * ncol);
	memset(mct->max, -1, sizeof(int) * nrow * ncol);
	return mct;
}

void
mct_deinit(mct_t *mct)
{

	free(mct->sum);
	free(mct);
	return;
}

int
mct_getsum(mct_t *mct, int rownum, int colnum)
{

	return *(mct->sum + rownum * mct->ncol + colnum);
}

void
mct_putsum(mct_t *mct, int rownum, int colnum, int val)
{

	*(mct->sum + rownum * mct->ncol + colnum) = val;
	return;
}

int
mct_getmax(mct_t *mct, int rownum, int colnum)
{

	return *(mct->max + rownum * mct->ncol + colnum);
}

void
mct_putmax(mct_t *mct, int rownum, int colnum, int val)
{

	*(mct->max + rownum * mct->ncol + colnum) = val;
	return;
}

int
doMCTFromLeafValues(int *arr, int low, int high, mct_t *mct)
{
	int i, k, n, min = 0, result;

	if(arr == NULL) {
		return 0;
	}
	n = high - low + 1;
	if(n == 1) {
		mct_putsum(mct, low, high, 0);
		return 0;
	}
	if((result = mct_getsum(mct, low, high)) != -1) {
		return result;
	}
	for(i = low; i < high; i++) {

		/*
		 * Partition into [low, i] [i + 1, high]
		 */

		result = mct_getmax(mct, low, i) * mct_getmax(mct, i + 1, high) +
			 doMCTFromLeafValues(arr, low, i, mct) +
			 doMCTFromLeafValues(arr, i + 1, high, mct);
		if(i == low || min > result) {
			min = result;
		}
	}
	mct_putsum(mct, low, high, min);
	return min;
}

int mctFromLeafValues(int* arr, int arrSize)
{
	int	i, j, max, result;
	mct_t	*mct;

	mct = mct_init(arrSize, arrSize);
	for(i = 0; i < arrSize; i++) {
		mct_putmax(mct, i, i, arr[i]);
		for(j = i + 1; j < arrSize; j++) {
			max = mct_getmax(mct, i, j - 1);
			max = MAX(max, arr[j]);
			mct_putmax(mct, i, j, max);
		}
	}
	result = doMCTFromLeafValues(arr, 0, arrSize - 1, mct);
	mct_deinit(mct);
	return result;
}

int
main(int argc, char *argv[])
{
	int	n, arr[] = {6, 2, 4};//15, 13, 5, 3, 15};

	n = sizeof(arr)/sizeof(arr[0]);
	printf("Minimum cost tree from leaf values: %d\n", mctFromLeafValues(arr, n));
	return 0;
}


