/*
 * Check whether given linked list of node values together as a number
 * form a palindrome.
 *
 * 	1 -> 2 -> 2 -> 1	true
 *	1 -> 2 -> 3 -> 2 -> 1	true
 *	1			true
 *	1 -> 2			false
 *	NULL			falsa
 */

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

struct ListNode {
	struct ListNode	*next;
	int		val;
};


struct ListNode *
reverse(struct ListNode *head)
{
	struct ListNode	*current, *next, *prev = NULL;

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

bool
isPalindrome(struct ListNode *head)
{
	bool		result;
	struct ListNode *newhead, *slow, *fast, *prev = NULL;
	        
	if(head == NULL || head->next == NULL) {
		return true;
	}
	slow = fast = head;
	while(fast) {
		prev = slow;	
		slow = slow->next;
		fast = fast->next;
		if(fast) {
			fast = fast->next;
		}
	}

	/*
	 * Break the list into two parts and reverse the second list.
	 */

	newhead = slow;
	prev->next = NULL;
	newhead = reverse(newhead);

	/*
	 * Now, we've list broken into two parts, in case of odd length,
	 * first list will have more elements, we're interested in comparisons
	 * until we do not exhaust *BOTH* the lists.
	 */

	result = true;
	while(head && newhead) {
		if(head->val != newhead->val) {
			result = false;
			break;
		}
		head = head->next;
		newhead = newhead->next;
	}
	newhead = reverse(newhead);
	slow->next = newhead;
	return result;
}

struct ListNode *
make_newnode(int val)
{

	struct ListNode *node = calloc(1, sizeof(struct ListNode));
	node->val = val;
	return node;
}

struct ListNode *
add_to_tail(struct ListNode *head, int val)
{
	struct ListNode *node = make_newnode(val), *current;

	if(head == NULL) {
		return node;
	}
	current = head;
	while(current->next) current = current->next;
	current->next = node;
	return head;
}



int
main(int argc, char *argv[])
{
	struct ListNode *head = NULL;

	head = add_to_tail(head, 1);
	head = add_to_tail(head, 2);
	head = add_to_tail(head, 3);
	head = add_to_tail(head, 4);
	head = add_to_tail(head, 2);
	head = add_to_tail(head, 1);

	printf("Given linked list %s a palindrome\n",
		isPalindrome(head) ? "is" : "is not");
	return 0;
}
