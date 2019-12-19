
/*
 * Right-side view of a binary tree
 */

#include <stdio.h>
#include <stdlib.h>


/*
 * Definition for a binary tree node.
 */

struct TreeNode {
	int val;
	struct TreeNode *left;
	struct TreeNode *right;
};

typedef struct qnode {
	struct qnode    *next;
	struct TreeNode *tn;
	int             lvl;
} qnode_t;
					     
typedef struct queue {
	qnode_t *next;
	int     size;
} queue_t;
						     
queue_t *
init_queue()
{
	queue_t *Q = malloc(sizeof(queue_t));
	Q->next = NULL;
	Q->size = 0;
	return Q;
}
									     
void
deinit_queue(queue_t *Q)
{
	qnode_t *qn, *next;

	while((qn = Q->next) != NULL) {
		next = qn->next;
		Q->next = next;
		qn-> next = NULL;
		free(qn);
	}
	free(Q);
	return;
}
																     
qnode_t *
make_qnode(struct TreeNode *tn, int lvl)
{

	qnode_t *qn = malloc(sizeof(qnode_t));
	qn->next = NULL;
	qn->tn = tn;
	qn->lvl = lvl;
	return qn;
}

void
enqueue(queue_t *Q, struct TreeNode *node, int lvl)
{
	qnode_t *current, *qn = make_qnode(node, lvl);

	if((current = Q->next) == NULL) {
		Q->next = qn;
		Q->size++;
		return;
	}
	while(current->next != NULL) current = current->next;
	current->next = qn;
	Q->size++;
	return; 
}

struct TreeNode *
dequeue(queue_t *Q, int *lvlp)
{
	qnode_t *qn;
	struct TreeNode *tn;
	
	if(Q->next == NULL) return NULL;
	qn = Q->next;
	Q->next = qn->next;
	Q->size--;
	qn->next = NULL;
	tn = qn->tn;
	*lvlp = qn->lvl;
	free(qn);
	return tn;
}


/**
 * Note: The returned array must be malloced, assume caller calls free().
 */
int * rightSideView(struct TreeNode* root, int* returnSize){
	int     i, lvlsize, lvl;
	int     *result, idx = 0;
	size_t  resultsz = 8;
	queue_t *Q;
	struct TreeNode *tn;

	if(root == NULL) {
		*returnSize = 0;
		return NULL;
	}
	Q = init_queue();
	enqueue(Q, root, 0);
	result = malloc(sizeof(int) * resultsz);
	while(1) {
		if((lvlsize = Q->size) == 0) break;
		for(i = 0; i < lvlsize; i++) {
			tn = dequeue(Q, &lvl);
			if(tn->left) {
				enqueue(Q, tn->left, lvl + 1);
			}
			if(tn->right) {
				enqueue(Q, tn->right, lvl + 1);
			}
			if(i == lvlsize - 1) {
				if(idx == resultsz - 1) {
					resultsz <<= 1;
					result = realloc(result, resultsz);
				}
				result[idx++] = tn->val;
			}
		}
	}
	deinit_queue(Q);
	*returnSize = idx;
	return result;
}

struct TreeNode *
make_treenode(int val)
{

	struct TreeNode *tn = malloc(sizeof(struct TreeNode));
	tn->left = tn->right = NULL;
	tn->val = val;
	return tn;
}

int
main(int argc, char *argv[])
{
	int	*result = NULL, i, returnsize;

	struct TreeNode	*root = make_treenode(1);
	root->left = make_treenode(2);
	root->right = make_treenode(3);
	root->left->right = make_treenode(5);
	root->right->right = make_treenode(4);
	root->right->right->left = make_treenode(7);
	root->right->right->right = make_treenode(11);
	root->left->right->left = make_treenode(13);
	root->left->right->left->left = make_treenode(15);
	root->left->right->left->right = make_treenode(17);
	root->right->right->right->left = make_treenode(19);
	root->right->right->right->right = make_treenode(20);
	result = rightSideView(root, &returnsize);
	for(i = 0; i < returnsize; i++) {
		printf(" %d ", result[i]);
	}
	printf("\n");
	return 0;
}
