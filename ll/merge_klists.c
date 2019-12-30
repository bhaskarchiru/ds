/*
 * Merge sorted lists into a sorted list using heap.
 */

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <limits.h>

#define LEFT_CHILD(x)	(2 * x + 1)
#define RIGHT_CHILD(x)	(2 * x + 2)
#define PARENT(x)	(x & 1 ? x / 2 : x / 2 -1)

struct ListNode {
	struct ListNode	*next;
	int		val;
};

typedef struct heapele {
	int	val;
	int	idx;
} heapele_t;

typedef struct heap {
	heapele_t	*data;
	int		size;
	int		capacity;
} heap_t;

heap_t *
init_heap(int capacity)
{
	heap_t	*h;

	h = malloc(sizeof(heap_t));
	h->size = 0;
	h->capacity = capacity;
	h->data = malloc(sizeof(heapele_t) * h->capacity);
	return h;
}

void
deinit_heap(heap_t *heap)
{

	free(heap->data);
	free(heap);
	return;
}

void
swap(heapele_t *a, heapele_t *b)
{
	heapele_t   c;
	c = *a;
	*a = *b;
	*b = c;
	return;
}

void
heap_insert(heap_t *h, int val, int idx)
{
	int         i;
	heapele_t   *ele, *pele;
   
   	if(h->size == 0) {
		ele = h->data;
		ele->val = val;
		ele->idx = idx;
		h->size++;
		return;
	}
    	i = h->size;
	ele = h->data + i;
	h->size++;
	ele->val = val;
	ele->idx = idx;
	i = PARENT(i);
	while(i >= 0) {
		pele = h->data + i;
		if(ele->val < pele->val) {
			swap(ele, pele);
		}
		ele = pele;
		i = PARENT(i);
	}
	return;
}


/*
 * Root of heap was replaced by last element from the heap.
 * Bubble it down to its rightful place.
 */

void
bubble_down(heap_t *h)
{
	int         i, nidx;
	heapele_t   *root, *ele, *lele = NULL, *rele = NULL;
	       
	root = h->data;
	i = 0;
	while(i < h->size) {
		ele = root;
		if(LEFT_CHILD(i) < h->size) {
			lele = h->data + LEFT_CHILD(i);
		}
		if(RIGHT_CHILD(i) < h->size) {
			rele = h->data + RIGHT_CHILD(i);
		}
		if(lele != NULL && lele->val < ele->val) {
			ele = lele;
			nidx = LEFT_CHILD(i);
		}
		if(rele != NULL && rele->val < ele->val) {
			ele = rele;
			nidx = RIGHT_CHILD(i);
		}
		if(ele != root) {
			swap(ele, root);
			root = ele;
			i = nidx;
			lele = NULL;
			rele = NULL;
		} else {
			break;
		}
	}
	return;
}

int
get_min(heap_t *h, int *idxp)
{
	int         val;
	heapele_t   *firstele, *lastele;

	if(h->size == 0) {
		return INT_MIN;
	}
	firstele = h->data;
	lastele = h->data + h->size - 1;
	val = firstele->val;
	*idxp = firstele->idx;
	h->size--;
	
	if(h->size == 0) return val;
	swap(firstele, lastele);
	bubble_down(h);
	return val;
}

bool
is_empty(heap_t *h)
{

	return h->size == 0;
}

struct ListNode *
add_to_result(struct ListNode *result, struct ListNode *node)
{
	struct ListNode *current;

	if(result == NULL) return node;
	current = result;
	while(current->next) current = current->next;
	current->next = node;
	return result;
}

struct ListNode* mergeKLists(struct ListNode** lists, int listsSize){
	int             i, min, listidx;
	heap_t          *h;
	struct ListNode *node, *next, *result = NULL;
																																			           
	/*
	 * Loop through the list, and insert all first values into a heap.
	 *  
	 *  while(heap is empty) { 
	 *      Select minimum from heap.
	 *      Detach selected nodes from its original ist and add next element from this list to heap
	 *      Add detached node to result.
	 * }
	 */

	if(listsSize == 0) {
		return NULL;
	}
	if(listsSize == 1) {
		return lists[0];
	}
	h = init_heap(listsSize);
	for(i = 0; i < listsSize; i++) {
		if(node = lists[i]) {
			heap_insert(h, node->val, i);
		}
	}
	while(!is_empty(h)) {
		min = get_min(h, &listidx);
		node = lists[listidx];
		next = node->next;
		node->next = NULL;
		lists[listidx] = next;
		if(next != NULL) {
			heap_insert(h, next->val, listidx);
		}
		result = add_to_result(result, node);
	}
	deinit_heap(h);
	return result;
}

struct ListNode *
make_node(int val)
{
	struct ListNode *node;
	node = malloc(sizeof(struct ListNode));
	node->val = val;
	node->next = NULL;
	return node;
}

struct ListNode *
sorted_insert(struct ListNode *head, struct ListNode *node)
{
	struct ListNode *current, *prev;

	if(head == NULL) {
		return node;
	}
	prev = NULL;
	current = head;
	while(current && current->val < node->val) {
		prev = current;
		current = current->next;
	}
	if(prev == NULL) {
		node->next = current;
		return node;
	}
	node->next = prev->next;
	prev->next = node;
	return head;
}

int
main(int *argc, char *argv[])
{
	int	i, j, n;
	struct	ListNode **lists, *node, *list = NULL;

	lists = malloc(sizeof(struct ListNode *) * 3);

	for(i = 0; i < 3; i++) {
		n = 3 + rand() % 7;	
		for(j = 0; j < n; j++) {
			node = make_node(rand() % 100);
			list = sorted_insert(list, node);
		}
		lists[i] = list;
		list = NULL;
	}
	for(i = 0; i < 3; i++) {
		printf("List %d ", i);
		node = lists[i];
		while(node) {
			printf(" %d -> ", node->val);
			node = node->next;
		}
		printf("NULL\n");
	}
	list = mergeKLists(lists, 3);
	while(list) {
		printf(" %d -> ", list->val);
		list = list->next;
	}
	printf("NULL\n");
	return 0;
}
