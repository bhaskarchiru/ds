/*
 * Floyd-warshall all pairs shortest path
 */

#include <stdio.h>
#include <stdlib.h>
#include <stdlib.h>
#include <limits.h>

#define	V	4
#define INF	999999	

void
floyd_warshall(int G[][V])
{
	int i, j, k, dist[V][V];

	for(i = 0; i < V; i++) {
		for(j = 0; j < V; j++) {
			dist[i][j] = G[i][j];
		}
	}

	/*
	 * For each <src, dst> , pick intermediate vertices.
	 */

	for(k = 0; k < V; k++) {

		/*
		 * Pick all vertices as source one by one.
		 */

		for(i = 0; i < V; i++) {

			/*
			 * Pick all vertices as destination for the above source.
			 * If we can reach 'j' from 'i' through 'k' in cheap, then
			 * add 'k' to the path between 'i' and 'j'.
			 */

			for(j = 0; j < V; j++) {
				if(dist[i][k] + dist[k][j] < dist[i][j]) {
					dist[i][j] = dist[i][k] + dist[k][j];
				}
			}
		}
	}
	for(i = 0; i < V; i++) {
		for(j = 0; j < V; j++) {
			if(dist[i][j] == INF) {
				printf(" %8s", "INF");
			} else {
				printf(" %8d ", dist[i][j]);
			}
		}
		printf("\n");
	}
	return;
}

int
main(int argc, char *argv[])
{
	int G[][V] = {{0, 5, INF, 10},
		      {INF, 0, 3, INF},
		      {INF, INF, 0, 1},
		      {INF, INF, INF, 0}};

	floyd_warshall(G);
	return 0;
}
