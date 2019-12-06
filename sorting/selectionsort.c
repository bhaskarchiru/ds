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

int
select_min(int *a, int sidx, int eidx)
{
	int i, minidx;

	minidx = sidx;
	for(i = sidx + 1; i < eidx; i++) {
		if(a[i] < a[minidx]) {
			minidx = i;
		}
	}
	return minidx;
}

void
selection_sort(int *a, int n)
{
	int	i, minidx, tmp;

	for(i = 0; i < n - 1; i++) {
		minidx = select_min(a, i + 1, n);
		if(a[minidx] < a[i]) {
			tmp = a[i];
			a[i] = a[minidx];
			a[minidx] = tmp;
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
	selection_sort(a, n);
	print_arr(a, n);
	return 0;
}
