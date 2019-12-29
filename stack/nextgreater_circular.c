/*
 * 503. Next Greater Element II
 * Next greater element in circular array.
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int *
nextGreaterElements(int* nums, int numsSize, int* returnSize)
{
	int i, stack[2 * numsSize + 1];
	int *result, top = -1;
	        
		    
	*returnSize = numsSize;
	if(numsSize == 0 || nums == NULL) {
		return NULL;
	}
	result = malloc(sizeof(int) * numsSize);
	memset(result, -1, sizeof(int) * numsSize);
	for(i = 0; i < numsSize * 2; i++) {
		while(top != -1 && nums[stack[top]] < nums[i % numsSize])
			result[stack[top--]] = nums[i % numsSize];
		printf("top: %d\n", top);
		stack[++top] = i % numsSize;
	}
	return result;
}

int
main(int argc, char *argv[])
{
	int	i, n, *result, returnSize, arr[] = {5, 4, 3, 2, 1};

	n = sizeof(arr)/sizeof(arr[0]);
	result = nextGreaterElements(arr, n, &returnSize);
	for(i = 0; i < n; i++) {
		printf(" %d ", result[i]);
	}
	printf("\n");
	return 0;
}
