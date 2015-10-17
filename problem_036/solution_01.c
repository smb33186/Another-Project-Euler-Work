/*
 * Solution to Project Euler Problem #36
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


int
problem36(int argc, char** argv)
{
	int i;
	int p;
	int cnt = 0;
	unsigned long sum = 0;
	const int stop = 1e6;
	int tmp;

	for (i = 1; i < stop; ++i) {
		p = 0;
		tmp = i;
		while (tmp > 0) {
			p = (p * 10) + (tmp % 10);
			tmp /= 10;
		}

		if (p != i)
			continue;

		p = 0;
		tmp = i;
		while (tmp > 0) {
			p = (p << 1) | (tmp & 0x1);
			tmp >>= 1;
		}

		if (p != i)
			continue;

		// printf("Palindrome found: %d, ", i);
		cnt++;
		sum += i;
		/*
		tmp = i;
		while (tmp > 0) {
			printf("%s", (tmp & 0x1 ? "1" : "0"));
			tmp >>= 1;
		}
		printf("\n");
		*/
	}

	printf("%d palindromes found under %d with a sum of %lu\n", cnt, stop, sum);

	return(0);
}

int
main(int argc, char** argv)
{
	return(problem36(argc, argv));
}
