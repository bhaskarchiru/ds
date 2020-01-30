/*
 * Print the leaves of a perfect binary tree with O(1) space.
 *
 * Perfect binary tree means - every node except the leaf nodes have two 
 * children and all the leaves are at same level.
 */

#include <stdio.h>
#include <stdlib.h>

struct TreeNode {
	struct TreeNode	*left;
	struct TreeNode *right;
	int		val;
};

struct TreeNode *
make_bstnode(int val)
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

void
print_leaf(struct TreeNode *root, int idx, int n)
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
	printf(" %d ", current->val);
	return;
}

void
print_leaves(struct TreeNode *root)
{
	int	i, d, numleaves;

	if(root == NULL) {
		return;
	}
	d = depth(root);
	numleaves = 1 << d;
	for(i = 0; i < numleaves; i++) {
		print_leaf(root, i, d);
	}
	printf("\n");
	return;
}

int
main(int argc, char *argv[])
{
	
	struct TreeNode	*root = make_bstnode(1);

	root->left = make_bstnode(2);
	root->right = make_bstnode(3);
	root->left->left = make_bstnode(4);
	root->left->right = make_bstnode(5);
	root->right->left = make_bstnode(6);
	root->right->right = make_bstnode(7);
	root->left->left->left = make_bstnode(8);
	root->left->left->right = make_bstnode(9);
	root->left->right->left = make_bstnode(10);
	root->left->right->right = make_bstnode(11);
	root->right->left->left = make_bstnode(12);
	root->right->left->right = make_bstnode(13);
	root->right->right->left = make_bstnode(14);
	root->right->right->right = make_bstnode(15);

	print_leaves(root);
	printf("Depth of the tree: %d\n", depth(root));
	return 0;
}
