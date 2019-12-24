
/*
 * Dijkstra's shortest path algorithm, graph is represented by adjancency matrix
 */

#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <stdbool.h>

#define	V	9

int
mindistance(int dist[], bool sptset[])
{
	int min_index, min = INT_MAX, i, j;

	for(i = 0; i < V; i++) {
		if(!sptset[i] && dist[i] <= min) {
			min = dist[i];
			min_index = i;
		}
	}
	return min_index;
}

/*
 * Initialize a distance array - distance of each node from given 'src'.
 * 	dist[src] = 0
 * Initialize sptset[] for all vertices as false, this set gets veritces
 * as shortest distance for the vertices from 'src' are calculated.
 *
 * for each vertex:
 *	select the vertex 'u', whose dist[u] is the minimum
 *		(first iteration will always selects source)
 *	sptset[u] = true
 *	for each neighbouring vertext 'v' of 'u':
 *		if dist[v] > graph[u][v] + dist[u]
 *			dist[v] = graph[u][v] + dist[u];
 */

void
dijkstra(int graph[V][V], int src)
{
	int	dist[V];
	bool	sptset[V];
	int	i, u, v;

	for(i = 0; i < V; i++) {
		dist[i] = INT_MAX;
		sptset[i] = false;
	}
	dist[src] = 0;
	for(i = 0; i < V; i++) {
		u = mindistance(dist, sptset);
		sptset[u] = true;
		for(v = 0; v < V; v++) {

			/*
			 * If this neighbour is already not in sptset AND
			 * If dist[u] is already relaxed further from inital INT_MAX AND
			 * Distance to reach 'v' is greater than 
			 *    distance to reach 'u + weight of edge (u, v)
			 */

			//if(!sptset[v] && graph[u][v] && dist[u] != INT_MAX &&
			if(graph[u][v] && dist[u] + graph[u][v] < dist[v]) {
			   dist[v] = dist[u] + graph[u][v];
			}
		}
	}
	for(i = 0; i < V; i++) {
		printf("Shortest distance from %d --> %d is %d\n", src, i, dist[i]);
	}
	return;
}

int
main(int argc, char *argv[])
{
	
	int graph[V][V] = { { 0, 4, 0, 0, 0, 0, 0, 8, 0 }, 
			    { 4, 0, 8, 0, 0, 0, 0, 11, 0 }, 
			    { 0, 8, 0, 7, 0, 4, 0, 0, 2 }, 
			    { 0, 0, 7, 0, 9, 14, 0, 0, 0 }, 
			    { 0, 0, 0, 9, 0, 10, 0, 0, 0 }, 
			    { 0, 0, 4, 14, 10, 0, 2, 0, 0 }, 
			    { 0, 0, 0, 0, 0, 2, 0, 1, 6 }, 
			    { 8, 11, 0, 0, 0, 0, 1, 0, 7 }, 
			    { 0, 0, 2, 0, 0, 0, 6, 7, 0 } };

	dijkstra(graph, 0);
	return 0;
}
