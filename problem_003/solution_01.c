/*
 * Solution to Project Euler Problem #3
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

int factor(unsigned long long num) {
	int i = 2;
	while( i < num ) {
		if( num % i == 0 ) {
			printf("%d ", i);
			// These help to verify prime of the factors:
			// printf("(");
			// factor(i);
			// printf(") ");
			factor(num / i);
			return( i );
		}
		++i;
	}
	printf("%d", i);
	return( i );
}

int main(int argc, char** argv) {

	// int target = 13195;
	unsigned long long target = 600851475143ULL;

	printf("Factoring %llu:\n", target);
	factor( target );
	printf("\n");

	return( 0 );
}
