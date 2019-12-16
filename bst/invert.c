/*
 * Invert a binary tree
 */

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct treenode {
	struct treenode *left;
	struct treenode *right;
	int		val;
} treenode_t;

/*
 * Queue of treenodes
 */

typedef struct queue {
	treenode_t	**q_tnodes;
	int		q_rear;
	int		q_front;
	int		q_capacity;
} queue_t;

treenode_t *
make_treenode(int val)
{
	treenode_t	*tn;

	tn = malloc(sizeof(treenode_t));
	tn->left = tn->right = NULL;
	tn->val = val;
	return tn;
}

queue_t *
init_queue(int capacity)
{

	queue_t	*Q;

	Q = malloc(sizeof(queue_t));
	Q->q_tnodes = malloc(sizeof(treenode_t *) * capacity);
	Q->q_capacity = capacity;
	Q->q_rear = Q->q_front = -1;
	return Q;
}

void
deinit_queue(queue_t *Q)
{

	free(Q->q_tnodes);
	free(Q);
	return;
}

void
enqueue(queue_t *Q, treenode_t *node)
{
	int rear = ++Q->q_rear;

	*(Q->q_tnodes + rear) = node;
	if(Q->q_front == -1) {
		Q->q_front = Q->q_rear;
	}
	return;
}

treenode_t *
dequeue(queue_t *Q)
{
	treenode_t	*tn;
	if(Q->q_front == -1) {
		return NULL;
	}
	tn = *(Q->q_tnodes + Q->q_front);
	if(Q->q_front == Q->q_rear) {
		Q->q_front = -1;
		Q->q_rear = -1;
	} else {
		Q->q_front++;
	}
	return tn;
}

/*
 * Empty the treenodes into queue and return it.
 */

treenode_t **
empty_queue(queue_t *Q, int *listsz)
{
	int		idx;
	treenode_t	**list;

	if(Q->q_rear == -1) {
		*listsz = 0;
		return NULL;
	}
	*listsz = Q->q_rear - Q->q_front + 1;
	list = calloc(1, sizeof(treenode_t *) * *listsz);
	for(idx = 0; idx < *listsz; idx++) {
		list[idx] = dequeue(Q);
	}
	return list;
}

bool
is_empty(queue_t *Q)
{
	return Q->q_front == -1;
}

int
sizeOfTree(treenode_t	*root)
{

	if(root == NULL) {
		return 0;
	}
	return 1 + sizeOfTree(root->left) + sizeOfTree(root->right);
}

void
invert_tree(treenode_t *root)
{
	int		i, listsz, n = sizeOfTree(root);
	int		*valarr;
	queue_t		*Q;
	treenode_t	*node, **list;

	if(n == 0 || n == 1) {
		return;
	}
	Q = init_queue(n);
	enqueue(Q, root);
	while((list = empty_queue(Q, &listsz)) != NULL) {
		valarr = malloc(sizeof(int) * listsz);
		for(i = 0; i < listsz; i++) {
			node = list[i];
			valarr[n - i - 1] = node->val;
			if(node->left) {
				enqueue(Q, node->left);
			}
			if(node->right) {
				enqueue(Q, node->right);
			}
		}
		for(i = 0; i < listsz; i++) {
			node = list[i];
			node->val = valarr[i];
		}
	}
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
	
	tn->left->left->left = make_treenode(8);
	tn->left->left->right = make_treenode(9);
	tn->left->right->left = make_treenode(10);
	tn->left->right->right = make_treenode(11);
	tn->right->left->left = make_treenode(12);
	tn->right->left->right = make_treenode(13);
	tn->right->right->left = make_treenode(14);
	tn->right->right->right = make_treenode(15);

	invert_tree(tn);
	destroy_tree(tn);
	return 0;
}
