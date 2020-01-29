/*
 * 22. Generate Parentheses
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct slist {
	char	**strings;
	int	capacity;
	int	size;
} slist_t;

slist_t *
slist_init(int capacity)
{
	slist_t	*slist = calloc(1, sizeof(slist_t));
	slist->capacity = capacity;
	slist->strings = (char **)calloc(1, sizeof(char *) * slist->capacity);
	slist->size = 0;
	return slist;
}

void
slist_add(slist_t *slist, char *str)
{
	if(slist->size + 1 == slist->capacity) {
		slist->capacity <<= 1;
		slist->strings = realloc(slist->strings,
					 sizeof(char *) * slist->capacity);
	}
	slist->strings[slist->size++] = strdup(str);
	return;
}

void
slist_deinit(slist_t *slist)
{
	int	i;
	for(i = 0; i < slist->size; i++) {
		if(slist->strings[i]) {
			free(slist->strings[i]);
		}
	}
	free(slist->strings);
	free(slist);
	return;
}

/*
 * Recursively generate valid paren string and add it to slist.
 */

void
doGenerateParenthesis(int numleft, int numright, char *str, int idx, slist_t *slist)
{

	/*
	 * Have we consumed all the left and right parens? This forms a valid
	 * string, add it to slist.
	 */

	if(numleft == 0 && numright == 0) {
		slist_add(slist, str);
	}

	/*
	 * If there are more left parens to be added, we can add and reduce
	 * consumed left parens by 1, for next frame of recursion.
	 */

	if(numleft > 0) {
		str[idx] = '(';
		doGenerateParenthesis(numleft - 1, numright, str, idx + 1, slist);
	}

	/*
	 * We can't use right parens, without a left parens remaining.
	 */

	if(numleft < numright) {
		str[idx] = ')';
		doGenerateParenthesis(numleft, numright - 1, str, idx + 1, slist);
	}
	return;
}

char **
generateParenthesis(int n, int *returnSize)
{
	int	i;
	char	str[2 * n + 1];
	char	**result;
	slist_t	*slist;

	str[2 * n] = '\0';
	slist = slist_init(8);
	doGenerateParenthesis(n, n, str, 0, slist);
	result = (char **)calloc(1, sizeof(char *) * slist->size);
	for(i = 0; i < slist->size; i++) {
		result[i] = slist->strings[i];
		slist->strings[i] = NULL;
	}
	*returnSize = slist->size;
	slist_deinit(slist);
	return result;
}

int
main(int argc, char *argv[])
{
	char	**result;
	int	i, resultsz = 0;

	result = generateParenthesis(3, &resultsz);
	for(i = 0; i < resultsz; i++) {
		printf("%s\n", result[i]);
	}
	for(i = 0; i < resultsz; i++) {
		free(result[i]);
	}
	free(result);
	return 0;
}
