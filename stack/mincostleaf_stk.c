#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

#define MIN(A, B)	((A) < (B) ? (A) : (B))

int
mctFromLeafValues(int *arr, int arrSize)
{
	int	i, val, *stack, top = -1, result = 0;

	if(arr == NULL || arrSize == 1) {
		return 0;
	}
	stack = malloc(sizeof(int) * arrSize + 1);
	stack[++top] = INT_MAX;
	for(i = 0; i < arrSize; i++) {
		while(stack[top] <= arr[i]) {
			val = stack[top--];
			printf("result = %d + %d * %d\n",
				result, val, MIN(stack[top], arr[i]));
			result += val * MIN(stack[top], arr[i]);
		}
		stack[++top] = arr[i];
	}
	for(i = 2; i <= top; i++) {
		printf("result = %d + %d * %d\n",
			result, stack[i], stack[i - 1]);
		result += stack[i] * stack[i - 1];
	}
	free(stack);
	return result;

}

/*
 * Minimum cost tree from leaf values using stack
 */

int
main(int argc, char *argv[])
{

	int	n, result, arr[] = {6, 2, 4};

	n = sizeof(arr)/sizeof(arr[0]);
	result = mctFromLeafValues(arr, n);
	printf("Minimum cost tree from leaf values: %d\n", result);
	return 0;
}
