/*
 * 60. Permutation Sequence
 */

#include <stdio.h>
#include <stdlib.h>

void
swap(int *a, int *b)
{
	int	c = *a;
	*a = *b;
	*b = c;
	return;
}

void
reverse(int *arr, int low, int high)
{

	while(low < high) {
		swap(&arr[low], &arr[high]);
		low++;
		high--;
	}
	return;
}

void
nextPermutation(int *arr, int n)
{

	int	i, j, maxidx;

	/*
	 * Find pivot - element just after non-decreasing suffix.
	 * If no pivot found, just reverse the permutation.
	 * Find smallest element which is larger than pivot in the suffix.
	 * Exchange pivot and the element found in previous step.
	 * Reverse suffix.
	 */

	for(i = n - 1; i > 0; i--) {
		if(arr[i - 1] < arr[i]) {
			break;
		}
	}
	
	/*
	 * Pivot is arr[i - 1]
	 */

	if(i == 0) {
		
		/*
		 * Did not find the pivot, just reverse the permutation.
		 */

		goto reverse;
	}
	maxidx = -1;
	for(j = n -1; j >= i; j--) {
		if(arr[j] > arr[i - 1] && maxidx == -1) {
			maxidx = j;
		}
		if(maxidx != -1 && arr[maxidx] > arr[j]) {
			maxidx = j;
		}
	}
	swap(&arr[i - 1], &arr[maxidx]);

reverse:
	reverse(arr, i, n - 1);
	return;
}

char * getPermutation(int n, int k)
{
	int	arr[n], i, j = 1, num;
	char	*result;
	size_t	resultsz;

	for(i = n - 1; i >= 0; i--) {
		arr[i] = j++;
	}
	for(i = 0; i < k; i++) {
		nextPermutation(arr, n);
	}
	num = 0;
	for(i = 0; i < n; i++) {
		num = num * 10 + arr[i];
	}
	resultsz = snprintf(NULL, 0, "%d", num);
	result = malloc(resultsz + 1);
	sprintf(result, "%d", num);
	return result;
}

int
main(int argc, char *argv[])
{

	printf("Permutation: %s\n", getPermutation(3, 3));
	return 0;
}
