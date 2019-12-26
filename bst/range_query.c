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
	int	*result = NULL;

	if(root == NULL) {
		return; 			
	}
	if(low < root->val) {
		range_query(root->left, low, high);
	}
	if(low <= root->val && root->val <= high) {
		printf(" %d ", root->val);
	}
	if(root->val < high) {
		range_query(root->right, low, high);
	}
	return;
}
	

void
inorder(bstnode_t *root)
{
	if(root) {
		inorder(root->left);
		printf(" %d ", root->val);
		inorder(root->right);
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
	inorder(root);
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
