/*
 * Solution to Project Euler Problem #xx
 *
 * Scott Busch
 *
 * Modification Log:
 *	Date			Change
 *	2011/xx/xx		Initial authoring. 
 *
 */

/*
 * Some references found during research for this problem.
 *
 * http://eli.thegreenplace.net/2009/02/25/project-euler-problem-26/
 * http://pastebin.com/f1efaf62d  (From a comment in the above blog post)
 *
 */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <stdint.h>

#define	MAX_NUM		(1000)
#define BM_SET(b, bm)		((bm)[((b)/8)] |= (0x1 << ((b) % 8)))
#define BM_CLR(b, bm)		((bm)[((b)/8)] &= (~(0x1 << ((b) % 8))))
#define BM_IS_SET(b, bm)	((bm)[((b)/8)] & (0x1 << ((b) % 8)))

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
			printf("Prime: %d\n", i);
			cnt++;
		}
	}

	return(cnt);
}

int problem26(int argc, char** argv) {

	int i;
	int x;
	int max_num = MAX_NUM;
	int cnt;
	int len = 0;
	int max_len = 0;
	int max_len_prime = 0;

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

	for (i = 2; i <= max_num; ++i) {

		/* Skip non prime numbers */
		if (BM_IS_SET(i, bm_primes)) 
			continue;

		x = 1;
		len = 0;

		while (x != 0) {

			while (x <= i) {
				x *= 10;
				len++;
			}

			x %= i;

			if (x == 1)
				break;

			if (len > (2 * i)) {
				printf("Error on prime %d: len = %d\n", i, len);
				return (1);
			}
		}

		if (len > max_len) {
			max_len = len;
			max_len_prime = i;
		}
	}

	printf("Longest decimal pattern: %d from prime %d\n", max_len, max_len_prime);

	return(0);
}

int main(int argc, char** argv) {

	return(problem26(argc, argv));
}
