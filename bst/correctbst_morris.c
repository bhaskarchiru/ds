#include <stdio.h>
#include <stdlib.h>

/*
 * Two nodes of a BST are swapped by mistake, correct them.
 */

typedef struct bstnode {
	struct bstnode *left;
	struct bstnode *right;
	int		val;
} bstnode_t;

bstnode_t *
make_bstnode(int val)
{

	bstnode_t *node = calloc(1, sizeof(bstnode_t));
	node->val = val;
	return node;
}

void
correct_bst(bstnode_t *root)
{
	int		val;
	bstnode_t	*current, *rightmost, *prev;
	bstnode_t	*first, *last;

	prev = first = last = NULL;
	current = root;
	while(current) {
		if(current->left == NULL) {
			if(prev && prev->val > current->val) {
				if(first == NULL) {
					first = prev;
				}	
				last = current;
			}
			prev = current;
			current = current->right;
		} else {
			rightmost = current->left;
			while(rightmost->right != NULL && rightmost->right != current) {
				rightmost = rightmost->right;
			}
			if(rightmost->right == NULL) {
				rightmost->right = current;
				current = current->left;
			} else {
				rightmost->right = NULL;
				if(prev && prev->val > current->val) {
					if(first) {
						first = prev;
					}
					last = current;
				}
				prev = current;
				current = current->right;
			}
		}
	}
	if(first && last) {
		val = first->val;
		first->val = last->val;
		last->val = val;
	}
	return;
}

void
print_inorder(bstnode_t *root)
{

	if(root) {
		print_inorder(root->left);
		printf(" %d ", root->val);
		print_inorder(root->right);
	}
	return;
}

void
print_postorder(bstnode_t *root)
{

	if(root) {
		print_postorder(root->left);
		print_postorder(root->right);
		printf(" %d ", root->val);
	}
	return;
}

int
main(int argc, char *argv[])
{

	bstnode_t	*root;

	root = make_bstnode(8);
	root->left = make_bstnode(5);
	root->right = make_bstnode(6);
	root->left->left = make_bstnode(4);
	root->left->right = make_bstnode(11);
	root->right->left = make_bstnode(10);
	root->right->right = make_bstnode(13);

	printf("Before fixing\n");
	printf("Inorder: ");
	print_inorder(root);
	printf("\n");
	printf("Postorder: ");
	print_postorder(root);
	printf("\n");
	correct_bst(root);
	printf("After fixing\n");
	printf("Inorder: ");
	print_inorder(root);
	printf("\n");
	printf("Postorder: ");
	print_postorder(root);
	printf("\n");
	return 0;
}
