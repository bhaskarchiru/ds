
/*
 * level order traversal - recursive
 */

#include <stdio.h>
#include <stdlib.h>

#define MAX(a, b)	((a) > (b) ? (a) : (b))

typedef struct treenode {
	struct treenode *left;
	struct treenode *right;
	int		val;
} treenode_t;

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
height(treenode_t	*root)
{

	if(root == NULL) {
		return 0;
	}
	return 1 + MAX(height(root->left), height(root->right));
}

void
do_levelorder(treenode_t *root, int lvl)
{

	if(root == NULL) {
		return;
	}
	if(lvl == 1) {
		printf(" %d ", root->val);
	} else if(lvl > 1) {
		do_levelorder(root->left, lvl - 1);
		do_levelorder(root->right, lvl - 1);
	}
	return;
}

void
level_order(treenode_t *root)
{
	int	i, h = height(root);

	if(h == 0) {
		return;
	}
	for(i = 1; i <= h; i++) {
		do_levelorder(root, i);
	}
	printf("\n");
	return;
}

void
destroy_tree(treenode_t *root)
{

	if(root == NULL) {
		return;
	}
	destroy_tree(root->left);
	destroy_tree(root->right);
	free(root);
	return;
}

int
main(int argc, char *argv[])
{
	treenode_t	*tn;

	tn = make_treenode(1);
	tn->left = make_treenode(2);
	tn->right = make_treenode(3);
	tn->left->left = make_treenode(4);
	tn->left->right = make_treenode(5);
	tn->right->left = make_treenode(6);
	tn->right->right = make_treenode(7);
	level_order(tn);
	destroy_tree(tn);
	return 0;
}
