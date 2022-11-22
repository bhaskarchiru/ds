/*
 * Leetcode - 217
 * 217. Contains Duplicate
 * Given an integer array nums, return true if any value appears at least twice in the array, and return false if every element is distinct.
 * 1 <= nums.length <= 10^5
 * -10^9 <= nums[i] <= 10^9
 */

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <limits.h>
#include <string.h>

bool containsDuplicate(int* nums, int numsSize){
    int hash[100000];
    int displace, slot;

   memset(hash, -1, sizeof(int) * 100000);
   for(int ii = 0; ii < numsSize; ii++) {
       displace = 1000000000 + nums[ii];
       slot = displace % 7773;
      while(hash[slot] != -1) {
      	if(hash[slot] == displace) return true;
	slot++;
      }
      hash[slot] = displace;
    }
    return false;
}

int
main(int argc, char *argv[])
{
	int nums[] = {1, 2, 3, 1};

	printf("Given array %s duplicates\n",
	       containsDuplicate(nums, sizeof(nums)/sizeof(nums[0])) ? "contains" : "doesn't contain");
	return 0;
}
