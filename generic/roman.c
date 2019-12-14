/*
 * Convert Roman numeral to decimal.
 */

#include <stdio.h>

int
romanToInt(char *s)
{
	int	result = 0;
	int	sawI = 0, sawX = 0, sawC = 0;
	char	c;

	if(s == NULL || *s == '\0') {
		return 0;
	}
	while((c = *s++) != '\0') {
		switch(c) {
		case 'I':
			result += 1;
			sawI = 1;
			break;

		case 'V':
			if(sawI) {
				result += 3;
				sawI = 0;
			} else {
				result += 5;
			}
			break;

		case 'X':
			if(sawI) {
				result += 8;
				sawI = 0;
			} else {
				result += 10;
			}
			sawX = 1;
			break;

		case 'L':
			if(sawX) {
				result += 30;
				sawX = 0;
			} else {
				result += 50;
			}
			break;

		case 'C':
			if(sawX) {
				result += 80;
				sawI = 0;
			} else {
				result += 100;
			}
			sawC = 1;
			break;
		
		case 'D':
			if(sawC) {
				result += 300;
				sawC = 0;
			} else {
				result += 500;
			}
			break;
		
		case 'M':
			if(sawC) {
				result += 800;
				sawC = 0;
			} else {
				result += 1000;
			}
			break;
		}
	}
	return result;
}

int
main(int argc, char *argv[])
{

	printf("Value of roman numeral %s is %d\n",  "MCMXCIV", romanToInt("MCMXCIV"));
	return 0;
}

