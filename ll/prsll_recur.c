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

	if(n == 0) {
		return NULL;
	}
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
		goto out;
	}
	while(head) {
		printf(" %d -> ", head->val);
		head = head->next;
	}

out:
	printf(" NULL\n");
	return;
}

node_t *
pairwise_reverse_list_recursive(node_t *head)
{
	node_t	*first, *second, *rest;

	/*
	 * Base conditions:
	 * For 0 or 1 elements, return the head passed.
	 */

	if((first = head) == NULL || (second = first->next) == NULL) {
		return first;
	}

	/*
	 * Recurse on rest of the list, starting from next element of second.
	 */

	rest = pairwise_reverse_list_recursive(second->next);
	second->next = first;
	first->next = rest;
	return second;
}

void
deinit_list(node_t	*head)
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
	int	n, arr1[] = {1, 2, 3, 4, 5, 6, 7, 8};
	int	arr2[] = {};
	int	arr3[] = {1, 2};
	int	arr4[] = {1};
	int	arr5[] = {1, 2, 3};
	int	arr6[] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11};
	node_t	*head;

	n = sizeof(arr1)/sizeof(arr1[0]);
	head = make_list(arr1, n);
	print_list(head);
	head = pairwise_reverse_list_recursive(head);
	print_list(head);
	deinit_list(head);

	head = make_list(arr2, 0);
	print_list(head);
	head = pairwise_reverse_list_recursive(head);
	print_list(head);
	deinit_list(head);

	n = sizeof(arr3)/sizeof(arr3[0]);
	head = make_list(arr3, n);
	print_list(head);
	head = pairwise_reverse_list_recursive(head);
	print_list(head);
	deinit_list(head);

	n = sizeof(arr4)/sizeof(arr4[0]);
	head = make_list(arr4, n);
	print_list(head);
	head = pairwise_reverse_list_recursive(head);
	print_list(head);
	deinit_list(head);

	n = sizeof(arr5)/sizeof(arr5[0]);
	head = make_list(arr5, n);
	print_list(head);
	head = pairwise_reverse_list_recursive(head);
	print_list(head);
	deinit_list(head);

	n = sizeof(arr6)/sizeof(arr6[0]);
	head = make_list(arr6, n);
	print_list(head);
	head = pairwise_reverse_list_recursive(head);
	print_list(head);
	deinit_list(head);
	return 0;
}
