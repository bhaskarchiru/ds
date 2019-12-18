/*
 * Height of a tree using BFS.
 */

#include <stdio.h>
#include <stdlib.h>

typedef struct treenode {
	struct treenode *left;
	struct treenode *right;
	int		val;
} treenode_t;

typedef struct qnode {
	struct qnode	*next;
	struct treenode	*tn;
	int		 lvl;
} qnode_t;

typedef struct queue {
	qnode_t	*next;
	int	numcnt;
} queue_t;

treenode_t *
make_treenode(int val)
{

	treenode_t	*tn;
	tn = malloc(sizeof(treenode_t));
	tn->val = val;
	tn->left = tn->right = NULL;
	return tn;
}

qnode_t *
make_qnode(treenode_t *tn, int lvl)
{

	qnode_t	*qn = malloc(sizeof(qnode_t));
	qn->next = NULL;
	qn->tn = tn;
	qn->lvl = lvl;
	return qn;
}

queue_t *
init_queue()
{

	queue_t	*Q = calloc(1, sizeof(queue_t));
	return Q;
}

void
enqueue(queue_t *Q, treenode_t *tn, int lvl)
{
	qnode_t	*next, *qn = make_qnode(tn, lvl);

	if((next = Q->next) == NULL) {
		Q->next = qn;
		Q->numcnt++;
		return;
	}

	while((next->next != NULL)) {
		next = next->next;
	}
	next->next = qn;
	Q->numcnt++;
	return;
}

treenode_t *
dequeue(queue_t *Q, int *lvlp)
{
	treenode_t	*tn;
	qnode_t	*qn;

	if((qn = Q->next) == NULL) {
		return NULL;
	}
	Q->next = qn->next;
	tn = qn->tn;
	*lvlp = qn->lvl;
	free(qn);
	return tn;
}

void
deinit_queue(queue_t *Q)
{
	qnode_t	*qn;

	while((qn = Q->next) != NULL) {
		Q->next = qn->next;
		free(qn);
	}
	free(Q);
	return;
}

void
destroy_tree(treenode_t *root)
{
	if(root == NULL) return;
	destroy_tree(root->left);
	destroy_tree(root->right);
	free(root);
	return;
}

int
height(treenode_t *root)
{
	int		lvl = 0 ;
	queue_t		*Q;
	treenode_t	*tn;

	if(root == NULL) {
		return 0;
	}
	Q = init_queue();
	enqueue(Q, root, lvl);
	while((tn = dequeue(Q, &lvl)) != NULL) {
		if(tn->left != NULL) {
			enqueue(Q, tn->left, lvl + 1);
		}
		if(tn->right != NULL) {
			enqueue(Q, tn->right, lvl + 1);
		}
	}
	deinit_queue(Q);
	return lvl;
}

int
main(int argc, char *argv[])
{
	treenode_t	*root = make_treenode(1);

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
	root->right->right->left = make_treenode(15);
	
	root->right->right->left->left = make_treenode(15);
	root->right->right->left->left->left = make_treenode(15);

	printf("Height of the tree: %d\n", height(root));
	destroy_tree(root);
	return 0;
}
