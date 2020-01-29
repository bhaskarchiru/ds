/*
 * 4. Median of Two Sorted Arrays
 */

#include <stdio.h>
#include <limits.h>

#define MAX(A, B)	((A) > (B) ? (A) : (B))
#define MIN(A, B)	((A) < (B) ? (A) : (B))

double 
findMedianSortedArrays(int *nums1, int nums1Size, int *nums2, int nums2Size)
{
	int	idx, low, high;
	int	maxleft_1, minright_1, maxleft_2, minright_2;
	int	partition1, partition2;

	if(nums2Size > nums1Size) {
		return findMedianSortedArrays(nums2, nums2Size, nums1, nums1Size);
	}

#if 0
	if(nums1Size == 0 && nums2Size == 0) {
		return 0;
	} else if(nums1Size == 0) {
		low = 0;
		high = nums2Size;
		idx = (low + high) >> 1;
		if(nums2Size % 2) {
			return (double)nums2[idx];
		} else {
			return (double)(nums2[idx - 1] + nums2[idx]) / 2.0;
		}
	} else if(nums2Size == 0) {
		low = 0;
		high = nums1Size;
		idx = (low + high) >> 1;
		if(nums1Size % 2) {
			return (double)nums1[idx];
		} else {
			return (double)(nums1[idx - 1] + nums1[idx]) / 2.0;
		}
	}
#endif

	low = 0;
	high = nums1Size - 1;
	while(low <= high) {

		/*
		 * Partition1 is the starting index of right side partition
		 * of nums1, likewise for nums2.
		 */

		partition1 = ((low + high) >> 1) + 1;
		partition2 = ((nums1Size + nums2Size + 1) >> 1) + 1 - partition1;

		if(partition1 < high && nums2[partition2 - 1] > nums1[partition1]) {
			low = partition1 + 1;
		} else if(partition1 > low && nums1[partition - 1] > nums2[partition2]) {
			high = partition - 1;
		} else {

		/*
		 * If MAX on left side of first array is less than the MIN on
		 * right side of first array - this means every element on left
		 * side of first array is less than every element on right side
		 * of second array as well as first array(since it's sorted).
		 * 
		 * Complementary case for MAX on left side of second array
		 * vis-a-vis MIN on right side of first array.
		 *
		 * If both the conditions are true, then we've found perfect
		 * partition of both the arrays.
		 */

			maxLeft = 0;
			if(partition1 == 0) {
				maxLeft = num2[partition2 - 1];
			} else if(partition2 == 0) {
				maxLeft = nums1[partition1 - 1];
			} else {
				maxLeft = MAX(A[partition - 1], B[partition
			
			/*
			 * If combined array is of odd length, then the median
			 * is MAX of max left values.
			 */

			if((nums1Size + nums2Size) % 2) {
				return (double)(MAX(maxleft_1, maxleft_2));
			} else {

				/*
				 * Even length - average of MAX of left partitions
				 * and MIN of right partitions.
				 */

				return (double)(MAX(maxleft_1, maxleft_2) + 
						MIN(minright_1, minright_2)) / 2;
			}
		} else if(maxleft_1 > minright_2) {

			/*
			 * MAX on left side of first array is ahead of MIN on
			 * right side of second array, we went too far on
			 * right side, Go to left side, i.e. tilt partition
			 * line more towards the left.
			 */

			high = partition1 - 1;
		} else {
			low = partition1 + 1;
		}
	}
	return INT_MIN;
}

int
main(int argc, char *argv[])
{
	//int	arr1[] = {1, 4, 7, 9, 14, 22, 30};
	//int	arr2[] = {3, 5, 27, 31};//, 13, 17, 18, 21};
	int	arr1[] = {4};
	int	arr2[] = {1, 2, 3, 5, 6};
	int	n1, n2;

	n1 = sizeof(arr1)/sizeof(arr1[0]);
	n2 = sizeof(arr2)/sizeof(arr2[0]);

	printf("Median: %lf\n", 
	       findMedianSortedArrays(arr1, n1, arr2, n2));
	return 0;	
}
