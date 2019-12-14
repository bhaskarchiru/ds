#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <time.h>
#include <string.h>

struct bstnode {
	int	val;
	struct	bstnode *left;
	struct	bstnode *right;
};

struct bstnode *
makenewnode(int val)
{
	struct bstnode *node;
	node = malloc(sizeof (struct bstnode));
	node->left = node->right = NULL;
	node->val = val;
	return node;
}

void
preorder(struct bstnode *root)
{
	if (root != NULL) {
		printf(" %d ", root->val);
	}
	if (root->left) {
		preorder(root->left);
	}
	if (root->right) {
		preorder(root->right);
	}
	return;
}

void
postorder(
	struct bstnode	*root)
{
	if (root == NULL) {
		return;
	}
	if (root->left) {
		postorder(root->left);
	}
	if (root->right) {
		postorder(root->right);
	}
	printf(" %d ", root->val);
	return;
}

void
inorder(
	struct bstnode	*root)
{
	if (root->left) {
		inorder(root->left);
	}
	if (root) {
		printf(" %d ", root->val);
	}
	if (root->right) {
		inorder(root->right);
	}
	return;
}

struct bstnode * 
dequeue(struct bstnode **Q, int *frontp)
{

	(*frontp)++;
	return Q[*frontp - 1];
}

void
enqueue(struct bstnode **Q, struct bstnode *node, int *rearp)
{

	Q[*rearp] = node;
	(*rearp)++;	
	return;	
}

struct bstnode **
create_queue(int size, int *frontp, int *rearp)
{
	struct bstnode **Q;

	Q = (struct bstnode **)malloc(sizeof (struct bstnode *) * size);
	*front = 0;
	*rear = 0;
	return Q;
}

/*
 * Essentially a Breadth-First Traversal.
 */

void
levelorder(struct bstnode *root, int size)
{
	struct bstnode **Q;
	int		front, rear;
	
	if (root == NULL) {
		return;
	}
	Q = create_queue(size, &front, &rear);
	while (root) {
		printf (" %d ", root->val);
		if (root->left) {
			enqueue(Q, root->left, &rear);
		}
		if (root->right) {
			enqueue(Q, root->right, &rear);
		}
		root = dequeue(Q, &front);
	}
	return;
}

void
insert_node(struct bstnode **rootRef, int val)
{
	struct bstnode *root, *prev;
	if ((root = *rootRef) == NULL) {
		root = makenewnode(val);
		*rootRef = root;
		return;
	}
	
	while (root != NULL) {
		prev = root;
		if (root->val < val) {
			root = root->right;
		} else {
			root = root->left;
		}
	}
	if (prev->val < val) {
		prev->right = makenewnode(val);
	} else {
		prev->left = makenewnode(val);
	}
	return;
}

void
morris_inorder(struct bstnode *root)
{
	struct bstnode *current, *pre;

	if(root == NULL) {
		return;
	}
	current = root;
	while(current) {
		if(current->left == NULL) {
			printf(" %d ", current->val);
			current = current->right;
		} else {
			pre = current->left;
			while(pre->right != NULL && pre->right != current) {
				pre = pre->right;
			}
			if(pre->right == NULL) {
				pre->right = current;
				current = current->left;
			} else {
				pre->right = NULL;
				printf(" %d ", current->val);
				current = current->right;
			}
		}
	}
	return;
}	

int
main(int argc, char *argv[])
{
	struct bstnode *root = NULL;
	int N, *arr, i = 0;
	
	N= atoi(argv[1]);
	arr = (int *)malloc(sizeof (int) * N);
	for (; i < N; i++) {
		arr[i] = atoi(argv[i+2]);
	}
	for (i = 0; i < N; i++) {
		insert_node(&root, arr[i]);
	}
	printf("Inorder:\n");
	inorder(root);
	printf("\n");		
	
	printf("Morris Inorder:\n");
	inorder(root);
	printf("\n");		

	printf("Preorder:\n");
	preorder(root);
	printf("\n");		
	
	printf("postorder:\n");
	postorder(root);
	printf("\n");		
	
	printf("Levelorder:\n");
	levelorder(root, N);
	printf("\n");
	return 0;
}
