/*
 * Solution to Project Euler Problem #30
 *
 * SB
 *
 * Modification Log:
 *	Date			Change
 *	2015/10/01		Initial authoring. 
 *
 */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <math.h>

#if 0
const unsigned int pow_4th[10] = {
	0,		// 0
	1,		// 1
	16,		// 2
	81,		// 3
	256,	// 4
	625,	// 5
	1296,	// 6
	2401,	// 7
	4096,	// 8
	6561	// 9
};
#define		powers			pow_4th
#define		powers_depth	4
#else
const unsigned int pow_5th[10] = {
	0,		// 0
	1,		// 1
	32,		// 2
	243,	// 3
	1024,	// 4
	3125,	// 5
	7776,	// 6
	16807,	// 7
	32768,	// 8
	59049	// 9
};
#define		powers			pow_5th
#define		powers_depth	5
#endif


int digits[10];	// Longer than necessary

void
print_result(int level, int sum, int *digits)
{
	int j;
	for (j = 0; j <= level; ++j) {
		printf("%d", digits[j]);
	}
	printf(" = ");
	for (j = 0; j <= level; ++j) {
		printf("%d", powers[digits[j]]);
		if (j != level)
			printf(" + ");
	}
	printf("\n");
}

int
check_digits(int level, int sum, int *digits)
{
	int i;
	int tmp = sum;

	for (i = level; i >= 0; --i) {
		if (digits[i] != tmp % 10)
			return(0);

		tmp /= 10;
	}

	return(1);
}


int
gen_combinations(int level, int max_depth, int sum, int *digits, int *results_sum)
{
	int i;
	int k;
	int cnt = 0;
	int tmp = sum;
	int min = (int)pow(10.0, (double)level);
	int max = (int)pow(10.0, (double)(level + 1));

	if (level >= max_depth) {
		return(0);
	} else {

		// for (k = 0; k < level; ++k) printf("\t");
		// printf("[%d] min: %d, max: %d, sum: %d\n", level, min, max, sum);
		i = (level ? 0 : 1);
		for (; i < 10; ++i) {
			tmp = sum + powers[i];

			// for (k = 0; k < level; ++k) printf("\t");
			// printf("[%d] i:%d tmp:%d\n", level, i, tmp);

			digits[level] = i;

			if (tmp > min && tmp < max) {
				if (tmp % 10 == i) {
					if (check_digits(level, tmp, digits)) {
						printf("Found solution[%d:%d]: %d = ", level, cnt, tmp);
						print_result(level, tmp, digits);
						cnt++;
						*results_sum += tmp;
					}
				}
			}

			cnt += gen_combinations(level + 1, max_depth, tmp, digits, results_sum);
		}
	}
	
	return(cnt);
}

int
problem30(int argc, char** argv)
{
	int cnt = 0;
	int results_sum = 0;
	int digits[10] = { 0 };

	printf("Hello World\n");

	cnt = gen_combinations(0, powers_depth, 0, &digits[0], &results_sum);
	printf("Count: %d\n", cnt);
	printf("Sum of matches: %d\n", results_sum);

	printf("Goodbye World\n");

	return(0);
}

int
main(int argc, char** argv)
{

	return(problem30(argc, argv));
}
