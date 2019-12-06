#include <stdio.h>
#include <stdlib.h>

void
print_arr(int *a, int n)
{
	int	i;

	for(i = 0; i < n; i++) {
		printf(" %d ", a[i]);
	}
	printf("\n");
	return;
}

void
insertion_sort(int *a, int n)
{
	int	i, j, tmp;

	for(i = 1; i < n; i++) {
		for(j = i; j > 0; j--) {
			if(a[j] > a[j - 1]) {
				continue;
			}
			tmp = a[j];
			a[j] = a[j - 1];
			a[j - 1] = tmp;
		}
		print_arr(a, n);
	}
	return;
}

int
main(int argc, char *argv[])
{

	int i, n, a[] = {15, 7, 0, 22, 8, 12, 1, 14, 2, 6, 11, 5, 4, 10, 24, 3, 13, 9};

	n = sizeof(a)/sizeof(a[0]);
	print_arr(a, n);
	insertion_sort(a, n);
	print_arr(a, n);
	return 0;
}
