#include <stdio.h>
#include <stdlib.h>

typedef struct sllnode {
	struct sllnode	*next;
	int		val;
} sllnode_t;

sllnode_t *
make_sllnode(int val)
{
	sllnode_t	*node;
	node = malloc(sizeof(sllnode_t));
	node->next = NULL;
	node->val = val;
	return node;
}

sllnode_t *
make_list(int *arr, int n)
{
	int		i;
	sllnode_t	*node, *head = NULL;

	head = make_sllnode(arr[0]);
	node = head;
	for(i = 1; i < n; i++) {
		node->next = make_sllnode(arr[i]);
		node = node->next;
	}
	return head;
}

int
length(sllnode_t *head)
{
	int count = 0;
	while(head) {
		count++;
		head = head->next;
	}
	return count;
}

void
print_list(sllnode_t	*head)
{
	sllnode_t	*node = head;

	while(node != NULL) {
		printf(" %d -> ", node->val);
		node = node->next;
	}
	printf(" NULL \n");
	return;
}

void
deinit_list(sllnode_t	*head)
{
	sllnode_t	*node, *next;

	if((node = head) == NULL) {
		return;
	}
	while(node != NULL) {
		next = node->next;
		free(node);
		node = next;
	}
	return;
}

sllnode_t *
addatplace(sllnode_t *head, sllnode_t *node)
{
	sllnode_t	*current, *prev = NULL;

	if((current = head) == NULL) {
		return node;
	}
	while(current != NULL && current->val <= node->val) {
		prev = current;
		current = current->next;
	}
	if(prev == NULL) {
		node->next = current;
		return node;
	}
	prev->next = node;
	node->next = current;
	return head;
}

sllnode_t *
merge_two_lists(sllnode_t *list1, sllnode_t *list2)
{
	int	l1 = length(list1);
	int	l2 = length(list2);
	sllnode_t	*next, *current, *mergeinto, *merge;

	
	if(l1 < l2) {
		merge = list2;
		mergeinto = list1;
	} else {
		merge = list1;
		mergeinto = list2;
	}
	current = merge;
	while(current)  {
		next = current->next;
		current->next = NULL;
		mergeinto = addatplace(mergeinto, current);
		current = next;
	}
	return mergeinto;
}


int
main(int argc, char *argv[])
{
	int		arr1[] = {2, 4, 7, 9, 10, 13, 15, 16, 19, 16};
	int		arr2[] = {1, 3, 8, 11, 12, 14};
	sllnode_t	*list1, *list2;
	
	list1 = make_list(arr1, sizeof(arr1)/sizeof(arr1[0]));
	print_list(list1);
	
	list2 = make_list(arr2, sizeof(arr2)/sizeof(arr2[0]));
	print_list(list2);

	list1 = merge_two_lists(list1, list2);
	print_list(list1);
	deinit_list(list1);
	return 0;
}
