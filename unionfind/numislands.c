#include <stdio.h>
#include <stdlib.h>

#define MAX_NEIGHBOURS	8

struct neigh {
	int	rowdis;
	int	coldis;
};

struct neigh neighbors[] = { {-1, -1}, {-1, 0}, {-1, 1}, {0, -1},
			     {0, 1}, {1, -1}, {1, 0}, {1, 1}};

void
DFS(int grid[][5], int visited[][5], int i, int j, int numrow, int numcol)
{
	int k, l, m;

	visited[i][j] = 1;
	for(k = 0; k < MAX_NEIGHBOURS; k++) {
		l = i + neighbors[k].rowdis;
		m = j + neighbors[k].coldis;
		if(l < 0 || l >= numrow || m < 0 || m >= numcol) {
			continue;
		}
		if(grid[l][m] != 0 && visited[l][m] == 0) {
			printf(" -- DFS called for [%d %d]\n", l, m);
			DFS(grid, visited, l, m, numrow, numcol);
		}
	}
	return ;
}

int
num_islands(int grid[][5], int numrow, int numcol)
{
	int	count = 0;
	int	i, j;
	int	visited[numrow][numcol];

	for(i = 0; i < numrow; i++) {
		for(j = 0; j < numcol; j++) {
			visited[i][j] = 0;
		}
	}
	for(i = 0; i < numrow; i++) {
		for(j = 0; j < numcol; j++) {
			if(grid[i][j] != 0 && visited[i][j] == 0) {
				printf("DFS called for [%d %d]\n", i, j);
				DFS(grid, visited, i, j, numrow, numcol);
				count++;
			}
		}
	}
	return count;
}

int
main(int argc, char *argv[])
{

	int grid[][5] = { 1, 1, 0, 1, 0,
			  1, 1, 0, 1, 0,
			  1, 1, 0, 0, 0,
			  0, 0, 0, 1, 0,
			  1, 0, 1, 0, 1};
		
	printf("Number of islands: %d\n", num_islands(grid, 5, 5));
	int grid1[][5] = {1, 0, 1, 0, 1,
		     0, 1, 0, 1, 0,
		     1, 0, 1, 0, 1,
		     0, 1, 0, 1, 0,
		     1, 0, 1, 0, 1};
	printf("Number of islands: %d\n", num_islands(grid1, 5, 5));
	return 0;
}
