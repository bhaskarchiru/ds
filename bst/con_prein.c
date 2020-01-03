/*
 * 105. Construct Binary Tree from Preorder and Inorder Traversal
 */

#include <stdio.h>
#include <stdlib.h>

struct TreeNode {
	int val;
	struct TreeNode *left;
	struct TreeNode *right;
};

struct TreeNode *
make_treenode(int val)
{
	struct TreeNode *node = malloc(sizeof(struct TreeNode));
	node->val = val;
	node->left = node->right = NULL;
	return node;
}

int
find_node_byval(int *arr, int val, int low, int high)
{
	int	i, residx = -1;

	for(i = low; i <= high; i++) {
		if(arr[i] == val) {
			residx = i;
			break;
		}
	}
	return residx;
}

struct TreeNode *
doBuildTree(int *pre, int plow, int phigh, int *in, int ilow, int ihigh)
{
	int		rootidx;
	int		leftsize;
	struct TreeNode *root;

	printf("plow: %d phigh: %d ilow: %d ihigh: %d\n", plow, phigh, ilow, ihigh);
	if(ilow > ihigh) {
		return NULL;
	}
	root = make_treenode(pre[plow]);
	if(ilow == ihigh) {
		return root;
	}
	rootidx = find_node_byval(in, pre[plow], ilow, ihigh);
	leftsize = rootidx - ilow;
	root->left = doBuildTree(pre, plow + 1, plow + leftsize, in, ilow, rootidx - 1);
	root->right = doBuildTree(pre, plow + leftsize + 1, phigh, in, rootidx + 1, ihigh);
	return root;
}

struct TreeNode*
buildTree(int* preorder, int preorderSize, int* inorder, int inorderSize)
{

	return doBuildTree(preorder, 0, preorderSize - 1, inorder, 0, inorderSize - 1);
}

void
preorder(struct TreeNode *root)
{
	if(root) {
		printf(" %d ", root->val);
		preorder(root->left);
		preorder(root->right);
	}
	return;
}

int
main(int argc, char *argv[])
{
	int	pre[] = {3, 9, 20, 15, 7};
	int	in[] = {9, 3, 15, 20, 7};
	struct TreeNode	*root;

	root = buildTree(pre, 5, in, 5);
	preorder(root);
	printf("\n");
	return 0;
}	
