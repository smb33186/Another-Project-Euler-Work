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

const int factorials[] = {
	1,
	1,
	2,
	6,
	24,
	120,
	720,
	5040,
	40320,
	362880
};

int
problem34(int argc, char** argv)
{
	int i;
	int tmp;
	int sum;
	int solution_sum = 0;

	for (i = 10; i < 1e8; ++i) {
		tmp = i;
		sum = 0;
		while(tmp > 0) {
			sum += factorials[tmp % 10];
			tmp /= 10;
		}
		if (sum == i) {
			solution_sum += i;
			printf("Found match: %d ==", i);
			tmp = i;
			while (tmp > 0) {
				printf(" %d! +", tmp % 10);
				tmp /= 10;
			}
			tmp = i;
			printf(" ==");
			while (tmp > 0) {
				printf(" %d +", factorials[tmp % 10]);
				tmp /= 10;
			}
			printf(" == %d\n", sum);
		}
	}
	
	printf("Sum of matches: %d\n", solution_sum);

	return(0);
}

int
main(int argc, char** argv)
{
	return(problem34(argc, argv));
}
