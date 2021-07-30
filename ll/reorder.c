/*
 * 143. Reorder List
 *  L0 -> L1 -> L2 -> L3 -> ... Ln -> NULL
 *   Into
 *  L0 -> Ln -> L1 -> Ln-1 -> L2 -> Ln-2 -> .... -> NULL
 */

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

struct ListNode {
	struct ListNode	*next;
	int		val;
};

struct ListNode *
make_newnode(int val)
{
	struct ListNode *node = malloc(sizeof(struct ListNode));
	node->next = NULL;
	node->val = val;
	return node;
}

struct ListNode *
add_to_tail(struct ListNode *head, int val)
{
	struct ListNode *current, *node = make_newnode(val);

	if(head == NULL) { 
		return node;
	}
	current = head;
	while(current->next)  {
		current = current->next;
	}
	current->next = node;
	return head;
}

struct ListNode *
reverse_list(struct ListNode *head)
{
	struct ListNode *current, *prev = NULL, *next;

	if(head == NULL || head->next == NULL) {
		return head;
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

/*
 * Break the list into half, reverse the second half,
 * and then merge the halves.
 */

void
reorderList(struct ListNode **headRef)
{
	bool		even = false;
	struct ListNode	*result = NULL, *list1 = NULL, *list2 = NULL;
	struct ListNode	*head, *next1, *next2, *fast, *slow, *prev;

	head = *headRef;
	if(head == NULL || head->next == NULL) {
		return;
	}
	fast = slow = prev = head;
	while(fast->next) {
		prev = slow;
		slow = slow->next;
		fast = fast->next;
		if(fast->next) {
			fast = fast->next;
		} else {
			even = true;
		}
	}
	if(even) {
		prev->next = NULL;
		list2 = slow;
	} else {
		list2 = slow->next;
		slow->next = NULL;
	}
	list1 = head;
	slow = list1;
	printf("list1:\t");
	while(slow) {
		printf("%d -> ", slow->val);
		slow = slow->next;
	}
	printf("NULL\n");
	list2 = reverse_list(list2);
	slow = list2;
	printf("list2:\t");
	while(slow) {
		printf("%d -> ", slow->val);
		slow = slow->next;
	}
	printf("NULL\n");
	prev = NULL;
	while(list1 != NULL && list2 != NULL) {
		next1 = list1->next;
		next2 = list2->next;
		list1->next = NULL;
		list2->next = NULL;
		if(prev == NULL) {
			*headRef = prev = list1;
			prev->next = list2;
		} else {
			prev->next = list1;
			prev->next->next = list2;
		}
		prev = list2;
		list1 = next1;
		list2 = next2;
	}
	if(list1) {
		next1 = list1->next;
		list1->next = NULL;
		prev->next = list1;
	}
	return;
}

int
main(int argc, char *argv[])
{
	struct ListNode *list = NULL;

	list = add_to_tail(list, 1);
	list = add_to_tail(list, 2);
	list = add_to_tail(list, 3);
	list = add_to_tail(list, 4);
	list = add_to_tail(list, 5);
	list = add_to_tail(list, 6);
	list = add_to_tail(list, 7);
	reorderList(&list);
	while(list) {
		printf("%d -> ", list->val);
		list = list->next;
	}
	printf(" NULL \n");
	return 0;
}
