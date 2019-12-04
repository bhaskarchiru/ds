#include <stdio.h>
#include <stdlib.h>
#include <string.h>

enum direction {
	NONE = 1,
	DIAGONAL,
	LEFT,
	TOP
};

/*
 * Struct to describe each cell in the table.
 */

typedef struct cell {
	int	len;
	int	dir;
} cell_t;

/*
 * Struct to describe table itself, basically set of cells
 * and its size.
 */

typedef struct tbl {
	cell_t	*tbl_data;
	int	numrow;
	int	numcol;
} tbl_t;

tbl_t *
init_tbl(int m, int n)
{
	tbl_t	*tbl;

	tbl = (tbl_t *)malloc(sizeof(tbl_t));
	tbl->numrow = m;
	tbl->numcol = n;
	tbl->tbl_data = malloc(sizeof(cell_t) * tbl->numrow * tbl->numcol);
	return tbl;
}

void
deinit_tbl(tbl_t *tbl)
{

	free(tbl->tbl_data);
	free(tbl);
	return;
}

/*
 * Get cell [ii, jj], row-major order:
 *  ii * numcol + jj
 */

cell_t *
get_cell(tbl_t *tbl, int ii, int jj)
{

	return tbl->tbl_data + tbl->numcol * ii + jj;
}

void
write_cell(tbl_t *tbl, int ii, int jj, int len, int dir)
{

	cell_t	*cell;

	cell = tbl->tbl_data + tbl->numcol * ii + jj;
	cell->len = len;
	cell->dir = dir;
	return;
}


/*
 * Construct longest common subsequence of str1 and str2
 */

char *
LCS(char *str1, char *str2)
{
	int	i, j, k;
	char	*result;
	int	m, n;
	cell_t	*cell1, *cell2;
	tbl_t	*tbl;

	m = strlen(str1) + 1;
	n = strlen(str2) + 1;

	tbl = init_tbl(m, n);
	for(i = 0; i < m; i++) {
		write_cell(tbl, i, 0, 0, NONE);
	}
	for(i = 0; i < n; i++) {
		write_cell(tbl, 0, i, 0, NONE);
	}
	for(i = 1; i < m; i++) {
		for(j = 1; j < n; j++) {
			if(str1[i - 1] == str2[j - 1]) {
				cell1 = get_cell(tbl, i - 1, j - 1);
				write_cell(tbl, i, j, 1 + cell1->len, DIAGONAL);
			} else {
				cell1 = get_cell(tbl, i - 1, j);
				cell2 = get_cell(tbl, i, j - 1);
				if(cell1->len > cell2->len) {
					write_cell(tbl, i, j, cell1->len, TOP);
				} else {
					write_cell(tbl, i, j, cell2->len, LEFT);
				}
			}
		}
	}
	cell1 = get_cell(tbl, m - 1, n - 1);
	k = cell1->len;
	result = malloc(k + 1);
	result[k] = '\0';
	k--;
	i = m - 1;
	j = n - 1;
	while(k >= 0) {
		if(cell1->dir == DIAGONAL) {
			result[k] = str1[i - 1];
			k--;
			i--;
			j--;
			cell1 = get_cell(tbl, i, j);
		} else if(cell1->dir == TOP) {
			i--;
			cell1 = get_cell(tbl, i, j);
		} else {
			j--;
			cell1 = get_cell(tbl, i, j);
		}
	}
	deinit_tbl(tbl);
	return result;
}

int
main(int argc, char *argv[])
{
	char	*str1 = "bhaskar reddy";
	char	*str2 = "baeekrry";

	printf("LCS of %s and %s is %s\n", str1, str2, LCS(str1, str2));
	return 0;
}
