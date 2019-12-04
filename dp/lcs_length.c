#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX(a, b) ((a) < (b) ? (b) : (a))

int **
init_tbl(int m, int n)
{
	int	**tbl, i;

	tbl = (int **)malloc(sizeof(int *) * m);
	for(i = 0; i < m; i++) {
		tbl[i] = malloc(sizeof(int) * n);
	}
	return tbl;
}

void
deinit_tbl(int **tbl, int m)
{
	int	i;

	for(i = 0; i < m; i++) {
		free(tbl[i]);
	}
	free(tbl);
	return;
}

int
LCS(char *str1, char *str2)
{
	int	i, j, result = 0;
	int	m, n;
	int	**tbl;

	m = strlen(str1) + 1;
	n = strlen(str2) + 1;

	tbl = init_tbl(m, n);
	for(i = 0; i < m; i++) {
		tbl[i][0] = 0;
	}
	for(i = 0; i < n; i++) {
		tbl[0][i] = 0;
	}
	for(i = 1; i < m; i++) {
		for(j = 1; j < n; j++) {
			if(str1[i - 1] == str2[j - 1]) {
				tbl[i][j] = 1 + tbl[i - 1][j - 1];
			} else {
				tbl[i][j] = MAX(tbl[i - 1][j], tbl[i][j - 1]);
			}
		}
	}
	result = tbl[m - 1][n - 1];
	deinit_tbl(tbl, m);
	return result;
}


int
main(int argc, char *argv[])
{
	char	*str1 = "abcdefghijkl";
	char	*str2 = "acegik";

	printf("LCS of %s and %s is %d\n", str1, str2, LCS(str1, str2));
	return 0;
}
