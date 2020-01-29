/*
 * 273. Integer to English Words
 */

#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <string.h>

char *ones[] = {
	"",
	"One",
	"Two",
	"Three",
	"Four",
	"Five",
	"Six",
	"Seven",
	"Eight",
	"Nine",
	"Ten",
	"Eleven",
	"Twelve",
	"Thirteen",
	"Fourteen",
	"Fifteen",
	"Sixteen",
	"Seventeen",
	"Eighteen",
	"Nineteen",
};

char *tens[] = {
	"",
	"",
	"Twenty",
	"Thirty",
	"Forty",
	"Fifty",
	"Sixty",
	"Seventy",
	"Eighty",
	"Ninety",
};

#define HUNDRED		"Hundred "
#define THOUSAND	"Thousand "
#define MILLION		"Million "
#define BILLION		"Billion "

#define SPACE		" "

void
print_one(int digit, char *result)
{
	if(digit) {
		strcat(result, ones[digit]);
	}
	return;
}

void
print_two(int digit1, int digit2, char *result)
{

	if(digit1 > 1) {
		strcat(result, tens[digit1]);
		if(digit2) {
			strcat(result, SPACE);
			strcat(result, ones[digit2]);
		}
	} else if(digit1 == 1) {
		strcat(result, ones[10 + digit2]);
	} else {
		strcat(result, ones[digit2]);
	}
	return;
}

void
reverse(int *arr, int highidx)
{
	int tmp, *start = arr;
	int *end = arr + highidx;

	while(start < end) {
		tmp = *start;
		*start = *end;
		*end = tmp;
		start++;
		end--;
	}
	return;
}

void
add_hundred(char *result)
{
	strcat(result, SPACE);
	strcat(result, HUNDRED);
	strcat(result, SPACE);
	return;
}

void
add_thousand(char *result)
{
	strcat(result, SPACE);
	strcat(result, THOUSAND);
	strcat(result, SPACE);
	return;
}

void
add_million(char *result)
{
	strcat(result, SPACE);
	strcat(result, MILLION);
	strcat(result, SPACE);
	return;
}

void
add_billion(char *result)
{
	strcat(result, SPACE);
	strcat(result, BILLION);
	strcat(result, SPACE);
	return;
}

char *
numberToWords(int num)
{
	char	*result;
	int	i, k = 0, digits[10], digit;

	/*
         *     1s - 1 digit
	 *    10s - 1 digit
	 *    100s - 1 digit
	 *   1000s - 3 digits
	 *  1000000s - 3 digits
	 * 1000000000 - 1 digit
	 */

	result = malloc(4096);
	result[0] = 0;
	if(num) {
		while(num) {
			digit = num % 10;
			digits[k++] = digit;
			num /= 10;
		}
	} else {
		strcat(result, "Zero");
		return result;
	}

	/*
	 * {1} 					- {1}
	 * {1, 2}				- {1, 2} 
	 * {1, 2, 3} 				- {1} {2, 3}
	 * {1, 2, 3, 4}				- {1} {2} {3, 4}
	 * {1, 2, 3, 4, 5}			- {1, 2} {3} {4, 5}
	 * {1, 2, 3, 4, 5, 6} 			- {1, 2, 3} {4}, {5, 6}
	 * {1, 2, 3, 4, 5, 6, 7}		- {1} {2, 3, 4} {5} {6, 7}
	 * {1, 2, 3, 4, 5, 6, 7, 8}		- {1, 2}, {3, 4, 5}, {6}, {7, 8}
	 * {1, 2, 3, 4, 5, 6, 7, 8, 9} 		- {1, 2, 3}, {4, 5, 6}, {7}, {8, 9}
	 * {1, 2, 3, 4, 5, 6, 7, 8, 9, 10}	- {1} {2, 3, 4}, {5, 6, 7}, {8}, {9, 10}
	 *
	 */

	reverse(digits, k - 1);
	switch(k) {
	case 1:
		print_one(digits[0], result);
		break;

	case 2:
		print_two(digits[0], digits[1], result);
		break;
	
	case 3:
		print_one(digits[0], result);
		add_hundred(result);
		if(digits[1] || digits[2]) {
			print_two(digits[1], digits[2], result);
		} else {
			result[strlen(result) - 1] = '\0';
		}
		break;
	
	case 4:
		print_one(digits[0], result);
		add_thousand(result);
		if(digits[1]) {
			print_one(digits[1], result);
			add_hundred(result);
		}
		if(digits[2] || digits[3]) {
			print_two(digits[2], digits[3], result);
		} else {
			result[strlen(result) - 1] = '\0';
		}
		break;
	
	case 5:
		print_two(digits[0], digits[1], result);
		add_thousand(result);
		if(digits[2]) {
			print_one(digits[2], result);
			add_hundred(result);
		}
		print_two(digits[3], digits[4], result);
		break;
	
	case 6:
		print_one(digits[0], result);
		add_hundred(result);
		if(digits[1] || digits[2]) {
			print_two(digits[1], digits[2], result);
		}
		add_thousand(result);
		if(digits[3]) {
			print_one(digits[3], result);
			add_hundred(result);
		}
		print_two(digits[4], digits[5], result);
		break;
	
	case 7:
		print_one(digits[0], result);
		add_million(result);
		print_one(digits[1], result);
		add_hundred(result);
		print_two(digits[2], digits[3], result);
		add_thousand(result);
		print_one(digits[4], result);
		add_hundred(result);
		print_two(digits[5], digits[6], result);
		break;
	
	case 8:
		print_two(digits[0], digits[1], result);
		add_million(result);
		print_one(digits[2], result);
		print_two(digits[3], digits[4], result);
		add_thousand(result);
		print_one(digits[5], result);
		add_hundred(result);
		print_two(digits[6], digits[7], result);
		break;
	
	case 9:
		print_one(digits[0], result);
		add_hundred(result);
		print_two(digits[1], digits[2], result);
		add_million(result);
		print_one(digits[3], result);
		print_two(digits[4], digits[5], result);
		add_thousand(result);
		print_one(digits[6], result);
		add_hundred(result);
		print_two(digits[7], digits[8], result);
		break;

	case 10:
		print_one(digits[0], result);
		add_billion(result);
		print_one(digits[1], result);
		add_hundred(result);
		print_two(digits[2], digits[3], result);
		add_million(result);
		print_one(digits[4], result);
		add_hundred(result);
		print_two(digits[5], digits[6], result);
		add_thousand(result);
		print_one(digits[7], result);
		add_hundred(result);
		print_two(digits[8], digits[9], result);
		break;	
	}
	return result;
}

int
main(int argc, char *argv[])
{
	int	num;
	
	if(argc < 2) {
		printf("Usage: %s <num>\n", argv[0]);
		return -1;
	}
	num = atoi(argv[1]);
	printf("%s\n", numberToWords(num));
	return 0;
}
