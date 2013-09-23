/*
 * Solution to Project Euler Problem #27
 *
 * Scott Busch
 *
 * Modification Log:
 *	Date			Change
 *	2013/09/23		Initial authoring. 
 *
 */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

#define	MAX_NUM		(1000)
#define BM_SET(b, bm)		((bm)[((b)/8)] |= (0x1 << ((b) % 8)))
#define BM_CLR(b, bm)		((bm)[((b)/8)] &= (~(0x1 << ((b) % 8))))
#define BM_IS_SET(b, bm)	((bm)[((b)/8)] & (0x1 << ((b) % 8)))

unsigned int	bm_max = 0;
unsigned char * bm_primes = NULL;

int calc_primes(int max) {

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

int isPrime(int n) {

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

int problem27(int argc, char** argv) {

	int a;
	int b;
	int n;
	int cnt;
	int max_num = MAX_NUM;
	int max_prime_cnt_n = 0;
	int max_prime_cnt_a = 0;
	int max_prime_cnt_b = 0;
	
	if (argc == 2) {
		max_num = atoi(argv[1]);
		if (max_num < 2) {
			printf("Invalid Max: \"%s\" (%d)\n", argv[1], max_num);
			return(1);
		}

		printf("Setting max number: %d\n", max_num);
	}

	cnt = calc_primes(max_num);
	printf("%d primes under %d\n", cnt, max_num);

	/* Prime numbers are now determined (any 0 bits in the bitmap) */

	for (b = 2; b < max_num; ++b) {

		/* Non primes are set to 1 in the BM */
		/* When n = 0 => b must be a prime alreayd */
		if (BM_IS_SET(b, bm_primes)) {
			continue;
		}

		/* If a < -b, then when n = 1, the result would be negative => no prime */
		/* a +=2 because when n = 1, (1 + a + b) needs to be an odd number */
		for (a = -b; a < max_num; a +=2) {

			for (n = 1; n < 100; ++n) {
				if (!isPrime(((n*n) + a*n + b))) {
					break;
				}
			}

			if (n >= 100) {
				printf("ERROR: n = %d, (a = %d, b = %d): I don't think it should "
					"ever get this high\n", n, a, b);
			}

			if (n > max_prime_cnt_n) {
				max_prime_cnt_n = n;
				max_prime_cnt_a = a;
				max_prime_cnt_b = b;
			}
		}
	}

	printf("Largest n = %d when a = %d, b = %d\n",
		max_prime_cnt_n, max_prime_cnt_a, max_prime_cnt_b);
	printf("Product of coefficients: %d\n", max_prime_cnt_a * max_prime_cnt_b);

	if (bm_primes) {
		free(bm_primes);
		bm_primes = NULL;
	}

	return(0);
}

int main(int argc, char** argv) {

	return(problem27(argc, argv));
}
