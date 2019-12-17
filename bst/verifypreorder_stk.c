
/*
 * verify if a given preorder traversal output is from a binary search tree.
 */

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <limits.h>

bool
verifyPreorder(int *preorder, int n)
{
	int *stack;
	int top = -1;
	int lower_bound = INT_MIN;

	if(n < 2) {
		return true;
	}
	stack = malloc(n);
	for(int i = 0; i < n; i++) {
		if(top == -1 || preorder[i] < preorder[i - 1]) {
			if(preorder[i] < lower_bound) {
				return false;
			}
			stack[++top] = preorder[i];
		} else {
			while(top >= 0 && stack[top] < preorder[i]) {
				lower_bound = stack[top--];
			}
			stack[++top] = preorder[i];
		}
	}
	return true;
}


int
main(int argc, char *argv[])
{

	int preorder[] = {10, 30, 9};
	int n = sizeof(preorder)/sizeof(preorder[0]);

	printf("Given preorder %s from a bst.\n",
	       verifyPreorder(preorder, n) ? "is" : "is not");
	return 0;
}
