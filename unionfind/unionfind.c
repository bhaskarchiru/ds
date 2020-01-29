
/*
 * Implementation of union-find data structure.
 *  - does both union-by-rank and path compression.
 */

#include <stdio.h>
#include <stdlib.h>


typedef struct unionfind {
	int	*parent;
	int	*rank;
	int	size;
} unionfind_t;

unionfind_t *
uf_init(int n)
{

	unionfind	*uf;

	uf = malloc(sizeof(unionfind_t));
	uf->parent = malloc(sizeof(int) * n);
	uf->rank = malloc(sizeof(int) * n);
	for(i = 0; i < n; i++) {
		uf->parent[i] = i;
		uf->rank[i] = 1;
	}
	return uf;
}

void
uf_deinit(unionfind_t *uf)
{

	free(uf->parent);
	free(uf->rank);
	free(uf);
	return;
}

/*
 * Given an element, return the representative element.
 */

int
find(unionfind_t *uf, int x)
{

	while(uf->parent[x] != x) {
		x = uf->parent[x];
	}
	return x;
}

/*
 * Union of two sets.
 */

int
do_union(unionfind_t *uf, int x, int y)
{
	int	root_x, root_y;

	root_x = find(uf, x);
	root_y = find(uf, y);

	if(uf->rank[root_x] < uf->rank[root_y]) {
		uf->parent[x] = root_y;
	} else {
		uf->parent[y] = root_x;	
	}
	return;
}

void
print_set(unionfind_t	*uf)
{

}

int
main(int argc, char *argv[]) 
{


	return 0;
}
