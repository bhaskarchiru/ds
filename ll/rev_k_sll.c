
#include <stdio.h>
#include <stdlib.h>


/*
 * Reverse every 'k' nodes in given linked list.
 */

struct ListNode {
	int	val;
	struct ListNode	*next;
};

struct ListNode *
reverse(struct ListNode *head)
{
	struct ListNode *current, *next, *prev = NULL;

	if(head == NULL || head->next == NULL) {
		return NULL;
	}
	current = head;
	while(current) {
		next = current->next;
		current->next = prev;
		prev = current;
		current = next;
	}
	return prev;
}

struct ListNode *
make_newnode(int val)
{
	struct ListNode *node;

	node =  malloc(sizeof(struct ListNode));
	node->val = val;
	node->next = NULL;
	return node;
}

struct ListNode *
add_at_tail(struct ListNode *head, int val)
{
	struct ListNode *current;

	if(head == NULL) {
		return make_newnode(val);
	}
	current = head;
	while(current->next) {
		current = current->next;
	}
	current->next = make_newnode(val);
	return head;
}

struct ListNode *
reverseKGroup(struct ListNode *head, int k)
{
	int		i;
	struct ListNode *next, *prev, *current;

	if(k == 1 || head == NULL || head->next == NULL) {
		return head;
	}
	current = head;
	for(i = 1; i < k; i++) {
		current = current->next;
		if(current == NULL) {
			break;
		}
	}
	if(i < k) {
		return head;
	}
	next = current->next;
	current->next = NULL;
	prev = head;
	head = reverse(head);
	prev->next = reverseKGroup(next, k);
	return head;
}

int
main(int argc, char *argv[])
{
	int		i;
	struct ListNode  *current, *head = NULL;
	
	for(i = 1; i < 20; i++) {
		head = add_at_tail(head, i);
	}
	current = head;
	while(current) {
		printf(" %d -> ", current->val);
		current = current->next;
	}
	printf("NULL\n");
	head = reverseKGroup(head, atoi(argv[1]));
	current = head;
	while(current) {
		printf(" %d -> ", current->val);
		current = current->next;
	}
	printf("NULL\n");
	return 0;
}
