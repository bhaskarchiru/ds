#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

/*
 * One program to print all orders iteratively.
 */

typedef struct treenode {
	struct treenode	*left;
	struct treenode	*right;
	int		val;
} treenode_t;

typedef enum {
	VISITED,
	LEFT_EXPLORED,
	RIGHT_EXPLORED
} state_t;

typedef struct stknode {
	struct treenode	*tnode;
	int		state;
} stknode_t;

typedef struct stk {
	stknode_t	*nodes;
	int		capacity;
	int		top;
} stk_t;

stk_t *
stk_init(int capacity)
{
	stk_t *s = malloc(sizeof(stack_t));
	
	s->nodes = (stknode_t *)malloc(sizeof(stknode_t) * capacity);
	s->capacity = capacity;
	s->top = -1;
	return s;
}

void
stk_push(stk_t *s, treenode_t *tnode, int state)
{	
	int		idx, new_capacity;
	stknode_t	*snode;

	idx = s->top + 1;
	if(idx  == s->capacity - 1) {
		new_capacity = s->capacity << 1;
		s->nodes = (stknode_t *)realloc(s->nodes, sizeof(stknode_t) * new_capacity);
		s->capacity = new_capacity;
	}
	snode = &s->nodes[idx];
	snode->tnode = tnode;
	snode->state = state;
	s->top++;
	return;
}

stknode_t *
stk_pop(stk_t *s)
{
	stknode_t	*snode;

	if(s->top == -1) {
		return NULL;
	}
	snode = &s->nodes[s->top];
	s->top--;
	return snode;
}

stknode_t *
stk_top(stk_t *s)
{

	if(s->top == -1) return NULL;
	return &s->nodes[s->top];
}

void
stk_deinit(stk_t *s)
{
	if(s) {
		if(s->nodes) {
			free(s->nodes);
		}
		free(s);
	}
	return;
}

void
print_order(treenode_t *root, int print_state)
{
	int		state;
	stk_t		*s;
	stknode_t	*stknode;
	treenode_t	*tnode;

	if(root == NULL) {
		return;
	}
	s = stk_init(20);
	stk_push(s, root, VISITED);
	while((stknode = stk_top(s)) != NULL) {
		state = stknode->state;
		tnode = stknode->tnode;
		switch(state) {
		case VISITED:
			if(print_state == VISITED) {
				printf(" %d ", tnode->val);
			}
			stknode->state++;
			if(tnode->left) {
				stk_push(s, tnode->left, VISITED);
			}
			break;

		case LEFT_EXPLORED:
			if(print_state == LEFT_EXPLORED) {
				printf(" %d ", tnode->val);
			}
			stknode->state++;
			if(tnode->right) {
				stk_push(s, tnode->right, VISITED);
			}
			break;

		case RIGHT_EXPLORED:
			if(print_state == RIGHT_EXPLORED) {
				printf(" %d ", tnode->val);
			}
			(void)stk_pop(s);
			break;

		default:
			assert(0);

		}
	}
	stk_deinit(s);
	return;
}

treenode_t *
make_node(int val)
{
	treenode_t	*node = malloc(sizeof(treenode_t));
	node->left = node->right = NULL;
	node->val = val;
	return node;
}

int
main(int argc, char *argv[])
{
	treenode_t	*root = make_node(1);

	root->left = make_node(2);
	root->right = make_node(3);

	root->left->left = make_node(4);
	root->left->right =  make_node(5);
	root->right->left = make_node(6);
	root->right->right = make_node(7);
	
	root->left->left->left = make_node(8);
	root->left->left->right = make_node(9);
	root->left->right->left =  make_node(10);
	root->left->right->right =  make_node(11);
	root->right->left->left = make_node(12);
	root->right->left->right = make_node(13);
	root->right->right->left = make_node(14);
	root->right->right->right = make_node(15);

	printf("Preorder: ");
	print_order(root, 0);
	printf("\n");
	printf("Inorder: ");
	print_order(root, 1);
	printf("\n");
	printf("Postorder: ");
	print_order(root, 2);
	printf("\n");
	return 0;
}
