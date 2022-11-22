/*
 * Articulation points in a graph using DFS.
 */

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define GRAPH_WEIGHTED  0x0001
#define GRAPH_DIRECTED  0x0002

#define MIN(a, b)	((a) < (b) ? (a) : (b))

typedef struct edgenode {
        struct edgenode *next;
	int             dst;    /* Destination vertex */
	int             weight; /* Weight of the edge */
} edgenode_t;

typedef struct graph {
	edgenode_t      **head; /* Array of heads of linked lists for each vertex */
	int             nvertex;
	int             nedge;
	int             flags;
} graph_t;


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

void
do_discover_ap(graph_t *G, int u, bool visited[], int disc[], int low[], int parent[], bool ap[])
{
	edgenode_t	*head, *current;
	static int	time = 0;
	int		v, children = 0;

	visited[u] = true;
	disc[u] = low[u] = ++time;
	current = head = G->head[u];
	while(current) {
		v = current->dst;
		if(!visited[v]) {
			children++;
			parent[v] = u;
			do_discover_ap(G, v, visited, disc, low, parent, ap);
			low[u] = MIN(low[u], low[v]);
			if(parent[u] == -1 && children > 1) {
				ap[u] = true;
			}
			if(parent[u] != -1 && low[v] >= disc[u]) {
				ap[u] = true;
			}
		} else if(v != parent[u]) {
			low[u] = MIN(low[u], disc[v]);
		}
		current = current->next;
	}
	return;
}

int *
discover_ap(graph_t *G, int *arti_szp)
{
	int	i, j, arti_sz = 0;
	int	*arti = NULL;
	int	low[G->nvertex];
	int	disc[G->nvertex];
	int	parent[G->nvertex];
	bool	visited[G->nvertex];
	bool	ap[G->nvertex];

	for(i = 0; i < G->nvertex; i++) {
		parent[i] = -1;
		visited[i] = false;
		ap[i] = false;
	}
	for(i = 0; i < G->nvertex; i++) {
		if(visited[i] == false) {
			do_discover_ap(G, i, visited, disc, low, parent, ap);
		}
	}
	for(i = 0; i < G->nvertex; i++) {
		if(ap[i] == true) {
			arti_sz++;
		}
	}
	if(arti_sz == 0) {
		*arti_szp = 0;
		return NULL;
	}
	arti = calloc(1, sizeof(int) * arti_sz);
	for(i = 0, j = 0; i < G->nvertex; i++) {
		if(ap[i] == true) {
			arti[j] = i;
			j++;
		}
	}
	*arti_szp = arti_sz;
	return arti;
}

int
main(int argc, char *argv[])
{
	int	*arti, arti_sz, i;
	graph_t	*G = init_graph(5, 5, false, false);
	
	add_edge(G, 1, 0, 0);
	add_edge(G, 0, 2, 0);
	add_edge(G, 2, 1, 0);
	add_edge(G, 0, 3, 0);
	add_edge(G, 3, 4, 0);

	arti = discover_ap(G, &arti_sz);
	if(arti_sz == 0) {
		printf("No articulation points found in the given graph\n");
	} else {
		for(i = 0; i < arti_sz; i++) {
			printf(" %d ", arti[i]);
		}
		printf("\n");
		free(arti);
	}
	return 0;
}
