/*
 * 1019. Next Greater Node In Linked List
 * 
 * I/P: [ 2, 1, 5]
 * O/P: [ 5, 5, 0]
 *
 * I/P: [ 2, 7, 4, 3, 5 ]
 * O/P: [ 7, 0, 5, 5, 0 ]
 *
 * I/P: [ 1, 7, 5, 1, 9, 2, 5, 1 ]
 * O/P: [ 7, 9, 9, 9, 0, 5, 0, 0 ]
 */

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <limits.h>

#define MIN(A, B)   ((A) < (B) ? (A) : (B))
#define MAX(A, B)   ((A) > (B) ? (A) : (B))

struct ListNode {
	struct ListNode *next;
	int		val;
};

typedef struct stackele {
	int ele;
	int idx;
}  stackele_t;


typedef struct stack {
	stackele_t  *data;
	int         top;
	int         capacity;
} stack_t;

stack_t *
init_stack(int capacity)
{
	stack_t *S = malloc(sizeof(stack_t));
	
	S->data = calloc(1, sizeof(stackele_t) * capacity);
	S->top = -1;
	S->capacity = capacity;
	return S;

}

void
deinit_stack(stack_t *S)
{

	free(S->data);
	free(S);
	return;
}

void
push(stack_t *S, int ele, int idx)
{
	stackele_t  *sele, *tele;

	sele = &S->data[++S->top];
	sele->ele = ele;
	sele->idx = idx;
	return;
}

int
pop(stack_t *S, int *idxp)
{
	stackele_t  *tele;

	if(S->top == -1) {
		*idxp = INT_MIN;
		return INT_MIN;
	}
	tele = &S->data[S->top--];
	*idxp = tele->idx;
	return tele->ele;
}

bool
is_empty(stack_t *S)
{
    
        return S->top == -1;
}

int
top(stack_t *S)
{

	stackele_t	*ele;

	ele = &S->data[S->top];
	return ele->ele;
}
	

int
lengthOfList(struct ListNode *head)
{
	int len = 0;
        
	while(head) {
		len++;
		head = head->next;
	}
	return len;
}

struct ListNode *
make_node(int val)
{
	struct ListNode *node = malloc(sizeof(struct ListNode));
	node->next = NULL;
	node->val = val;
	return node;
}

struct ListNode *
add_to_list(struct ListNode *head, int val)
{
	struct ListNode *current, *node = make_node(val);
	
	if(head == NULL) {
		return node;
	}
	current = head;
	while(current->next != NULL) current = current->next;
	current->next = node;
	return head;
}

int* nextLargerNodes(struct ListNode* head, int* returnSize){
	int		idx, *result, val, curidx = 0;
        struct ListNode *current;
	stack_t         *S;

	if(head == NULL) {
		return NULL;
	}
			        
	*returnSize = lengthOfList(head);
	result = calloc(1, sizeof(int) * *returnSize);
	S = init_stack(*returnSize);
	current = head;
	push(S, current->val, curidx++);
	current = current->next;
	while(current) {
		while(!is_empty(S) && top(S) < current->val) {
			val = pop(S, &idx);
			result[idx] = current->val;
		}
		push(S, current->val, curidx++);
		current = current->next;
	}
	while(!is_empty(S)) {
		val = pop(S, &idx);
		result[idx] = 0;
	}
	deinit_stack(S);
	return result;
}

int
main(int argc, char *argv[])
{
	int		i, *resultp = NULL, resultsz = 0;
	struct ListNode *head = NULL;

	head = add_to_list(head, 9);
	head = add_to_list(head, 7);
	head = add_to_list(head, 6);
	head = add_to_list(head, 7);
	head = add_to_list(head, 6);
	head = add_to_list(head, 9);

	resultp = nextLargerNodes(head, &resultsz);
	for(i = 0; i < resultsz; i++) {
		printf(" %d ", resultp[i]);
	}
	printf("\n");
	return 0;
}
