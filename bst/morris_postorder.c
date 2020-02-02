/*
 * Morris postorder traversal
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
morris_postorder(bstnode_t *root)
{
	bstnode_t	*current, *pred;
	bstnode_t	dummy, *dummyp = &dummy;
	bstnode_t	*first, *middle, *last;

	/*
	 * If we assume there is no right child for a given tree, then
	 * printing the left child followed by root becomes a post-order
	 * traversal. So, let's create a dummy node and make the given tree
	 * as its left subtree.
	 */

	current = dummyp;
	current->left = root;
	current->right = NULL;
	while(current) {

		/*
		 * If there is no left sub-tree for this node, go to its
		 * right sub-tree.
		 */

		if(current->left == NULL) {
			current = current->right;
		} else {

			/*
			 * There is a left sub-tree for 'current'. We can find
			 * inorder predecessor for 'current' in its left
			 * sub-tree.
			 */

			pred = current->left;
			while(pred->right != NULL && pred->right != current) {
				pred = pred->right;
			}

			/*
			 * Now 'pred' is the inorder predecessor of 'current'.
			 * After pre-order traversing current's left sub-tree,
			 * we need to come to 'current' to continue, so link
			 * up pred and current, make pred's right to point
			 * to current. We knew that pred's right will be NULL.
			 * Unless, we already did this link-up in the previous
			 * iteration, now it's time to destroy that fake link.
			 */

			if(pred->right == NULL) {
				//printf("Temp link established between %d and %d\n",
				//       pred->val, current->val);

				pred->right = current;
				current = current->left;
			} else {
				//printf("Temp link destroyed between %d and %d\n",
				//       pred->val, current->val);

				/*
				 * Destroy the fake link between this node and its
				 * successor.
				 */

				first = current;
				middle = current->left;
				while(middle != current) {
					last = middle->right;
					middle->right = first;
					first = middle;
					middle = last;
				}
				first = current;
				middle = pred;
				while(middle != current) {
					printf(" %d ", middle->val);
					last = middle->right;
					middle->right = first;
					first = middle;
					middle = last;
				}
				pred->right = NULL;

				/*
				 * We pre-order traversed 'current' and its
				 * left-subtree, time to move onto its right
				 * sub-tree.
				 */

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
	int		arr[] = {4, 2, 1, 3, 6, 5, 7};

	srand(time(NULL));
	for(i = 0; i < 7; i++) {
		root = insert_bst(root, arr[i]);//rand() % 77);
	}
	morris_postorder(root);
	printf("\n");

#if 0
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
#endif
	destroy_tree(root);
	return 0;
}
