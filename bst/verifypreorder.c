
#include <stdio.h>
#include <stdbool.h>
#include <limits.h>
#include <assert.h>

/*
 * Given a result of pre-order results, return true if it's from BST.
 */


bool
doverifyPreorder(int *preorder, int low, int high, int min, int max)
{
	int i, root;

	printf("low: %d high: %d min: %d max: %d\n", low, high, min, max);
	if(low > high) {
		return true;
	}
	root = preorder[low];
	for(i = low + 1; i <= high; i++) {
		if(preorder[i] < min || preorder[i] > max) {
			return false;
		}
		if(preorder[i] > root) {
			return doverifyPreorder(preorder, low + 1, i - 1, min, preorder[low]) &&
				doverifyPreorder(preorder, i, high, preorder[low], max);
		}
	}
	return doverifyPreorder(preorder, low + 1, high, min, root);
}


bool verifyPreorder(int *preorder, int preorderSize)
{

	return doverifyPreorder(preorder, 0, preorderSize - 1, INT_MIN, INT_MAX);
}

int
main(int argc, char *argv[])
{

	int	preorder[] = {5, 2, 6, 1, 3};
	int	n = sizeof(preorder)/sizeof(preorder[0]);

	printf("Given preorder %s from a bst.\n",
	       verifyPreorder(preorder, n) ? "is" : "is not");
	return 0;
}
