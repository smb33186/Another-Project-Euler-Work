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

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <stdint.h>

#define MAX		28123

#define bm_set(i, arr)	(((arr)[(i) / 32]) |= (0x1 << ((i) % 32)))

int problem(int argc, char** argv) {

	int i;
	int j;
	int a_nums[MAX+1];
	uint32_t abundant_sums[MAX+1];
	uint32_t bm_abundant_sums[(MAX - 1) / 32 + 1];
	int non_abundant_sum = 0;

	memset(&bm_abundant_sums[0], 0, sizeof(bm_abundant_sums));
	memset(&abundant_sums[0], 0, sizeof(abundant_sums));

	for (i = MAX; i >= 0; --i) {
		a_nums[i] = 1;
	}

	/* Generate all the factor sums: d(i) = n */
	for (i = 2; i <= MAX / 2; ++i) {
		for (j = (i*2); j <= MAX; j += i) {
			a_nums[j] += i;
		}
	}

	for (i = 4; i <= MAX; ++i) {
		if (a_nums[i] <= i)
			continue;

		for (j = i; j <= MAX; ++j) {
			if (a_nums[j] <= j)
				continue;

			if (i + j > MAX)
				break;

			// printf("Abundant pair: %d (%d) + %d (%d) = %d\n", i, a_nums[i], j, a_nums[j], (i + j));
			bm_set(i + j, bm_abundant_sums);
			abundant_sums[i+j] = 1;
		}
	}

	int count = 0;
	for (i = 1; i < MAX; ++i) {
		if (abundant_sums[i] != 1) {
			non_abundant_sum += i;
			count++;
		}
	}

	printf("Found = %d\n", count);
	printf("Sum of all non-abundant sumable numbers under %d: %d\n", MAX, non_abundant_sum);

	return( 0 );
}

int main(int argc, char** argv) {

	return( problem(argc, argv) );
}
