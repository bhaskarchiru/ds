/*
 * Leetcode 42. Rain water
 * Given n non-negative integers representing an elevation map where the width of each bar is 1, 
 * compute how much water it is able to trap after raining.
 */

#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <stdbool.h>

#define MAX(a, b)   ((a) > (b) ? (a) : (b))

typedef struct stackele {
	int	num;
	int	max;
} stackele_t;

typedef struct stack {
	stackele_t	*data;
	int		top;
	int		capacity;
} stack_t;

stack_t *
init_stack(int capacity)
{
	stack_t *s = malloc(sizeof(stack_t));
	s->data = malloc(sizeof(stackele_t) * capacity);
	s->top = -1;
	s->capacity = capacity;
	return s;
}

void
deinit_stack(stack_t *s)
{

	free(s->data);
	free(s);
	return;
}

int
push(stack_t *s, int num)
{
	stackele_t  *ele, *tele;
        
	if(s->top == -1) {
		ele = &s->data[++s->top];
		ele->num = num;
		ele->max = num;
		return num;
	}
						    
	tele = &s->data[s->top];
	if(num >= tele->max) {
		s->top = -1;
		ele = &s->data[++s->top];
		ele->num = num;
		ele->max = num;
		return num;
	}
	ele = &s->data[++s->top];
	ele->num = num;
	ele->max = tele->max;
	return tele->max;
}

int
pop(stack_t *s, int *num)
{
	stackele_t  ele;

	if(s->top == -1) {
		return INT_MIN;
	}
	ele = s->data[s->top--];
	*num = ele.num;
	return ele.max;
}

bool
is_empty(stack_t *s)
{

	return s->top == -1;
}

int trap(int* height, int heightSize)
{
	int	prevnum, num, i, max, water = 0;
	stack_t	*s;
        
	    
	for(i = 0; i < heightSize; i++) {
		if(height[i] != 0) {
			break;
		}
	}    
	if(i == heightSize) {
		return 0;
	}
	s = init_stack(heightSize - i);
	for(; i < heightSize; i++) {
		max = push(s, height[i]);
		water += max - height[i];
	}
	printf("So far %d units\n", water);
	prevnum = INT_MIN;
	while(!is_empty(s)) {
		max = pop(s, &num);
		if(prevnum > num) {
			water -= (max - prevnum);
		} else {
			prevnum = num;
			water -= (max - num);
		}
	}

	deinit_stack(s);
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
