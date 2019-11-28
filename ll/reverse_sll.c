#include <stdio.h>
#include <stdlib.h>

typedef struct node {
	struct node	*next;
	int		val;
} node_t;

node_t *
make_node(int val)
{

	node_t	*node = calloc(1, sizeof(node_t));
	node->val = val;
	return node;
}

node_t *
make_list(int *arr, int n)
{
	int	ii;
	node_t	*head, *current;

	head = current = make_node(arr[0]);
	for(ii = 1; ii < n; ii++) {
		current->next = make_node(arr[ii]);
		current = current->next;
	}
	return head;
}

void
print_list(node_t *head)
{

	if(head == NULL) {
		return;
	}
	while(head) {
		printf(" %d -> ", head->val);
		head = head->next;
	}
	printf(" NULL\n");
	return;
}

node_t *
reverse_list(node_t *head)
{
	node_t	*current, *next, *prev = NULL;

	prev = NULL;
	current = head;
	while(current) {
		next = current->next;
		current->next = prev;
		prev = current;
		current = next;
	}
	return prev;
}

node_t *
reverse_list_recursive(node_t *head)
{
	node_t	*first, *rest;

	/*
	 * Base conditions:
	 * For 0 or 1 elements, return the head passed.
	 */

	if((first = head) == NULL || (rest = first->next) == NULL) {
		return first;
	}

	/*
	 * Recurse on rest of the list.
	 */

	rest = reverse_list_recursive(rest);

	/*
	 * First's next still contains address of erstwhile second element,
	 * which has become the tail of the list after the above reverse.
	 * Append first to that.
	 */

	first->next->next = first;

	/*
	 * Now, first has become last element, its next should be NULL.
	 */

	first->next = NULL;
	return rest;
}

void
deinit_list(node_t *head)
{
	node_t	*next;

	if(head == NULL) {
		return;
	}
	while(head) {
		next = head->next;
		free(head);
		head = next;
	}
	return;
}

int
main(int argc, char *argv[])
{
	int	n, arr[] = {1, 2, 3, 4, 5, 6, 7, 8};
	node_t	*head;

	n = sizeof(arr)/sizeof(arr[0]);

	head = make_list(arr, n);
	print_list(head);
	head = reverse_list(head);
	print_list(head);

	head = reverse_list_recursive(head);
	print_list(head);
	deinit_list(head);
	return 0;
}
