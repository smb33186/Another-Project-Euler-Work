/*
 * Solution to Project Euler Problem #39
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

#define setDigit(d, c)	((c) |= (0x1 << d))
#define isDigit(d, c)	((c) & (0x1 << d))

int
problem38(int argc, char** argv)
{
	int n;
	int i;
	int j;
	int tmp;
	int sum = 0;
	int largest = 0;
	int digits = 0;

	for (i = 1; i < 10000; ++i) {
		// printf("%d\n", i);
		digits = 0;
		sum = 0;
		for (n = 1; n < 10; ++n) {
			// printf("   %d\n", n);
			tmp = i * n;
			while (tmp > 0) {
				if (isDigit(tmp % 10, digits))
					break;
				setDigit(tmp % 10, digits);
				tmp /= 10;
			}

			if (tmp)
				break;

			// printf("i:%d, n:%d, d:0x%x\n", i, n, digits);
			if (digits == 0x3fe) {
				// All digits used
				for (j = 1; j <= n; ++j) {
					tmp = i * j;
					// printf("i:%d, j:%d: %d\n", i, j, i*j);
					while (tmp > 0) {
						sum *= 10;
						tmp /= 10;
					}
					sum += (i * j);
				}

				if (sum > largest) {
					// printf("Old largest: %d, new largest: %d\n", largest, sum);
					// printf("  i:%d, n:%d\n", i, n);
					largest = sum;
				}

				break;
			}
		}
	}

	printf("Largest: %d\n", largest);

	return(0);
}

int
main(int argc, char** argv)
{
	return(problem38(argc, argv));
}
