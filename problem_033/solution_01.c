/*
 * Solution to Project Euler Problem #33
 *
 * Scott Busch
 *
 * Modification Log:
 *	Date			Change
 *	2015/10/05		Initial authoring. 
 *
 */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

int
reduce(int *n, int *d)
{
	int c = 2;

	while (c <= *n && c <= *d) {
		if (*n % c == 0 && *d % c == 0) {
			*n /= c;
			*d /= c;
			c = 2;
		} else {
			if (c == 2)
				++c;
			else
				c += 2;
		}
	}

	return(0);
}

int
problem30(int argc, char** argv)
{
	int n, d;
	int d1, d2, n1, n2;
	int n_prod = 1;
	int d_prod = 1;

	for (d = 99; d > 10; --d) {
		if (d % 10 == 0)
			continue;

		d1 = d % 10;
		d2 = (d / 10) % 10;

		for (n = d-1; n > 10; --n) {
			if (n % 10 == 0)
				continue;

			n1 = n%10;
			n2 = (n / 10) % 10;

			if (n1 == d1 && (double)n2 / (double)d2 == (double)n / (double)d) {
				printf("Found candidate: %d / %d == %d%d / %d%d == %d / %d == %f\n", n, d, n2, n1, d2, d1, n2, d2, (double)n / (double)d);
				reduce(&n2, &d2);
				printf("  Reduced: %d / %d == %f\n", n2, d2, (double)n2/d2);
				n_prod *= n2;
				d_prod *= d2;
				continue;
			} else if (n1 == d2 && (double)n2 / (double)d1 == (double)n / (double)d) {
				printf("Found candidate: %d / %d == %d%d / %d%d == %d / %d == %f\n", n, d, n2, n1, d2, d1, n2, d1, (double)n / (double)d);
				reduce(&n2, &d1);
				printf("  Reduced: %d / %d == %f\n", n2, d1, (double)n2/d1);
				n_prod *= n2;
				d_prod *= d1;
				continue;
			}

			if (n2 == d1 && (double)n1 / (double)d2 == (double)n / (double)d) {
				printf("Found candidate: %d / %d == %d%d / %d%d == %d / %d == %f\n", n, d, n2, n1, d2, d1, n1, d2, (double)n / (double)d);
				reduce(&n1, &d2);
				printf("  Reduced: %d / %d == %f\n", n1, d2, (double)n1/d2);
				n_prod *= n1;
				d_prod *= d2;
				continue;
			} else if (n2 == d2 && (double)n1 / (double)d1 == (double)n / (double)d) {
				printf("Found candidate: %d / %d == %d%d / %d%d == %d / %d == %f\n", n, d, n2, n1, d2, d1, n1, d1, (double)n / (double)d);
				reduce(&n1, &d1);
				printf("  Reduced: %d / %d == %f\n", n1, d1, (double)n1/d1);
				n_prod *= n1;
				d_prod *= d1;
				continue;
			}
		}
	}

	reduce(&n_prod, &d_prod);
	printf("Denominator product: %d\n", d_prod);

	return(0);
}

int
main(int argc, char** argv)
{
	return(problem30(argc, argv));
}
