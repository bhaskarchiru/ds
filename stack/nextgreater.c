/*
 * Next greater element in array.
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int *
nextGreaterElements(int* nums, int numsSize, int* returnSize)
{
	int i, stack[numsSize];
	int *result, top = -1;
	        
		    
	*returnSize = numsSize;
	if(numsSize == 0 || nums == NULL) {
		return NULL;
	}
	result = malloc(sizeof(int) * numsSize);
	memset(result, -1, sizeof(int) * numsSize);
	for(i = 0; i < numsSize; i++) {
		while(top != -1 && nums[stack[top]] < nums[i])
			result[stack[top--]] = nums[i];
		stack[++top] = i;
	}
	while(top != -1) {
		result[stack[top--]] = -1;
	}
	return result;
}

int
main(int argc, char *argv[])
{
	int	i, n, *result, returnSize, arr[] = {2, 1, 4, 5, 3, 6, 7};

	n = sizeof(arr)/sizeof(arr[0]);
	result = nextGreaterElements(arr, n, &returnSize);
	for(i = 0; i < n; i++) {
		printf(" %d ", result[i]);
	}
	printf("\n");
	return 0;
}
