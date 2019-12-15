/*
 * Zig-zag traversal of a binary tree using recursion.
 *
 *		   1
 *	     2            3
 *       4      5      6      7
 *    8   9  10   11 12 13  14 15
 *
 *   1 3 2 4 5 6 7 15 14 13 12 11 10 9 8
 */

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

struct TreeNode {
	int	val;
	struct TreeNode	*left;
	struct TreeNode *right;
};

struct TreeNode *
make_treenode(int val)
{

	struct TreeNode *tn;
	tn = malloc(sizeof(struct TreeNode));
	tn->val = val;
	tn->left = tn->right = NULL;
	return tn;
}

#define MAX(a, b)	((a) > (b) ? (a) : (b))

int
height(struct TreeNode *root)
{

	if(root == NULL) {
		return 0;
	}
	return 1 + MAX(height(root->left), height(root->right));
}

void
print_level(struct TreeNode *root, int level, bool dir)
{

	if(root == NULL) {
		return;
	}
	if(level == 1)  {
		printf(" %d ", root->val);
	} else if(level > 1) {
		if(dir) {
			print_level(root->left, level - 1, dir);
			print_level(root->right, level - 1, dir);
		} else {
			print_level(root->right, level - 1, dir);
			print_level(root->left, level - 1, dir);
		}
	}
	return;
}

void
zigzagLevelOrder(struct TreeNode *root)
{
	int	i, h;
	bool	dir;

	if(root == NULL) {
		return;
	}
	h = height(root);
	dir = true;
	for(i = 1; i <= h; i++) {
		print_level(root, i, dir);
		dir = !dir;
	}
	printf("\n");
	return;
}

int
main(int argc, char *argv[])
{

	struct TreeNode *root;

	root = make_treenode(1);
	root->left = make_treenode(2);
	root->right = make_treenode(3);

	root->left->left = make_treenode(4);
	root->left->right = make_treenode(5);
	root->right->left = make_treenode(6);
	root->right->right = make_treenode(7);

	root->left->left->left = make_treenode(8);
	root->left->left->right = make_treenode(9);
	root->left->right->left = make_treenode(10);
	root->left->right->right = make_treenode(11);
	root->right->left->left = make_treenode(12);
	root->right->left->right = make_treenode(13);
	root->right->right->left = make_treenode(14);
	root->right->right->right  = make_treenode(15);

	zigzagLevelOrder(root);
	
	return 0;
}

