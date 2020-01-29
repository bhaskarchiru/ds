/*
 * 79. Word Search
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

int neighbours[][2] = {{-1, 0}, {0, -1}, {0, 1}, {1, 0}};

bool
checkExists(char **board, int rownum, int colnum, int numrow, int numcol,
	    char *word, int idx, int lidx, int **visited)
{
	int     ii, nextrow, nextcol;
	bool    result = false;

	visited[rownum][colnum] = 1;
	if(idx == lidx) {
		if(board[rownum][colnum] == word[idx]) {
			return true;
		}
		return false;
	}
	if(board[rownum][colnum] != word[idx]) {
		return false;
	}
	for(ii = 0; ii < 4; ii++) {
		nextrow = rownum + neighbours[ii][0];
		nextcol = colnum + neighbours[ii][1];
		if(nextrow >= 0 && nextrow < numrow &&
		   nextcol >= 0 && nextcol < numcol) {

		   	/*
			 * If we've already visited the neighbour in this
			 * context, skip it.
			 */

			if(visited[nextrow][nextcol]) {
				continue;
			}
	
			/*
			 * Check if we can find the match by going to 
			 * this neighbour.
			 */

			if(checkExists(board, nextrow, nextcol, numrow, numcol,
				       word, idx + 1, lidx, visited)) {
				result = true;
				break;
			}

			/*
			 * Nope, backtrack.
			 */

			visited[nextrow][nextcol] = 0;	
		}
	}   
	return result;
}

void
reset_visited(int **visited, int numrow, int numcol)
{
	int	i, j;

	for(i = 0; i < numrow; i++) {
		for(j = 0; j < numcol; j++) {
			visited[i][j] = 0;
		}
	}
	return;
}

bool 
exist(char **board, int boardSize, int *boardColSize, char *word)
{
	int		i, j, **visited;
	bool		result = false;
	char		str[strlen(word) + 1];

	visited = (int **)calloc(1, sizeof(int *) * boardSize);
	for(i = 0; i < boardSize; i++) {
		visited[i] = calloc(1, sizeof(int) * *boardColSize);
	}
	for(i = 0; i < boardSize; i++) {
		for(j = 0; j < *boardColSize; j++) {
			if(board[i][j] != word[0]) {
				continue;
			}
			if(checkExists(board, i, j, boardSize, *boardColSize,
				       word, 0, strlen(word) - 1, visited)) {
				result = true;
				break;
			}
			reset_visited(visited, boardSize, *boardColSize);
		}
	}
	return result;
}

int
main(int argc, char *argv[])
{
	bool	exists;
#if 0
	int	rowsize = 3, colsize = 4;
	char 	*board[] = { "ABCE", "SFCS", "ADEE"};
	char	*word = "SEE";

	int	rowsize = 2, colsize = 1;
	char	*board[] = { "a", "a" };
	char	*word = "aaa";
#endif

	int	rowsize = 2, colsize = 2;
	char	*board[] = { "ab", "cd" };
	char	*word = "acdb";

	exists = exist(board, rowsize, &colsize, word); 
	printf("Path %s %s exists in the board\n",
	       word, exists ? "does" : "does not");
	return 0;
}
