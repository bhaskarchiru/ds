#include <stdio.h>
#include <stdlib.h>

void
partitions(int nums1Size, int nums2Size)
{

	int	low, high;
	int	parition1, partition2;

	if(nums1Size < nums2Size) {
		partition(nums2Size, nums1Size);
	}
	low = 0;
	high = nums1Size;
	
	

