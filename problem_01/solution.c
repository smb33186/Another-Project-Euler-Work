/*
 * Solution to Project Euler Problem #1
 *
 * Scott Busch
 *
 * Modification Log:
 *	Date			Change
 *	2010/12/02		Initial authoring. 
 *
 */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main(int argc, char** argv) {

	int m = 10;
	int n = 0;
	int total = 0;
	int count = 0;
	int multiples[] = {3, 5};
	int i = 0;

	/* Problem Solving */

	count = sizeof( multiples ) / sizeof( int );

	for( i = 0; i < count; ++i ) {
		n = (int) ((m - 1) / multiples[i]);

		total += multiples[i] * (n * (n+1) / 2);
	}

	printf("The total sum for the multiples of {");
	for( i = 0; i < count; ++i ) {
		printf("%d%s", multiples[i], (i == (count-1) ? "" : ", "));
	}
	printf("} in %d is equal to %d.\n", m, total);

	return( 0 );
}
