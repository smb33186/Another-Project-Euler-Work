/*
 * Solution to Project Euler Problem #xx
 *
 * Scott Busch
 *
 * Modification Log:
 *	Date			Change
 *	2013/02/10		Initial authoring. 
 *
 */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

#define MAX		10000

int problem021(int argc, char** argv) {

	int i;
	int j;
	int a_nums[MAX+1];
	int pair_sum = 0;

	for (i = MAX; i >= 0; --i) {
		a_nums[i] = 1;
	}

	for (i = 2; i <= MAX / 2; ++i) {
		/* Add in the new divisor */
		for (j = (i*2); j <= MAX; j += i) {
			a_nums[j] += i;
		}

		if (a_nums[i] < i) {
			if (a_nums[a_nums[i]] == i) {
				/* Found amicable pair */
				printf("Amicable pair found: %d (%d) & %d (%d)\n", i, a_nums[i], a_nums[i], a_nums[a_nums[i]]);
				pair_sum += a_nums[a_nums[i]] + i;
			}
		}
	}

	printf("Sum of all amicable numbers under %d: %d\n", MAX, pair_sum);

	return(0);
}

int main(int argc, char** argv) {

	return(problem021(argc, argv));
}
