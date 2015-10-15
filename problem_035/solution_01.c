/*
 * Solution to Project Euler Problem #35
 *
 * Scott Busch
 *
 * Modification Log:
 *	Date			Change
 *	2015/10/11		Initial authoring. 
 *
 */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <math.h>

#define BM_SET(b, bm)		((bm)[((b)/8)] |= (0x1 << ((b) % 8)))
#define BM_CLR(b, bm)		((bm)[((b)/8)] &= (~(0x1 << ((b) % 8))))
#define BM_IS_SET(b, bm)	((bm)[((b)/8)] & (0x1 << ((b) % 8)))

unsigned int	bm_max = 0;
unsigned char * bm_primes = NULL;

int
calc_primes(int max)
{

	int i;
	int j;
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
isPrime(int n)
{
	int i;

	/* Negative, special, or even number */
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
test_rotations(int num, int order)
{
	int i;
	int d;
	int largest = (int)pow(10.0, order-1);

	for (i = 0; i < order; ++i) {
		d = num % 10;
		num /= 10;
		num += (largest * d);

		if (!isPrime(num)) {
			return(0);
		}
	}

	return(1);
}


int
problem35(int argc, char** argv)
{
	int i;
	int cnt1 = 1;		// Counts for 2
	int tmp;
	int order;
	const int end = 1e6;	// 1e7;

	calc_primes(end);

	for (i = 3; i < end; i += 2){
		if (!isPrime(i))
			continue;
		
		tmp = i;
		order = 0;
		while (tmp > 0) {
			if (tmp % 10 % 2 == 0)
				break;
			tmp /= 10;
			++order;
		}

		if (tmp > 0)
			continue;

		if (test_rotations(i, order)) {
			// printf("Rotations are all primes: %d\n", i);
			cnt1++;
		}
	}

	printf("Circular Primes under %d: %d\n", end, cnt1);

	return(0);
}

int
main(int argc, char** argv)
{
	return(problem35(argc, argv));
}
