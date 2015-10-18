/*
 * Solution to Project Euler Problem #37
 *
 * Scott Busch
 *
 * Modification Log:
 *	Date			Change
 *	2015/10/17		Initial authoring. 
 *
 */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

#define BM_SET(b, bm)		((bm)[((b)/8)] |= (0x1 << ((b) % 8)))
#define BM_CLR(b, bm)		((bm)[((b)/8)] &= (~(0x1 << ((b) % 8))))
#define BM_IS_SET(b, bm)	((bm)[((b)/8)] & (0x1 << ((b) % 8)))

unsigned int	bm_max = 0;
unsigned char * bm_primes = NULL;

int
calcPrimes(unsigned int max)
{

	unsigned int i;
	unsigned int j;
	int cnt = 0;
	int size = (max >> 3) + 1;

	bm_primes = (unsigned char *)malloc(size);
	memset(bm_primes, 0, size);

	BM_SET(0, bm_primes);
	BM_SET(1, bm_primes);

	for (i = 2; i <= max; ++i) {
		if (!BM_IS_SET(i, bm_primes)) {
			for (j = 2; (i*j) <= max; ++j) {
				BM_SET((i*j), bm_primes);
			}
		}
	}

	for (i = 2; i <= max; ++i) {
		if (!BM_IS_SET(i, bm_primes)) {
			// printf("Prime: %d\n", i);
			cnt++;
		}
	}

	bm_max = max;

	return(cnt);
}

int
isPrime(unsigned int n)
{
	unsigned int i;

	/* Negative, special, or even number */
	if (n == 2)
		return(1);

	if (n < 2 || n % 2 == 0)
		return(0);

	/* Within the range of the BM of primes */
	if (n < bm_max) {
		return(!BM_IS_SET(n, bm_primes));
	}

	/* Now search using the primes from the BM */
	for (i = 3; i < bm_max; i += 2) {

		if (BM_IS_SET(i, bm_primes))
			continue;

		if (n % i == 0)
			return(0);
	}

	/* Resume where the BM ended */
	for (; i < (n/2) + 1; i += 2) {
		if (n % i == 0) {
			return(0);
		}
	}

	return(1);
}


int
problem37(int argc, char** argv)
{
	int i;
	int r;
	int cnt = 0;
	int sum = 0;
	int tmp;
	int order;
	const unsigned int stop = 1e7;

	calcPrimes(stop);

	for (i = 11; i < stop && cnt < 11; i += 2) {
		order = 1;
		tmp = i;
		while (tmp > 0) {
			r = tmp % 10;
			if (r % 2 == 0 && r != 2)
				break;

			// Check "right-to-left" truncated primes"
			if (!isPrime(tmp))
				break;

			tmp /= 10;
			order *= 10;
		}

		if (tmp)
			continue;

		order /= 10;
		tmp = i;
		while (order > 1) {
			if (!isPrime(tmp %= order))
				break;

			order /= 10;
		}

		if (order != 1)
			continue;

		cnt++;
		sum += i;
		// printf("Found matching prime: %d\n", i);
	}

	printf("Matching count: %d (i = %d)\n", cnt, i);
	printf("Sum of all left- and right-truncated primes: %d\n", sum);

	return(0);
}

int
main(int argc, char** argv)
{
	return(problem37(argc, argv));
}
