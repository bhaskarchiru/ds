#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <time.h>
#include <string.h>

/*
 * Construct a Binary Search Tree from Pre-order output.
 */

struct bstnode {
	int		val;
	struct bstnode	*left;
	struct bstnode	*right;
};

void
print_inorder(
	struct bstnode *root)
{
	int	val;
	if (root->left) 
		print_inorder(root->left);
	printf(" %d ", val);
	if (root->right)
		print_inorder(root->right);
	return;
}

void
print_preorder(
	struct bstnode *root)
{
	if (root) 
		printf(" %d ", root->val);
	if (root->left)
		print_preorder(root->left);
	if (root->right)
		print_preorder(root->right);
	return;
}

struct bstnode *
makenewnode(int val) 
{
	struct bstnode *node = (struct bstnode *)malloc(sizeof (struct bstnode));
	node->left = node->right = NULL;
	node->val = val;
	return node;
}

/*
 * Recursively construct a binary search tree from given arr[low ... high]
 * Worst-case for this O(n^2).
 */

struct bstnode *
construct_bstutil(
	int	*arr,
	int	low,
	int	high)
{
	struct	bstnode *root;
	int	idx = 0;

	if (low > high) {
		return NULL;
	}
	if (low == high) {
		return  makenewnode(arr[low]);
	}
	for (idx = low + 1; idx <= high; idx++) {
		if (arr[idx] > arr[low]) break;
	}
	root = makenewnode(arr[low]);
	root->left = construct_bstutil(arr, low + 1, idx - 1);
	root->right = construct_bstutil(arr, idx, high);
	return root;
}

	

struct bstnode *
construct_bst(int *arr, int size)
{
	return construct_bstutil(arr, 0, size-1);
}

/*
 * This construction is O(n)
 */

struct bstnode *
construct_bstutil1(
	int	*arr,
	int	*idx,
	int	key,
	int 	min,
	int 	max,
	int	size)
{
	struct bstnode *root = NULL;
	if (*idx >= size) {
		return root;
	}
	if (key > min && key < max) {
		root = makenewnode(key);
		*idx = *idx + 1;
		if (*idx < size) {
			root->left = construct_bstutil1(arr, idx, arr[*idx], min, key, size);
			root->right = construct_bstutil1(arr, idx, arr[*idx], key, max, size);
		}  
	}
	return root;
}

struct bstnode *
construct_bst1(int *arr, int size)
{
	int idx = 0;
	return construct_bstutil1(arr, &idx, arr[idx], INT_MIN, INT_MAX, size);
} 
	
int
main(int argc, char *argv[])
{
	struct bstnode *root = NULL;
	struct bstnode *root1 = NULL;
	int size;
	int *a, i;
	
	size = atoi(argv[1]);
	a = (int *)malloc(sizeof (int));
	for (i = 0; i < size; i++) {
		a[i] = atoi(argv[i+2]);
	}
	root = construct_bst(a, size);
	print_inorder(root);
	printf("\n");
	print_preorder(root);
	printf("\n");
	root1 = construct_bst1(a, size);
	print_inorder(root1);
	printf("\n");
	return 0;
}	
