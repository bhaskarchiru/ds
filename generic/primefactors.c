#include <stdio.h>
#include <math.h>
#include <stdlib.h>

#define ALLOC_SZ	8

/*
 * Return 'unique' prime factors of a given number.
 */

int *
primefactors(int n, int *primeszp)
{
	int	i, primesz, *primes, curidx = 0;

	primesz = ALLOC_SZ;
	primes = malloc(sizeof(int) * primesz);
	primes[curidx++] = 1;
	while((n % 2) == 0) {
		if(curidx == 1) {
			primes[curidx++] = 2;
		}
		n /= 2;
	}
	for(i = 3; i <= sqrt(n); i += 2) {
		while((n % i) == 0) {
			if(curidx + 1 == primesz) {
				primesz <<= 1;
				primes = realloc(primes, sizeof(int) * primesz);
			}
			if(primes[curidx - 1] != i) {
				primes[curidx++] = i;
			}
			n /= i;
		}
	}
	if(n > 2)  {
		primes[curidx++] = n;
	}
	*primeszp = curidx;
	return primes;
}

int
main(int argc, char *argv[])
{
	int	*primes, primesz;//, n = atoi(argv[1]);

	for(int i = 1; i <= 1000; i++) {
	primes = primefactors(i, &primesz);
	printf("Unique Prime factors of %d are:\n", i);
	for(int i = 0; i < primesz; i++) {
		printf(" %d ", primes[i]);
	}
	free(primes);
	printf("\n");
	}
	return 0;
}
