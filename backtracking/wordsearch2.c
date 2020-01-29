/*
 * 212. Word Search II
 */

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

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
        int     i, j;                                                           

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
	int             i, j, **visited;                                        
	bool            result = false;                                         
	char            str[strlen(word) + 1];                                  
	
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
	for(i = 0; i < boardSize; i++) {
		free(visited[i]);
	}
	free(visited);
	return result;                                                          
}

/**
 * Note: The returned array must be malloced, assume caller calls free().
  */
char ** findWords(char** board, int boardSize, int *boardColSize, char ** words, int wordsSize, int* returnSize)
{
	int     idx = 0, ii, asz = 8;
        char    **result;
	      
	result = (char **)calloc(1, sizeof(char *) * asz);
	for(ii = 0; ii < wordsSize; ii++) {
		if(exist(board, boardSize, boardColSize, words[ii])) {
			if(idx + 1 == asz) {
				asz <<= 1;
				result = realloc(result, sizeof(char *) * asz);
			}
			result[idx++] = strdup(words[ii]);
		}
	}
	*returnSize = idx;
	return result;
}

int
main(int argc, char *argv[])
{
	int	rowsize = 4, colsize = 4, resultsz, ii;
	char	**results;
	char	*board[] = {"oaan", "etae", "ihkr", "iflv"};
	char	*words[] = {"oath", "pea", "eat", "rain"};

	results = findWords(board, rowsize, &colsize, words, 4, &resultsz);	
	for(ii = 0; ii < resultsz; ii++) {
		printf("%s\t", results[ii]);
	}
	printf("\n");
	for(ii = 0; ii < resultsz; ii++) {
		free(results[ii]);
	}
	free(results);
	return 0;
}
