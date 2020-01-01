
/*
 * Right-side view of a binary tree
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#define MAX_NODE_LENGTH	5
#define NODE_SEPARATOR	","
#define NULL_NODE	"null"

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

bool
is_empty(queue_t *Q)
{

	return Q->size == 0;
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

struct TreeNode *
deserialize(char *data)
{
	int		lvl = 0, i, lvlsize;
	char		*nodeval;
	queue_t		*Q;
	struct TreeNode	*root = NULL, *node, dummy;

	if(data == NULL) {
		return NULL;
	}
	Q = init_queue();
	nodeval = strtok(data, NODE_SEPARATOR);
	root = make_treenode(atoi(nodeval));
	enqueue(Q, root, lvl);
	while(!is_empty(Q)) {
		lvlsize = Q->size;
		for(i = 0; i < lvlsize; i++) {
			node = dequeue(Q, &lvl);
			if(node == &dummy) {
				printf(" null ");
				continue;
			} else {
				printf(" %d ", node->val);
			}
			nodeval = strtok(NULL, NODE_SEPARATOR);
			if(!strcmp(nodeval, NULL_NODE)) {
				enqueue(Q, &dummy, lvl + 1);
				node->left = NULL;
			} else {
				node->left = make_treenode(atoi(nodeval));
				enqueue(Q, node->left, lvl + 1);
			}
			nodeval = strtok(NULL, NODE_SEPARATOR);
			if(!strcmp(nodeval, NULL_NODE)) {
				enqueue(Q, &dummy, lvl + 1);
				node->right = NULL;
			} else {
				node->right = make_treenode(atoi(nodeval));
				enqueue(Q, node->right, lvl + 1);
			}
		}
		printf("\n");
	}
	deinit_queue(Q);
	return root;
}

int
main(int argc, char *argv[])
{
	int	*result = NULL, i, returnsize;
	char	values[] = "-64,"
			   "12,18,"
			   "-4,-53,null,76,"
			   "null,-51,null,null,-93,3,"
			   "null,-31,47,null,3,53,"
			   "-81,33,4,null,-51,-44,-60,11,"
			   "null,null,null,null,78,null,-35,-64,26,-81,-31,27,60,74,"
			   "null,null,8,-38,47,12,-24,null,-59,-49,-11,-51,67,null,null,null,null,null,"
			   "null,null,-67,null,-37,-19,10,-55,72,null,null,null,-70,17,-4,null,null,null,null,null,"
			   "null,null,3,80,44,-88,-91,null,48,-90,-30,null,null,90,-34,37,null,null,"
			   "73,-38,-31,-85,-31,-96,null,null,-18,67,34,72,null,-17,-77,null,56,-65,-88,-53,null,null,"
			   "null,-33,86,null,81,-42,null,null,98,-40,70,-26,24,null,null,null,null,92,72,-27,null,null,null,null,null,null,-67,null,null,null,null,null,"
			   "null,null,-54,-66,-36,null,-72,null,null,43,null,null,null,-92,-1,-98,null,null,null,null,null,null,null,39,-84,null,null,null,"
			   "null,null,null,null,null,null,null,null,null,null,-93,null,null,null,98";
	struct TreeNode	*root;
	
	root = deserialize(values);

	/*
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
	*/
	result = rightSideView(root, &returnsize);
	for(i = 0; i < returnsize; i++) {
		printf(" %d ", result[i]);
	}
	printf("\n");
	return 0;
}
