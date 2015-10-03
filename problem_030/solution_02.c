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
#define		powers_depth	6
#endif


int
check_digits(int num)
{
	int tmp = num;
	int sum = 0;

	while (tmp > 0) {
		sum += powers[tmp % 10];
		tmp /= 10;
	}

	if (sum == num)
		return(1);
	
	return(0);
}


int
gen_combinations(int level, int max_depth, int sum, int *digits, int *results_sum)
{
	int i;
	// int k;
	int cnt = 0;

	for (i = 2; i < 999999; ++i) {
		if (check_digits(i)) {
			printf("Found result: %d\n", i);
			cnt++;
			*results_sum += i;
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
