/*
 * Boundary traversal of a binary tree - more clever solution.
 */

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct treenode {
	struct treenode	*left;
	struct treenode *right;
	int		val;
} treenode_t;

void
doBoundaryTraversal(treenode_t *root, bool leftbound, bool rightbound)
{
	if(root == NULL) {
		return;
	}
	if(leftbound) {
		printf(" %d ", root->val);
	}
	if(!leftbound && !rightbound && root->left == NULL && root->right == NULL) {
		printf(" %d ", root->val);
	}
	doBoundaryTraversal(root->left, leftbound, rightbound && (root->right == NULL));
	doBoundaryTraversal(root->right, leftbound && (root->left == NULL), rightbound);
	if(rightbound) {
		printf(" %d ", root->val);
	}
	return;
}

void
boundaryTraversal(treenode_t *root)
{
	if(root == NULL) {
		return;
	}
	printf(" %d ", root->val);
	doBoundaryTraversal(root->left, true, false);
	doBoundaryTraversal(root->right, false, true);
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
	tn->right = make_treenode(3);

	tn->left->left = make_treenode(4);
	tn->left->right = make_treenode(5);

	tn->right->left = make_treenode(6);
	tn->right->right = make_treenode(7);
	
	tn->left->left->left = make_treenode(8);
	tn->left->left->right = make_treenode(9);
	tn->left->right->left = make_treenode(10);
	tn->left->right->right = make_treenode(11);

	tn->right->left->left = make_treenode(12);
	tn->right->left->right = make_treenode(13);
	tn->right->right->left = make_treenode(14);
	tn->right->right->right = make_treenode(15);

	boundaryTraversal(tn);
	return 0;
}

