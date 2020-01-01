#include <stdio.h>
#include <stdlib.h>

void
swap(int *a, int *b)
{

	int c = *a;
	*a = *b;
	*b = c;
	return;
}

void
reverse(int *arr, int low, int high)
{

	while(low < high) {
		//printf("swapping arr[%d] and arr[%d]\n",
		//	low, high);
		swap(&arr[low], &arr[high]);
		low++;
		high--;
	}
	return;
}

void
nextPermutation(int *nums, int numsSize)
{
	int	i, j, maxidx;
	

	for(i = numsSize - 1; i > 0; i--) {
		if(nums[i] > nums[i - 1]) {
			break;
		}
	}
	if(i == 0) {
		goto reverse;
	}
	//printf("pivot - i: %d, nums[i]: %d\n", i - 1, nums[i - 1]);
	maxidx = -1;
	for(j = numsSize - 1; j >= i; j--) {
		if(nums[j] > nums[i - 1] && maxidx == -1) {
			maxidx = j;
		}
		if(maxidx != -1 && nums[j] < nums[maxidx]) {
			maxidx = j;
		}
	}
	//printf("maxidx - %d nums[maxidx] - %d\n", maxidx, nums[maxidx]);
	swap(&nums[i - 1], &nums[maxidx]);
	//printf("nums[i - 1]: %d nums[maxidx]: %d\n", nums[i - 1], nums[maxidx]);

reverse:
	//printf("reversing [%d .... %d]\n", i, numsSize - 1);
	reverse(nums, i, numsSize - 1);
	return;
}

int
main(int argc, char *argv[]) {
	int i, j, n, arr[] = {1, 2, 3, 4, 5};

	n = sizeof(arr)/sizeof(arr[0]);
	for(j = 0; j < n; j++) {
		printf("%d", arr[j]);
	}
	printf("\n");
	for(i = 0; i < 119; i++) {
		nextPermutation(arr, n);
		for(j = 0; j < n; j++) {
			printf("%d", arr[j]);
		}
		printf("\n");
	}
	return 0;
}




