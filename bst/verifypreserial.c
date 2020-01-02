/*
 * 331. Verify Preorder Serialization of a Binary Tree
 */

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

#define NULL_NODE		"#"
#define NODE_SEPARATOR		","
#define MAX_NODE_NAME_LEN	2
#define INITIAL_CAPACITY	8

typedef struct stackele {
	char	node[MAX_NODE_NAME_LEN];
	int	children;
} stackele_t;

typedef struct stack {
	stackele_t	*data;
	int		top;
	int		capacity;
} stack_t;

stack_t *
init_stack(int capacity)
{

	stack_t *stk = malloc(sizeof(stack_t));
	stk->data = malloc(sizeof(stackele_t) * capacity);
	stk->capacity = capacity;
	stk->top = -1;
	return stk;
}

void
push(stack_t *stk, char *node)
{
	stackele_t	*element;

	if(stk->top == stk->capacity) {
		stk->capacity <<= 1;
		stk->data = realloc(stk->data, sizeof(stackele_t) * stk->capacity);
	}
	element = &stk->data[++stk->top];
	snprintf(element->node, MAX_NODE_NAME_LEN, "%s", node);
	element->children = 2;
	return;
}

stackele_t *
pop(stack_t *stk)
{
	stackele_t	*element;

	if(stk->top == -1) {
		return NULL;
	}
	element = &stk->data[stk->top--];
	//printf("Popping off %s, child count: %d top: %d\n",
	//	element->node, element->children, stk->top);
	return element;
}

bool
do_decrease_childcnt(stack_t *stk)
{
	stackele_t	*element;

	element = &stk->data[stk->top];
	//printf("Decreasing child count of %s from %d -> %d\n",
	//	element->node, element->children, element->children - 1);
	element->children--;
	if(element->children == 0) {
		(void)pop(stk);
		if(stk->top == -1) {
			return true;
		}
		return do_decrease_childcnt(stk);
	}
	return true;
}


/*
 * Decrease child count of top node in the stack, this also
 * helps us in detecting anamolies
 *	If there is no top NODE
 */


bool
decrease_childcnt(stack_t *stk)
{

	if(stk->top == -1) {
		return false;
	}
	return do_decrease_childcnt(stk);
}

bool
is_empty(stack_t *stk)
{

	return stk->top == -1;
}

stackele_t *
top(stack_t *stk)
{
	stack_t	*element;

	if(stk->top == -1) {
		return NULL;
	}
	return &stk->data[stk->top];
}

void
deinit_stack(stack_t *stk)
{

	free(stk->data);
	free(stk);
	return;
}

bool isValidSerialization(char * preorder)
{
	int	i = 0;
	bool	result;
	char	*token;
	stack_t	*stk;

	if(preorder == NULL) {
		return false;
	}
	if(strlen(preorder) == 1 && !strcmp(preorder, NULL_NODE)) {
		return true;
	}
	stk = init_stack(INITIAL_CAPACITY);
	token = strtok(preorder, NODE_SEPARATOR);
	while(token) {
		if(!strcmp(token, NULL_NODE)) {

			/*
			 * Encountered a leaf node.
			 */

			if(!decrease_childcnt(stk)) {
				result = false;
				goto out;
			}
			token = strtok(NULL, NODE_SEPARATOR);
			continue;
		}
		push(stk, token);
		i++;
		token = strtok(NULL, NODE_SEPARATOR);
	}
	result = is_empty(stk) ? true : false;

out:
	deinit_stack(stk);
	return result;
}

int
main(int argc, char *argv[])
{
	//char preorder[] = "9,3,4,#,#,1,#,#,2,#,6,#,#";
	//char preorder[] = "1,#";
	//char preorder[] = "9, #, #, 1";
	//char preorder[] = "#";
	//char preorder[] = "9,9,9,9,9,9,#,#,9,9,#,#,#,9,9,9,9,#,#,9,#,9,#,#,#,#,9,9,9,#,#,9,#,#,9,#,#,9,#,#,9,9,#,#,9,#,9,9,#,#,#";
	char preorder[] = "1,2,3,4,#,5,6,#,7,#,9,10,#,#,#,#,#,#,#";

	printf("Given seriralization sequence %s from a binary tree.\n",
	  	isValidSerialization(preorder) ? "is" : "is not");
	return 0;
}
