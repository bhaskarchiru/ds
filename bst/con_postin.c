/*
 * 106. Construct Binary Tree from Postorder and Inorder Traversal
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
doBuildTree(int *post, int plow, int phigh, int *in, int ilow, int ihigh)
{
	int		rootidx;
	int		leftsize;
	struct TreeNode *root;

	//printf("plow: %d phigh: %d ilow: %d ihigh: %d\n", plow, phigh, ilow, ihigh);
	if(ilow > ihigh) {
		return NULL;
	}
	root = make_treenode(post[phigh]);
	if(ilow == ihigh) {
		return root;
	}
	rootidx = find_node_byval(in, post[phigh], ilow, ihigh);
	leftsize = rootidx - ilow;
	root->left = doBuildTree(post, plow, plow + leftsize -1, in, ilow, rootidx - 1);
	root->right = doBuildTree(post, plow + leftsize, phigh - 1, in, rootidx + 1, ihigh);
	return root;
}

struct TreeNode*
buildTree(int* postorder, int postorderSize, int* inorder, int inorderSize)
{

	return doBuildTree(postorder, 0, postorderSize - 1, inorder, 0, inorderSize - 1);
}

void
postorder(struct TreeNode *root)
{
	if(root) {
		postorder(root->left);
		postorder(root->right);
		printf(" %d ", root->val);
	}
	return;
}

int
main(int argc, char *argv[])
{
	int	post[] = {9, 15, 7, 20, 3};
	int	in[] = {9, 3, 15, 20, 7};
	struct TreeNode	*root;

	root = buildTree(post, 5, in, 5);
	postorder(root);
	printf("\n");
	return 0;
}	
