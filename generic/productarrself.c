/*
 * Product of array except itself.
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int* productExceptSelf(int* nums, int numsSize, int* returnSize){
	int i, j, *result = malloc(sizeof(int) * numsSize);
	int left, right;

	left = 1;
	result[0] = left;
	for(i = 1; i < numsSize; i++) {
		left *= nums[i - 1];
		result[i] = left;
	}

	right = 1;
	for(i = numsSize - 2; i >= 0; i--) {
		right *= nums[i + 1];
		result[i] *= right;
	}
	*returnSize = numsSize;
	return result;
}

int
main(int argc, char *argv[])
{

	int 	*result, arr[] = {1, 2, 3, 4};
	int	i, n;

	n = sizeof(arr)/sizeof(arr[0]);
	result = productExceptSelf(arr, n, &n);
	for(i = 0; i < n; i++) {
		printf(" %d ", result[i]);
	}
	printf("\n");
	return 0;
}
