/*
 * Lowest common ancestor of given two nodes in a binary tree
 * Uses DFS
 */

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <assert.h>

struct TreeNode
{
	struct TreeNode	*left;
	struct TreeNode	*right;
	int		val;
};

typedef struct snode {
	struct TreeNode *sn_tnode;
	int             sn_status;
} snode_t;

typedef struct stack {
	snode_t *stk_data;  /* Arrary of stack nodes */
	int     stk_asz;    /* Allocated size of stk_data */
	int     stk_top;    /* Top of the stack */
} stack_t;

enum {
	UNEXPLORED = 1,
	LEFTVISITED,
	RIGHTVISITED
};

stack_t *
init_stack(void)
{
	stack_t *s;
	s = malloc(sizeof(stack_t));
	s->stk_top = -1;
	s->stk_asz = 8;
	s->stk_data = malloc(sizeof(snode_t) * s->stk_asz);
	return s;
}

void
deinit_stack(stack_t *s)
{

	free(s->stk_data);
	free(s);
	return;
}

void
push(stack_t *s, struct TreeNode *tn, int status)
{
	snode_t *snode;
        
	if(s->stk_top == -1) {
		snode = &s->stk_data[++s->stk_top];
		snode->sn_tnode = tn;
		snode->sn_status = status;
		return;
	}
	if(s->stk_top == s->stk_asz - 1) {
		s->stk_asz <<= 1;
		s->stk_data = realloc(s->stk_data, sizeof(snode_t) * s->stk_asz);
	}
	snode = &s->stk_data[++s->stk_top];
	snode->sn_tnode = tn;
	snode->sn_status = status;
	return;
}

struct TreeNode *
pop(stack_t *s, int *statusp)
{
	snode_t *sn;
	struct TreeNode *tn;

	if(s->stk_top == -1) {
		return NULL;
	}
	sn = &s->stk_data[s->stk_top];
	s->stk_top--;
	tn = sn->sn_tnode;
	if(statusp) {
		*statusp = sn->sn_status;
	}
	return tn;
}

struct TreeNode *
top(stack_t *s, int *statusp)
{
	snode_t		*sn;
	struct TreeNode *tn;

	sn = &s->stk_data[s->stk_top];
	if(statusp) {
		*statusp = sn->sn_status;
	}
	return sn->sn_tnode;
}

void
up_status(stack_t *s)
{
	snode_t	*sn;

	if(s->stk_top == -1) {
		return;
	}
	sn = &s->stk_data[s->stk_top];
	sn->sn_status++;
	return;
}

bool
is_empty(stack_t *s)
{

	return s->stk_top == -1;
}

struct TreeNode **
empty_stack_into_path(stack_t *s, int *pathsz)
{
	int		i;
	struct TreeNode *tn, **path;
	        
	*pathsz = s->stk_top + 1;
	path = malloc(sizeof(struct TreeNode *) * *pathsz);
	for(i = *pathsz - 1; i >= 0; i--) {
		tn = pop(s, NULL);
		path[i] = tn;
	}
	return path;
}

struct TreeNode **
construct_path(struct TreeNode *root, struct TreeNode *node, int *pathsz)
{
	bool    found = false;
	int     status;
	stack_t *s;
	struct TreeNode *current, **path;
		    
	s = init_stack();
	push(s, root, UNEXPLORED);
	while(!is_empty(s)) {
		current = top(s, &status);
		if(current->val == node->val) {
						            
			/*
			 * Found the node we're looking for.
			 */
			
			found = true;
			break;
		}
		switch(status) {
		case UNEXPLORED:
			if(current->left != NULL) {
				up_status(s);
				push(s, current->left, UNEXPLORED);
			} else if(current->right != NULL) {
				up_status(s);
				push(s, current->right, UNEXPLORED);
			} else {
				(void)pop(s, NULL);
			}
			break;

		case LEFTVISITED:
			if(current->right != NULL) {
				up_status(s);
				push(s, current->right, UNEXPLORED);
			} else {
				(void)pop(s, NULL);
			}
			break;
			
		case RIGHTVISITED:
			(void)pop(s, NULL);
			break;    
		}
	}
	
	if(!found) {
		deinit_stack(s);
		*pathsz = 0;
		return NULL;
	}
	path = empty_stack_into_path(s, pathsz);
	deinit_stack(s);
	return path;
}

struct TreeNode *
lowestCommonAncestor(struct TreeNode* root, struct TreeNode* p, struct TreeNode* q)
{
    
	/*
	 * Do Depth First Traversal from root till node to figure out the path from node 'p' to
	 * node 'root'. Likewise, for node 'q'.
	 * 
	 * Traverse the paths thus constructed until they diverge, last point of their divergence
	 * is LCA.
	 */
				          
					      
	struct TreeNode **p_path, **q_path, *lca = NULL;
	int             idx = 0, p_pathsz, q_pathsz;
						          
	p_path = construct_path(root, p, &p_pathsz);
	q_path = construct_path(root, q, &q_pathsz);
	
	while(idx < p_pathsz && idx < q_pathsz) {
		if(p_path[idx] != q_path[idx]) {
			break;
		}
		lca = p_path[idx];
		idx++;
	}
	return lca;
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
	struct TreeNode  *lca, *root = make_treenode(3);
	struct TreeNode	 *node1, *node2;

	root->left = make_treenode(5);
	root->right = make_treenode(1);
	root->left->left = make_treenode(6);
	root->left->right = node1 = make_treenode(2);
	root->left->right->left = make_treenode(7);
	root->left->right->right = node2 = make_treenode(4);
	root->right->left = make_treenode(0);
	root->right->right = make_treenode(8);

	lca = lowestCommonAncestor(root, node1, node2);
	printf("LCA of %d and %d is %d\n",
		node1->val, node2->val, lca->val);
	return 0;
}



