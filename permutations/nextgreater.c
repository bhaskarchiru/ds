/*
 * Next greater element.
 */

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <assert.h>
#include <limits.h>

void
swap(int *a, int *b)
{
	int c = *a;
	*a = *b;
	*b = c;
	return;
}

/*
 * low = 0 high = 1 
 *	i = 0; i < 1; i++
 *		swap(&arr[0], &arr[1])
 *
 * low = 0 high = 2
 *	i = 0; i < 2; i++
 *		swap(&arr[0], &arr[2]);
 *		swap(&arr[1], &arr[1]);
 */

void
reverse(int *arr, int low, int high)
{
	int	i;

	for(i = 0; i < (low + high) / 2 + 1; i++) {
		swap(&arr[low + i], &arr[high - i]);
	}
	return;
}

int
nextGreaterNumber(int n)
{
	int	i = 0, j, numdigit, tmp, arr[16] = {0};
	int	next, maxidx;

	/*
	 * Break the number into array of digits,
	 * arr[n]arr[n-1]....arr[0]
	 */

	tmp = n;
	while(tmp) {
		arr[i] = tmp % 10;
		tmp /= 10;
		i++;
	}

	/*
	 * Identify the longest prefix that is non-decreasing, this prefix
	 * is already the highest permutation, so the element just after
	 * this prefix will be our pivot.
	 */

	numdigit = i;
	for(i = 1; i < numdigit; i++) {
		if(arr[i] < arr[i - 1]) {
			break;
		}
	}

	/*
	 * arr[i] is our pivot, if we break out of above loop, without ever
	 * finding such element, then we cant find next permutation which
	 * will be greater than the given number.
	 */

	if(i == numdigit) {
		return -1;
	}

	/*
	 * Find smallest element in prefix, which is greater than pivot.
	 */

	maxidx = -1;
	for(j = 0; j < i; j++) {
		if(arr[j] > arr[i] && maxidx == -1) {
			maxidx = j;
		}
		if(maxidx != -1 && arr[j] < arr[maxidx]) {
			maxidx = j;
		}
	}

	/*
	 * Interchange pivot and next greatest element to pivot in prefix.
	 */

	swap(&arr[i], &arr[maxidx]);

	/*
	 * Reverse the prefix
	 */

	reverse(arr, 0, i - 1);

	/*
	 * Reconstruct the number from digit array, carefully looking out
	 * for integer overflow, if we are going to overflow, just return -1.
	 */

	next = 0;
	for(i = numdigit; i >= 0; i--) {
		if(next > INT_MAX / 10) {
			next = -1;
			break;
		}
		next = next * 10;
		if(next > INT_MAX - arr[i]) {
			next = -1;
			break;
		}
		next += arr[i];
	}
	return next;
}

int
main(int argc, char *argv[])
{
	int	i, n, next;

	srand(time(NULL));
	for(i = 0; i < 100000; i++) {
		n = rand() % INT_MAX;
		next = nextGreaterNumber(n);
		printf("n: %d next: %d\n", n, next);
		assert(next > n || next == -1);
	}
	return 0;
}
