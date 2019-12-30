/*
 * 445. Add Two Numbers II
 * (7 -> 2 -> 4 -> 3) + (5 -> 6 -> 4)
 * (7 -> 8 -> 0 -> 7)
 */

#include <stdio.h>
#include <stdlib.h>

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
reverse_list(struct ListNode *head)
{

	struct ListNode *current, *next, *prev = NULL;

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

int
length(struct ListNode *head)
{

	int len = 0;
	while(head) {
		len++;
		head = head->next;
	}
	return len;
}

struct ListNode* addTwoNumbers(struct ListNode* l1, struct ListNode* l2){
	int *stack1, *stack2, top1 = -1, top2 = -1, carry, sum;
	struct ListNode *head, *node, *prev = NULL;
	int l1len, l2len;

	l1len = length(l1);
	l2len = length(l2);
	if(l1len == 0) {
		return l2;
	}
	if(l2len == 0) {
		return l1;
	}
	stack1 = malloc(sizeof(int) * l1len);
	stack2 = malloc(sizeof(int) * l2len);

	node = l1;
	while(node) {
		stack1[++top1] = node->val;
		node = node->next;
	}
	node = l2;
	while(node) {
		stack2[++top2] = node->val;
		node = node->next;
	}
	carry = 0;
	while(top1 != -1 && top2 != -1) {
		sum = carry + stack1[top1--] + stack2[top2--];
		node = make_newnode(sum % 10);
		if(prev == NULL) {
			head = node;
		} else {
			prev->next = node;
		}
		prev = node;
		carry = sum / 10;
	}
	while(top1 != -1) {
		sum = carry + stack1[top1--];
		node = make_newnode(sum % 10);
		prev->next = node;
		prev = node;
		carry = sum / 10;
	}
	while(top2 != -1) {
		sum = carry + stack2[top2--];
		node = make_newnode(sum % 10);
		prev->next = node;
		prev = node;
		carry = sum / 10;
	}
	if(carry) {
		node = make_newnode(carry);
		prev->next = node;
	}
	head = reverse_list(head);
	free(stack1);
	free(stack2);
	return head;
}

struct ListNode *
add_to_list(struct ListNode *head, int val)
{
	struct ListNode *current, *node = make_newnode(val);

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
	struct ListNode *l1 = NULL, *l2 = NULL;

	l1 = add_to_list(l1, 7);
	l1 = add_to_list(l1, 2);
	l1 = add_to_list(l1, 4);
	l1 = add_to_list(l1, 3);
	l2 = add_to_list(l2, 5);
	l2 = add_to_list(l2, 6);
	l2 = add_to_list(l2, 4);
	l1 = addTwoNumbers(l1, l2);
	while(l1) {
		printf("%d -> ", l1->val);
		l1 = l1->next;
	}
	printf(" NULL \n");
	return 0;
}
