/*
 * 1130. Minimum Cost Tree From Leaf Values
 */

#include <stdio.h>
#include <stdlib.h>

/*
 * Return maximum value in the given array in the range [low ... high]
 */

int
maximum_of(int *arr, int low, int high)
{
	int i, max = arr[low];

	for(i = low + 1; i <= high; i++) {
		if(arr[i] > max) {
			max = arr[i];
		}
	}
	return max;
}

int
doMCTFromLeafValues(int *arr, int low, int high, int depth)
{
	int i, k, n, min = 0, result;

	for(i = 0; i < depth; i++) {
		printf("\t");
	}
	printf("MCT low: %d high: %d\n", low, high);
	if(arr == NULL) {
		return 0;
	}
	n = high - low + 1;
	if(n == 1) {
		return arr[low];
	}
	if(n == 2) {
		//printf("\tFor n = 2, low: %d high: %d, result: %d\n",
		//     low, high, arr[low] * arr[high]);
		return arr[low] * arr[high];
	}
	if(n == 3) {
		min = arr[low] * maximum_of(arr, low + 1, high) + arr[low + 1] * arr[high];
		result = arr[low] * arr[low + 1] + maximum_of(arr, low, low + 1) * arr[high];
		//printf("\tFor n = 3, low: %d high: %d, result1: %d, result2: %d\n",
		//	low, high, min, result);
		if(result < min) {
			min = result;
		}
		return min;
	}
														        
															       
	for(i = low; i < high; i++) {
																           
		/*
		 * Partition into [low, i] [i + 1, high]
		 */

		for(k = 0; k < depth; k++) printf("\t");
		printf("Partition: [%d %d][%d %d]\n", low, i, i + 1, high);
		result = maximum_of(arr, low, i) * maximum_of(arr, i + 1, high) +
			 doMCTFromLeafValues(arr, low, i, depth + 1) +
			 doMCTFromLeafValues(arr, i + 1, high, depth + 1);
		for(k = 0; k < depth; k++) printf("\t");
		printf("Partition: [%d %d][%d %d] result: %d\n", low, i, i + 1, high, result);
		if(i == low || min > result) {
			min = result;
		}
	}

	return min;
}

int mctFromLeafValues(int* arr, int arrSize)
{

	return doMCTFromLeafValues(arr, 0, arrSize - 1, 0);
}

int
main(int argc, char *argv[])
{
	int	n, arr[] = {15, 13, 5, 3, 15};

	n = sizeof(arr)/sizeof(arr[0]);
	printf("Minimum cost tree from leaf values: %d\n", mctFromLeafValues(arr, n));
	return 0;
}


