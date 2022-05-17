
/*
 * Dijkstra's shortest path algorithm, graph is represented by adjancency list. 
 * Uses min-heap
 */

#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <stdbool.h>
#include <assert.h>
#include <string.h>

#define GRAPH_WEIGHTED	0x0001
#define GRAPH_DIRECTED	0x0002

#define PARENT(x)	((x) & 1) ? (x) / 2 : (x) / 2 - 1
#define LEFT_CHILD(x)	(2 * (x) + 1)
#define RIGHT_CHILD(x)	(2 * (x) + 2)

/*
 * Linked list of edges.
 */

typedef struct edgenode {
	struct edgenode	*next;
	int		dst;	/* Destination vertex */
	int		weight;	/* Weight of the edge */
} edgenode_t;

typedef struct graph {
	edgenode_t	**head;	/* Array of heads of linked lists for each vertex */
	int		nvertex;
	int		nedge;
	int		flags;
} graph_t;

/*
 * Each node in min-heap saves the distance value, which is the value
 * on which comparisons are made, and the vertex index in the graph
 * this min-heap node corresponds to.
 */

typedef struct mhnode {
	int	vertex;	/* Vertex index in the graph */
	int	dist;	/* Distance to this vertex from source, so far */
} mhnode_t;

typedef struct minheap {
	mhnode_t	*data;	/* Array of min-heap nodes */
	int		size;	/* Logical size of min-heap */
	int		capacity;/* Allocated size of min-heap */
	int		*pos;	/* Map of <min_heap_node_idx> --> <Vertex index> */
} minheap_t;

void
swap(mhnode_t *a, mhnode_t *b)
{
	mhnode_t	c;

	memcpy(&c, a, sizeof(mhnode_t));
	memcpy(a, b, sizeof(mhnode_t));
	memcpy(b, &c, sizeof(mhnode_t));
	return;
}

graph_t *
init_graph(int nvertex, int nedge, int weighted, int directed)
{
	graph_t	*G;
	
	G = malloc(sizeof(graph_t));
	G->nvertex = nvertex;
	G->nedge = nedge;
	G->head = (edgenode_t **)calloc(1, sizeof(edgenode_t *) * G->nvertex);
	if(weighted) {
		G->flags = GRAPH_WEIGHTED;
	}
	if(directed) {
		G->flags |= GRAPH_DIRECTED;
	}
	return G;
}

void
deinit_graph(graph_t *G)
{
	int		i;
	edgenode_t	*current, *next, *head;

	for(i = 0; i < G->nvertex; i++) {
		head = current = G->head[i];
		while(current) {
			next = current->next;
			current->next = NULL;
			free(current);
			current = next;
		}
	}
	free(G->head);
	free(G);
	return;
}

edgenode_t *
make_edge(int dst, int weight)
{

	edgenode_t *edge = malloc(sizeof(edgenode_t));
	edge->dst = dst;
	edge->weight = weight;
	edge->next = NULL;
	return edge;
}

void
do_add_edge(graph_t *G, int src, int dst, int weight)
{
	edgenode_t	*head, *current, *edge;

	edge = make_edge(dst, weight);
	head = G->head[src];
	if((current = head) == NULL) {
		G->head[src] = edge;
		return;
	}
	while(current->next != NULL) {
		current = current->next;
	}
	current->next = edge;
	return;
}

void
add_edge(graph_t *G, int src, int dst, int weight)
{

	edgenode_t	*head, *current, *edge;

	do_add_edge(G, src, dst, weight);
	if(!(G->flags & GRAPH_DIRECTED)) {
		do_add_edge(G, dst, src, weight);
	}
	return;
}

minheap_t *
init_minheap(int capacity)
{
	minheap_t	*mh;
	
	mh = malloc(sizeof(minheap_t));
	mh->pos = malloc(sizeof(int) * capacity);
	mh->data = malloc(sizeof(mhnode_t) * capacity);
	mh->capacity = capacity;
	return mh;
}

void
deinit_minheap(minheap_t *heap)
{

	free(heap->pos);
	free(heap->data);
	free(heap);
	return;
}

bool
minheap_exists(minheap_t *heap, int vertex)
{

	return heap->pos[vertex] < heap->size;
}

bool
minheap_empty(minheap_t *heap)
{

	return heap->size == 0;
}



void
decrease_key(minheap_t *heap, int vertex, int dist)
{
	int		pvidx, vidx;
	mhnode_t	*mhn, *pmhn;

	/*
	 * Find the index of this vertex in the min-heap.
	 */

	vidx = heap->pos[vertex];
	mhn = &heap->data[vidx];
	assert(mhn->vertex == vertex);
	mhn->dist = dist;
	while(1) {
		
		/*
		 * If we're at root, we're done.
		 */

		if(vidx <= 0) {
			break;
		}
		pvidx = PARENT(vidx);
		pmhn = &heap->data[pvidx];
		assert(heap->pos[pmhn->vertex] == pvidx);
		if(pmhn->dist < mhn->dist) {
			break;
		}
		heap->pos[mhn->vertex] = pvidx;
		heap->pos[pmhn->vertex] = vidx;
		swap(&heap->data[pvidx], &heap->data[vidx]);
		vidx = pvidx;
	}
	return;
}

void
min_heapify(minheap_t *heap)
{
	int		i, swapidx;
	mhnode_t	*large_mhn, *mhn, *rmhn, *lmhn;

	/*
	 * Start from the parent of last node in the heap.
	 */

	for(i = PARENT(heap->size - 1); i >= 0; i--) {
		large_mhn = mhn = &heap->data[i];
		if(LEFT_CHILD(i) <= heap->size - 1) {
			lmhn = &heap->data[LEFT_CHILD(i)];
			if(lmhn->dist < large_mhn->dist) {
				large_mhn = lmhn;
				swapidx = LEFT_CHILD(i);
			}
		}
		if(RIGHT_CHILD(i) <= heap->size - 1) {
			rmhn = &heap->data[RIGHT_CHILD(i)];
			if(rmhn->dist < large_mhn->dist) {
				large_mhn = rmhn;
				swapidx = RIGHT_CHILD(i);
			}
		}
		if(large_mhn != mhn) {
			heap->pos[large_mhn->vertex] = i;
			heap->pos[mhn->vertex] = swapidx;
			swap(&heap->data[i], &heap->data[swapidx]);
		}
	}
	return;
}

mhnode_t *
extract_min(minheap_t *heap)
{
	mhnode_t	*min, *root, *lastnode;

	if(minheap_empty(heap)) {
		return NULL;
	}
	root = &heap->data[0];	
	lastnode = min = &heap->data[heap->size - 1];
	heap->pos[root->vertex] = heap->size - 1;
	heap->pos[lastnode->vertex] = 0;
	swap(&heap->data[0], &heap->data[heap->size - 1]);
	heap->size--;
	min_heapify(heap);
	return min;
}

void
print_path(int *parent, int i)
{

	if(parent[i] == -1) {
		return;
	}
	print_path(parent, parent[i]);
	printf(" %d ", i);
	return;
}

/*
 * Initialize a distance array - distance of each node from given 'src'.
 * as INT_MIN and insert these values into min-heap.
 * Set dist[src] = 0 and decrease key of 'src' in min-heap
 *
 * Until heap is empty:
 *	extract vertex 'u' from heap, whose dist[u] is minimum
 	(first extract_min will return source)
 *	for each neighbouring vertext 'v' of 'u':
 *		if dist[v] < graph[u][v] + dist[u]
 *			dist[v] = graph[u][v] + dist[u];
 *			decrease_key of 'v' in min-heap
 */

void
dijkstra(graph_t *G, int src)
{
	int		dist[G->nvertex];
	int		parent[G->nvertex];
	int		i, u, v;
	mhnode_t	*mhn;
	minheap_t	*heap;
	edgenode_t	*head, *current;

	heap = init_minheap(G->nvertex);
	for(i = 0; i < G->nvertex; i++) {
		dist[i] = INT_MAX;
		parent[i] = -1;
		mhn = &heap->data[i];
		mhn->dist = INT_MAX;
		mhn->vertex = i;
		heap->pos[i] = i;
	}
	heap->size = G->nvertex;
	dist[src] = 0;
	decrease_key(heap, src, dist[src]);
	while(!minheap_empty(heap)) {
		mhn = extract_min(heap);
		u = mhn->vertex;
		head = G->head[u];
		current = head;
		while(current != NULL) {
			v = current->dst;
			if(current->weight + dist[u] < dist[v]) {
				dist[v] = dist[u] + current->weight;
				decrease_key(heap, v, dist[v]);
				parent[v] = u;
			}
			current = current->next;
		}
	}
	deinit_minheap(heap);
	printf("src->dst\t\tdist\t\tpath\n");
	for(i = 0; i < G->nvertex; i++) {
		printf("%d -> %d\t\t%d\t\t%d ", src, i, dist[i], src);
		print_path(parent, i);
		printf("\n");
	}
	return;
}

void
print_neighbours(graph_t *G)
{
	int		i;
	edgenode_t	*head, *current;

	for(i = 0; i < G->nvertex; i++) {
		head = G->head[i];
		printf("Node: %d\n", i);
		current = head;
		while(current) {
			printf("\t %d -> %d (%d)\n", i, current->dst, current->weight);
			current = current->next;
		}
	}
	return;
}

int
main(int argc, char *argv[])
{
	graph_t	*G;

	G = init_graph(9, 15, true, false);
	add_edge(G, 0, 1, 4);
	add_edge(G, 0, 7, 8);
	add_edge(G, 1, 2, 8);
	add_edge(G, 1, 7, 11);
	add_edge(G, 2, 3, 7);
	add_edge(G, 2, 8, 2);
	add_edge(G, 2, 5, 4);
	add_edge(G, 3, 4, 9);
	add_edge(G, 3, 5, 14);
	add_edge(G, 4, 5, 10);
	add_edge(G, 5, 6, 2);
	add_edge(G, 6, 7, 1);
	add_edge(G, 6, 8, 6);
	add_edge(G, 7, 8, 7);
	
	//print_neighbours(G);
	dijkstra(G, 0);
	deinit_graph(G);
	return 0;
}

