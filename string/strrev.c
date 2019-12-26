#include <stdio.h>
#include <string.h>

void
swap(char *a, char *b)
{
	int	c = *a;
	*a = *b;
	*b = c;
	return;
}

void reverseString(char* s, int sSize){
	char  tmp, *L, *R;

	if(s == NULL || sSize == 0) return;
	L = s;
	R = s + sSize - 1;
	while(L < R) {
		swap(L, R);
		L++;
		R--;
	}
	return;
}

int
main(int argc, char *argv[])
{
	char	s[] = "hello";
	printf("Given string: %s ", s);
	reverseString(s, strlen(s));
	printf("Reverse: %s\n", s);
	return 0;
}

