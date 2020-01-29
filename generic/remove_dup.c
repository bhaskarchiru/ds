
/*
 * Remove duplicates from a sorted array.
 */

#include <stdio.h>
#include <stdlib.h>

int removeDuplicates(int *nums, int numsSize){
	int i, j, k, m, len;
	int lastidx;

	if(numsSize < 2) {
		return numsSize;
	}
      
	len = numsSize;
	lastidx = numsSize - 1;
	i = 0;
	while( i < len - 1) {
		j = k = i + 1;
		while(k < len && nums[k] == nums[i]) {
			k++;
		}
		if(j == k) {
			i++;
			continue;
		} 
		len -= (k - j);
		for(m = j; m < lastidx - (k - j) + 1; m++) {
			printf("Moving %d to %d\n",
			       m + k - j, m);
			nums[m] = nums[m + k - j];
		}
		lastidx -= (k - j);
		i++;
	}
	return len;
}

void
print_arr(int *nums, int numsSize)
{
	int i;

	for(i = 0; i < numsSize; i++) {
		printf(" %d ", nums[i]);
	}
	printf("\n");
	return;
}

int
removeDuplicates2(int *nums, int numsSize) {
	int i, count = 0;
	for(i = 1; i < numsSize; i++) {
		if(nums[i] == nums[i - 1]) {
			count++;
		}
		nums[i - count] = nums[i];
		print_arr(nums, numsSize);
	}
	return numsSize - count;
}

int
main(int argc, char *argv[])
{
	int i, newlen;
	int arr[] = {0, 0, 1, 1, 1, 2, 2, 3, 3, 4};
	//int arr[] = {1, 1};
	//int arr[] = {1, 1, 1};
	//int arr[] = {1, 1, 1, 2};
	
	newlen  = removeDuplicates2(arr, sizeof(arr)/sizeof(arr[0]));
	for(i = 0; i < newlen; i++) {
		printf(" %d ", arr[i]);
	}
	printf("\n");
	return 0;
}
