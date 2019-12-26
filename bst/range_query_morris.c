/*
 * Range-query on a BST using in-order
 */

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

typedef struct bstnode {
	struct bstnode	*left;
	struct bstnode	*right;
	int		val;
} bstnode_t;

bstnode_t *
make_bstnode(int val)
{

	bstnode_t	*node = calloc(1, sizeof(bstnode_t));
	node->val = val;
	return node;
}

bstnode_t *
insert_bst(bstnode_t *root, int val)
{
	bstnode_t	*node = make_bstnode(val);
	bstnode_t	*current, *prev = NULL;

	if(root == NULL) {
		return node;
	}

	current = root;
	while(current) {
		if(current->val <= val) {
			prev = current;
			current = current->right;
			continue;
		}
		prev = current;
		current = current->left;
	}
	if(prev->val <= val) {
		prev->right = node;
	} else {
		prev->left = node;
	}
	return root;
}

void
range_query(bstnode_t *root, int low, int high)
{
	bstnode_t	*current, *left;

	current = root;
	while(current) {
		if(current->left == NULL) {
			if(low <= current->val && current->val <= high) {
				printf(" %d ", current->val);
			}
			if(current->val < high) {
				current = current->right;
			} else {
				break;
			}
		} else {
			left = current->left;
			while(left->right != NULL && left->right != current) {
				left = left->right;
			}
			if(left->right == NULL) {
				left->right = current;
				current = current->left;
			} else {
				left->right = NULL;
				if(low <= current->val && current->val <= high) {
					printf(" %d ", current->val);
				}
				if(current->val < high) {
					current = current->right;
				} else {
					break;
				}
			}
		}
	}
	return;
}

void
morris_inorder(bstnode_t *root)
{
	bstnode_t	*current, *left;

	current = root;
	while(current) {
		if(current->left == NULL) {

			/*
			 * There is no left child, so print the root's value,
			 * and go to right subtree.
			 */

			printf(" %d ", current->val);
			current = current->right;
		} else {

			/*
			 * Traverse until we find the right-most child in left subtree
			 * of current, that would be inorder predecessor of current.
			 * Link up current as right child of predecessor, traverse
			 * down the path of left of current.
			 * If we already did the link up and ended up at the current
			 * then we finished traversing left subtree, just print the
			 * current value and go to right sub-tree.
			 */

			left = current->left;
			while(left->right != NULL && left->right != current) {
				left = left->right;
			}
			if(left->right == NULL) {
				left->right = current;
				current = current->left;
			} else {
				left->right = NULL;
				printf(" %d ", current->val);
				current = current->right;
			}
		}	
	}
	return;
}

void
destroy_tree(bstnode_t *root)
{

	if(root == NULL) return;
	destroy_tree(root->left);
	destroy_tree(root->right);
	free(root);
	return;
}

#define MIN(A, B)	((A) < (B) ? (A) : (B))

int
main(int argc, char *argv[])
{
	bstnode_t	*root = NULL;
	int		i, *resultp = NULL, resultsz;
	int		low, high;

	srand(time(NULL));
	for(i = 0; i < 70; i++) {
		root = insert_bst(root, rand() % 100);
	}
	morris_inorder(root);
	printf("\n");
	low = rand() % 100;
	high = low + rand() % 100;
	printf("Range query results for range: [%d %d]:\n", low, high);	
	range_query(root, low, high);
	printf("\n");
	/*for(i = 0; i < resultsz; i++) {
		printf(" %d ", result[i]);
	}
	printf("\n");
	if(result) {
		free(result);
	} */
	destroy_tree(root);
	printf("\n");
	return 0;
}
