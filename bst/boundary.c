/*
 * Boundary traversal of a binary tree
 */

#include <stdio.h>
#include <stdlib.h>

typedef struct treenode {
	struct treenode	*left;
	struct treenode *right;
	int		val;
} treenode_t;
void
rightBoundaryTraversal(treenode_t *root)
{
	if(root == NULL) {
		return;
	}
	if(root->right != NULL) {
		rightBoundaryTraversal(root->right);
		printf(" %d ", root->val);
		return;
	}
	if(root->left != NULL) {
		rightBoundaryTraversal(root->left);
		printf(" %d ", root->val);
	}
	return;
}

void
leftBoundaryTraversal(treenode_t *root)
{
	if(root == NULL) {
		return;
	}
	if(root->left) {
		printf(" %d ", root->val);
		leftBoundaryTraversal(root->left);
		return;
	}
	if(root->right) {
		printf(" %d ", root->val);
		leftBoundaryTraversal(root->right);
	}
	return;
}

void
printLeaves(treenode_t *root)
{
	if(root == NULL) {
		return;
	}
	if(root->left == NULL && root->right == NULL) {
		printf(" %d ", root->val);
		return;
	}
	printLeaves(root->left);
	printLeaves(root->right);
	return;
}

void
boundaryTraversal(treenode_t *root)
{
	if(root == NULL) {
		return;
	}
	printf(" %d ", root->val);
	leftBoundaryTraversal(root->left);
	printLeaves(root->left);
	printLeaves(root->right);
	rightBoundaryTraversal(root->right);
	printf("\n");
	return;
}

treenode_t *
make_treenode(int val)
{
	treenode_t	*tn;

	tn = malloc(sizeof(treenode_t));
	tn->left = tn->right = NULL;
	tn->val = val;
	return tn;
}

int
main(int argc, char *argv[])
{
	treenode_t	*tn = make_treenode(1);

	tn->left = make_treenode(2);
	//tn->right = make_treenode(3);

	tn->left->left = make_treenode(4);
	//tn->left->right = make_treenode(5);

	//tn->right->left = make_treenode(6);
	//tn->right->right = make_treenode(7);
	
	//tn->left->left->left = make_treenode(8);
	tn->left->left->right = make_treenode(9);
	//tn->left->right->left = make_treenode(10);
	//tn->left->right->right = make_treenode(11);

	//tn->right->left->left = make_treenode(12);
	//tn->right->left->right = make_treenode(13);
	//tn->right->right->left = make_treenode(14);
	//tn->right->right->right = make_treenode(15);

	boundaryTraversal(tn);
	return 0;
}

