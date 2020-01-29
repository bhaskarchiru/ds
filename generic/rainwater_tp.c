/*
 * Leetcode 42. Rain water
 * Given n non-negative integers representing an elevation map where the width of each bar is 1, 
 * compute how much water it is able to trap after raining.
 * Using two pointer technique
 */

#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <stdbool.h>

int trap(int* height, int heightSize)
{
	int	*L = height;
	int	*R = L + heightSize - 1;
	int	lower, level = 0, water = 0;

	while(L < R) {
		printf("*L %d *R %d level %d lower %d, water %d\n",
		       *L, *R, level, lower, water);
		lower = *L < *R ? *L++ : *R--;
		if(lower > level) {
			level = lower;
		}
		water += level - lower;
	}
	return water;    
}

int
main(int argc, char *argv[])
{
	int	heights[] = {5,5,1,7,1,1,5,2,7,6};
	int	n = sizeof(heights)/sizeof(heights[0]);

	printf("Rain water trapped is %d units\n", trap(heights, n));
	return 0;
}
