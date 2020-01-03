
/*
 * 146. LRU Cache
 * Design and implement a data structure for Least Recently Used (LRU) cache.
 * It should support the following operations: get and put.
 * get(key) - Get the value (will always be positive) of the key if the key
 *	      exists in the cache, otherwise return -1.
 * put(key, value) - Set or insert the value if the key is not already present.
 * When the cache reached its capacity, it should invalidate the least recently
 * used item before inserting a new item.
 *
 * The cache is initialized with a positive capacity.
 */

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

typedef struct Node {
	struct Node	*next;
	struct Node	*prev;
	int		key;
	int		val;
} Node;

typedef struct LRUCache {
	Node	*next;
	Node	*prev;
	int	size;
	int	capacity;
} LRUCache;

Node *
make_node(int key, int val)
{
	Node *n = malloc(sizeof(Node));
	n->next = n->prev = n;
	n->key = key;
	n->val = val;
	return n;
}

LRUCache *
lRUCacheCreate(int capacity)
{
	
	LRUCache *cache = malloc(sizeof(LRUCache));
	cache->next = cache->prev = (Node *)cache;
	cache->size = 0;
	cache->capacity = capacity;
	return cache;
}

void
addAtHead(LRUCache *cache, Node *current)
{
	
	current->next = cache->next;
	cache->next->prev = current;
	cache->next = current;
	current->prev = (Node *)cache;
	return;
}

int
lRUCacheGet(LRUCache *cache, int key)
{
	int	val = -1;
	Node	*current;

	current = cache->next;
	while(current != (Node *)cache) {
		if(current->key == key) {
			val = current->val;
			break;
		}
		current = current->next;
	}
	if(val != -1) {
		
		/*
		 * Found the result, move the current to head, if it's not already
		 * at the head.
		 */
	
		if(current->prev != (Node *)cache) {
			current->prev->next = current->next;
			current->next->prev = current->prev;
			current->next = current;
			current->prev = current;
			addAtHead(cache, current);
		}
	}
	return val;
}

void
removeTail(LRUCache *cache)
{
	Node	*tail;

	tail = cache->prev;
	cache->prev = tail->prev;
	cache->prev->next = (Node *)cache;
	tail->next = tail;
	tail->prev = tail;
	free(tail);
	cache->size--;
	return;
}

void
lRUCachePut(LRUCache *cache, int key, int val)
{
	Node	*current, *result = NULL;

	current = cache->next;
	while(current != (Node *)cache) {
		if(current->key == key) {
			result = current;
			break;
		}
		current = current->next;
	}
	if(result) {
		result->val = val;
		result->prev->next = result->next;
		result->next->prev = result->prev;
		result->next = result;
		result->prev = result;
		addAtHead(cache, result);
		return;
	}
	result = make_node(key, val);
	addAtHead(cache, result);
	cache->size++;
	if(cache->size > cache->capacity) {
		removeTail(cache);
	}
	return;
}

void
lRUCacheFree(LRUCache *cache)
{

	while(cache->size == 0) {
		removeTail(cache);
	}
	free(cache);
	return;
}

int
main(int argc, char *argv[])
{
	int	  val;
	LRUCache* cache = lRUCacheCreate(1);

	val = lRUCacheGet(cache, 1);
	assert(val == -1);
	lRUCacheFree(cache);

	lRUCachePut(cache, 1, 3);
	lRUCachePut(cache, 2, 6);
	lRUCachePut(cache, 3, 9);
	lRUCachePut(cache, 4, 12);
	lRUCachePut(cache, 5, 15);
	lRUCachePut(cache, 6, 18);

	/*
	 * Expect '1' to be evicted.
	 */

	val = lRUCacheGet(cache, 1);
	assert(val == -1);

	/*
	 * Accessing '2' brings it to head
	 */

	val = lRUCacheGet(cache, 2);
	assert(val == 6);

	/* 
	 * This evicts '3'.
	 */

	lRUCachePut(cache, 7, 21);
	val = lRUCacheGet(cache, 3);
	assert(val == -1);

	/*
	 * Updating '4' brings it to head.
	 */

	lRUCachePut(cache, 4, 13);
	val = lRUCacheGet(cache, 4);
	assert(val == 13);

	/*
	 * This evicts '5'.
	 */

	lRUCachePut(cache, 8, 24);
	val = lRUCacheGet(cache, 5);
	assert(val == -1);
	lRUCacheFree(cache);
	return 0;
}

