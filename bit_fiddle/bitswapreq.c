#include <stdio.h>
#include <stdlib.h>

int
main(int argc, char *argv[]) 
{
	int a = atoi(argv[1]);
	int b = atoi(argv[2]);
	
	int c, count = 0;
	for (c = a ^ b; c != 0; c &= c-1) {
		count++;
	}
	printf("count: %d\n", count);
	return 0;
}
