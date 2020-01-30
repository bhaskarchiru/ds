/*
 * Count nodes in a complete binary tree.
 *
 * In a complete binary tree every level, except possibly the last, is
 * completely filled, and all nodes in the last level are as far left
 * as possible.
 */

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

struct TreeNode {
	struct TreeNode	*left;
	struct TreeNode *right;
	int		val;
};

struct TreeNode *
make_treenode(int val)
{
	struct TreeNode *node = calloc(1, sizeof(struct TreeNode));

	node->val = val;
	return node;
}

int
depth(struct TreeNode	*root)
{
	int	 d = -1;

	while(root) {
		d++;
		root = root->left;
	}
	return d;
}

/*
 * Check the existence of a leaf, return true if exists.
 */

bool
check_leaf(struct TreeNode *root, int idx, int n)
{
	int		i;
	struct TreeNode	*current;

	current = root;
	for(i = n - 1; i >= 0; i--) {
		if((idx >> i) & 0x1) {
			current = current->right;
		} else {
			current = current->left;
		}
	}
	return current != NULL;
}

int
count_nodes(struct TreeNode *root)
{
	int	i, d, numleaves;
	int	numinternal;
	int	low, high, mid;
	bool	midleaf;

	if(root == NULL) {
		return 0;
	}
	d = depth(root);
	numinternal = (1 << d) - 1;
	if(d == 0) {
		return numinternal;
	}

	/*
	 * Maximum number of leaves possible.
	 */

	numleaves = 1 << d;

	/*
	 * Do linear search to know which one is the last leaf.
	 */

#if 0
	for(i = 0; i < numleaves; i++) {
		if(!check_leaf(root, i, d)) break;
	}
	return numinternal + i;
#endif

	/*
	 * Binary search - Find the index first NULL leaf.
	 */

	low = 0;
	high = numleaves - 1;
	while(low <= high) {
		mid = low + (high - low) / 2;
		midleaf = check_leaf(root, mid, d);

		/*
		 * If a leaf is not present at mid index and is present
		 * at one index before that, then 'mid' is our answer.
		 */

		if(!midleaf &&
		   (mid == 0 || check_leaf(root, mid - 1, d))) {
		   return numinternal + mid;
		} else if(!midleaf) {

			/*
			 * If a leaf is not present at mid index,
			 * then NULL leaf will be on left side of mid.
			 */

			high = mid - 1;
		} else {
			low = mid + 1;
		}
	}

	/*
	 * If we're out of loop, that means all leaves are present.
	 */

	return numinternal + numleaves; 
}

int
main(int argc, char *argv[])
{
	
	struct TreeNode	*root = make_treenode(1);

	root->left = make_treenode(2);
	root->right = make_treenode(3);
	root->left->left = make_treenode(4);
	root->left->right = make_treenode(5);
	root->right->left = make_treenode(6);
	#if 0
	root->right->right = make_treenode(7);
	root->left->left->left = make_treenode(8);
	root->left->left->right = make_treenode(9);
	root->left->right->left = make_treenode(10);
	root->left->right->right = make_treenode(11);
	root->right->left->left = make_treenode(12);
	root->right->left->right = make_treenode(13);
	root->right->right->left = make_treenode(14);
	root->right->right->right = make_treenode(15);
	#endif
	printf("Number of nodes: %d\n", count_nodes(root));
	return 0;
}
