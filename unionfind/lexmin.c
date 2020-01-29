/*
 * Lexicographically minimal string
 * You are given three strings named as A, B, and C.
 *	Here, the length of the strings  A and B is equal.
 * All strings contain lowercase English letters. The string A and B contain the following properties:

 *	The characters located at the same indexes in the string A and B are equivalent to each other. 
 *	If character 'a' is equivalent to character 'b', then the character 'b' is also equivalent
 *	to the character 'a'.
 *	If character 'a' is equivalent to character 'b' and character 'b' is equivalent to character 'c',
 *	then character 'a' is also equivalent to character 'c'/
 *	Every character is equivalent to itself.
 * For example:
 *	You are given two strings:
 *	A - abc
 *	B - xcd
 * Here, the character 'a' is equivalent to the character 'x', character 'b' is equivalent to the character 'c',
 * and character 'c' is equivalent to the character 'd'.
 * According to the third property, the character 'b' is also equivalent to the character 'd'.
 *
 *  You can replace any character of string C with its any equivalent character. By replacing any character of the string  with its
 * equivalent characters, you can construct multiple new strings. Your task is to print the lexicographically smallest
 * string out of all possible new strings that you can construct.
 *
 * Note: If the first character of s(s1) is smaller than the first character of t(t1) , then
 * the lexicographical order is an order relation where string s is smaller than string t.
 * If they are equivalent, the second character is checked and so on.
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct unionfind {
	int	parent[26];	/* Maximum possible set of numbers. */
	int	rank[26];
} unionfind_t;

#define CHAR_TO_IDX(a)		((int)a - 97)
#define IDX_TO_CHAR(idx)	((char)((idx) + 97))

int
find(unionfind_t *uf, int e1)
{

	while(e1 != uf->parent[e1]) {
		e1 = uf->parent[e1];
	}
	return e1;
}

void
do_union(unionfind_t *uf, int e1, int e2)
{

	e1 = find(uf, e1);
	e2 = find(uf, e2);
	if(uf->rank[e1] < uf->rank[e2]) {
		uf->parent[e2] = e1;
		uf->rank[e1]++;
	} else {
		uf->parent[e1] = e2;
		uf->rank[e2]++;
	}
	return;
}

char *
lexmin(char *A, char *B, char *C)
{
	int		i, idx1, idx2;
	char		*lex;
	size_t		len;
	unionfind_t	*uf = calloc(1, sizeof(unionfind_t));

	for(i = 0; i < 26; i++) {
		uf->parent[i] = i;
		uf->rank[i] = i;
	}
	len = strlen(A);
	lex = malloc(len + 1);
	for(i = 0; i < len; i++) {
		idx1 = CHAR_TO_IDX(A[i]);
		idx2 = CHAR_TO_IDX(B[i]);
		do_union(uf, idx1, idx2);
	}

	for(i = 0; i < len; i++) {
		idx1 = CHAR_TO_IDX(C[i]);
		idx1 = find(uf, idx1);
		lex[i] = IDX_TO_CHAR(idx1);
	}
	lex[i] = '\0';
	return lex;
}

int
main(int argc, char *argv[])
{
	char *A = "abc";
	char *B = "xyz";
	char *C = "yzp";

	printf("lexicographicaly minimal string: %s\n",
	        lexmin(A, B, C));
	return 0;
}
