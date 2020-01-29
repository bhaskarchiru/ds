/*
 * 17. Letter Combinations of a Phone Number
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

#define CHAR_TO_IDX(c)	((int)c - 50)

char *strings[] = {
	"abc",
	"def",
	"ghi",
	"jkl",
	"mno",
	"pqrs",
	"tuv",
	"wxyz",
};

void
generateLetterCombinations(char *digits, char *str, int idx, int lidx, slist_t *slist)
{
	int	ii;
	char	c, *comb;

	if(idx == lidx) {
		slist_add(slist, str);
		return;
	}
	c = digits[idx];

	/*
	 * How many choices for we've for c.
	 */

	comb = strings[CHAR_TO_IDX(c)];
	for(ii = 0; ii < strlen(comb); ii++) {
		str[idx] = comb[ii];
		generateLetterCombinations(digits, str, idx + 1, lidx, slist);
	}
	return;
}

char **
letterCombinations(char *digits, int *returnSize)
{
	int		i;
	char		*str, **result;
	size_t		len;
	slist_t		*slist;

	slist = slist_init(8);
	len = strlen(digits);
	str = calloc(1, len + 1);
	generateLetterCombinations(digits, str, 0, len, slist);
	result = (char **)malloc(sizeof(char *) * slist->size);
	for(i = 0; i < slist->size; i++) {
		result[i] = slist->strings[i];
		slist->strings[i] = NULL;
	}
	*returnSize = slist->size;
	slist_deinit(slist);
	free(str);
	return result;
}

int
main(int argc, char *argv[])
{
	int	ii, resultsz = 0;
	char	**result;
	char	*num = "23";

	result = letterCombinations(num, &resultsz);
	for(ii = 0; ii < resultsz; ii++) {
		printf("%s\n", result[ii]);
	}
	for(ii = 0; ii < resultsz; ii++) {
		free(result[ii]);
	}
	free(result);
	return 0;
}
