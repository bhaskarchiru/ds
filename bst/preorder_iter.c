/*
 * Non-recursive pre-order traversal.
 */

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

enum states {
	UNEXPLORED = 1,
	LEFTVISITED,
	RIGHTVISITED,
};

typedef struct bstnode {
	struct bstnode	*left;
	struct bstnode	*right;
	int		val;
} bstnode_t;

typedef struct stacknode {
	struct bstnode	*node;
	int		state;
} stacknode_t;

typedef struct stack {
	stacknode_t	*snodes;
	int		top;
} stack_t;

stack_t *
init_stack(int capacity)
{
	stack_t	*s;

	s = malloc(sizeof(stack_t));
	s->snodes = calloc(1, capacity * sizeof(stacknode_t));
	s->top = -1;
	return s;
}

void
deinit_stack(stack_t *s)
{

	free(s->snodes);
	free(s);
	return;
}

void
push(stack_t *s, bstnode_t *node, int state)
{
	stacknode_t	*snode;

	s->top++;
	snode = s->snodes + s->top;
	snode->node = node;
	snode->state = state;
	return;
}

void
pop(stack_t *s, bstnode_t **node, int *statep)
{
	stacknode_t	*snode;

	*node = NULL;
	*statep = 0;

	if(s->top == -1) {
		return;
	}
	snode = s->snodes + s->top;
	*node = snode->node;
	*statep = snode->state;
	snode = NULL;
	s->top--;
	return;
}

void
top(stack_t *s, bstnode_t **node, int *statep)
{
	stacknode_t	*snode;

	*node = NULL;
	*statep = 0;

	if(s->top == -1) {
		return;
	}
	snode = s->snodes + s->top;
	*node = snode->node;
	*statep = snode->state;
	return;
}

bstnode_t *
make_bstnode(int val)
{

	bstnode_t *node = calloc(1, sizeof(bstnode_t));
	node->val = val;
	return node;
}

int
sizeoftree(bstnode_t *root)
{
	int	size = 0;

	if(root) {
		return 1 + sizeoftree(root->left) + sizeoftree(root->right);
	}
	return size;
}

void
print_preorder(bstnode_t *root)
{
	int		state;
	stack_t		*s;
	bstnode_t	*current;

	if((current = root) == NULL) {
		return;
	}
	if(current->left == NULL && current->right == NULL) {
		printf(" %d ", current->val);
		return;
	}
	s = init_stack(sizeoftree(root));
	push(s, current, UNEXPLORED);
	while(1) {
		pop(s, &current, &state);
		if(current == NULL) {
			break;
		}

		switch(state) {
		case RIGHTVISITED:
			break;

		case LEFTVISITED:
			if(current->right != NULL) {
				push(s, current, RIGHTVISITED);
				push(s, current->right, UNEXPLORED);
			} else {
				printf(" %d ", current->val);
			}
			break;

		default:
			assert(state == UNEXPLORED);	
			printf(" %d ", current->val);
			if(current->left != NULL) {
				push(s, current, LEFTVISITED);
				push(s, current->left, UNEXPLORED);
			} else if(current->right != NULL) {
				push(s, current, RIGHTVISITED);
				push(s, current->right, UNEXPLORED);
			}
			break;
		}
	}
	deinit_stack(s);
	return;

}

int
main(int argc, char *argv[])
{
	bstnode_t	*root;

	/*
	 *		8
	 *	   5	    11
	 *      4     6  10    13
	 *
	 *   Preorder:  8 5 4 6 11 10 13
	 */

	root = make_bstnode(8);
	root->left = make_bstnode(5);
	root->right = make_bstnode(11);
	root->left->left = make_bstnode(4);
	root->left->right = make_bstnode(6);
	root->right->left = make_bstnode(10);
	root->right->right = make_bstnode(13);

	print_preorder(root);
	printf("\n");
	return 0;
}
