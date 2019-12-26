/*
 * Invert a binary tree
 */

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct TreeNode {
	struct TreeNode *left;
	struct TreeNode *right;
	int		val;
} treenode_t;

typedef struct qnode {
	struct qnode	*next;
	treenode_t	*tnode;
} qnode_t;

/*
 * Queue
 */

typedef struct queue {
	qnode_t		*head;
	int		size;
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
init_queue(void)
{

	return calloc(1, sizeof(queue_t));
}

void
deinit_queue(queue_t *Q)
{
	qnode_t	*current, *next;

	current = Q->head;
	while(current) {
		next = current->next;
		current->next = NULL;
		free(current);
		current = next;
	}
	free(Q);
	return;
}

qnode_t *
make_qnode(treenode_t *tnode)
{
	qnode_t	*qn = malloc(sizeof(qnode_t));
	qn->tnode = tnode;
	qn->next = NULL;
	return qn;
}

void
enqueue(queue_t *Q, treenode_t *tnode)
{
	qnode_t	*qn, *current;

	qn = make_qnode(tnode);
	if(Q->head == NULL) {
		Q->head = qn;
		Q->size++;
		return;
	}
	current = Q->head;
	while(current->next != NULL) current = current->next;
	current->next = qn;
	Q->size++;
	return;
}

treenode_t *
dequeue(queue_t *Q)
{
	qnode_t		*current, *next;
	treenode_t	*tn;

	if(Q->head == NULL) {
		return NULL;
	}

	current = Q->head;
	next = current->next;
	current->next = NULL;
	Q->head = next;
	Q->size--;
	tn = current->tnode;
	free(current);
	return tn;
}


bool
is_empty(queue_t *Q)
{
	return Q->size == 0;
}

void
level_order(treenode_t	*root)
{
	int		i, lvlsize;
	queue_t		*Q;
	treenode_t	*node;

	if(root == NULL) {
		return;
	}
	if(root->left == NULL &&  root->right == NULL) {
		return;
	}
	Q = init_queue();
	enqueue(Q, root);
	while(!is_empty(Q)) {
		lvlsize = Q->size;
		for(i = 0; i < lvlsize; i++) {
			node = dequeue(Q);
			printf(" %d ", node->val);
			if(node->left) {
				enqueue(Q, node->left);
			}
			if(node->right) {
				enqueue(Q, node->right);
			}
		}
	}
	deinit_queue(Q);
	return;
}

void
invert_tree(treenode_t *root)
{
	int		i, lvlsize;
	queue_t		*Q;
	treenode_t	*node, *left, *right;

	if(root == NULL) {
		return;
	}
	if(root->left == NULL &&  root->right == NULL) {
		return;
	}
	Q = init_queue();
	enqueue(Q, root);
	while(!is_empty(Q)) {
		lvlsize = Q->size;
		for(i = 0; i < lvlsize; i++) {
			node = dequeue(Q);
			left = node->left;
			right = node->right;
			node->right = left;
			node->left = right;
			if(node->left) {
				enqueue(Q, node->left);
			}
			if(node->right) {
				enqueue(Q, node->right);
			}
		}
	}
	deinit_queue(Q);
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

	printf("Level order before invert\n");
	level_order(tn);
	printf("\n");
	invert_tree(tn);
	printf("Level order after invert\n");
	level_order(tn);
	printf("\n");
	destroy_tree(tn);
	return 0;
}
