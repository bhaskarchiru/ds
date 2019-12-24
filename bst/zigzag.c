
/*
 * zig-zag order traversal - using queue 
 */

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define MAX(a, b)	((a) > (b) ? (a) : (b))

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

int
height(treenode_t *root)
{
	if(root == NULL) {
		return 0;
	}
	return 1 + MAX(height(root->left), height(root->right));
}

/*
 * Return zig-zag order traversal results in an array of arrays. 
 *   numlvl - Number of levels
 *   lvlsizes - Number of nodes in each level
 */

int **
zigzag_order(treenode_t *root, int *numlvlp, int **lvlsizesp)
{
	int		i, j, h, listsz, n;
	int		**resultp;
	int		*printarr, *lvlsizes;
	bool		dir = false;
	queue_t		*Q;
	treenode_t	*node, **list;

	if(root == NULL) {
		*numlvlp = 0;
		*lvlsizesp = NULL;
		return NULL;
	}
	h = height(root);
	resultp = (int **)malloc(sizeof(int *) * h);
	lvlsizes = (int *)malloc(sizeof(int) * h);
	if(h == 1) {
		lvlsizes[0] = 1;
		resultp[0] = (int *)malloc(sizeof(int));
		resultp[0][0] = root->val;
		goto out;
	}

	Q = init_queue(sizeOfTree(root));
	enqueue(Q, root);
	j = 0;
	while((list = empty_queue(Q, &listsz)) != NULL) {
		lvlsizes[j] = listsz;
		printarr = resultp[j] = malloc(sizeof(int) * listsz);
		for(i = 0; i < listsz; i++) {
			node = list[i];
			if(dir) {
				printarr[listsz - i - 1] = node->val;
			} else {
				printarr[i] = node->val;
			}
			if(node->left) {
				enqueue(Q, node->left);
			}
			if(node->right) {
				enqueue(Q, node->right);
			}
		}
		j++;
		dir = !dir;
	}

out:
	*lvlsizesp = lvlsizes;
	*numlvlp = h;
	return resultp;
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
	int		**result;
	int		*total;
	int		numlvls;
	int		*lvlsizes = NULL;
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

	result = zigzag_order(tn, &numlvls, &lvlsizes);
	for(int i = 0; i < numlvls; i++) {
		for(int j = 0; j < lvlsizes[i]; j++) {
			printf(" %d ", result[i][j]);
		}
		printf("\n");
	}
	destroy_tree(tn);
	return 0;
}
