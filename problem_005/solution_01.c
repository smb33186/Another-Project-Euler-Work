/*
 * Solution to Project Euler Problem #4
 *
 * Scott Busch
 *
 * Modification Log:
 *	Date			Change
 *	2010/12/03		Initial authoring. 
 *
 */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

int counters[21];
int maxCounts[21];

int factor(unsigned long long num) {
	int i = 2;
	while( i < num ) {
		if( num % i == 0 ) {
			factor(num / i);
			++counters[i];
			return( i );
		}
		++i;
	}
	++counters[num];
	return( i );
}

int main(int argc, char** argv) {

	int i = 1;
	int j = 0;
	int lcm = 1;

	memset(&maxCounts[0], 0, 21 * sizeof(int));

	for( i = 1; i < 21; ++i ) {
		memset(&counters[0], 0, 21 * sizeof(int));

		factor(i);

		for( j = 0; j < 21; ++j ) {
			if( counters[j] > maxCounts[j] ) {
				maxCounts[j] = counters[j];
			}
		}

		/* * /
		printf(" i = %d:\n", i);
		for( j = 0; j < 21; ++j )
			printf("%2d ", j);
		printf("\n");
		for( j = 0; j < 21; ++j )
			printf("%2d ", counters[j]);
		printf("\n");

		for( j = 0; j < 21; ++j )
			printf("%2d ", maxCounts[j]);
		printf("\n\n");
		/ * */
	}

	printf("Max Counts:\n");
	for( j = 0; j < 21; ++j )
		printf("%2d ", j);
	printf("\n");

	for( j = 0; j < 21; ++j )
		printf("%2d ", maxCounts[j]);
	printf("\n\n");

	for( i = 1; i < 21; ++i ) {
		for( j = 0; j < maxCounts[i]; ++j )
			lcm *= i;
	}

	printf("lcm = %d;\n", lcm);

	for( i = 1; i < 21; ++i ) {
		if( lcm % i != 0 )
			printf("Error: %d %% %d = %d;\n", lcm, i, lcm % i);
	}

	return( 0 );
}
