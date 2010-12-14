/*
 * Solution to Project Euler Problem #7
 *
 * Scott Busch
 *
 * Modification Log:
 *	Date			Change
 *	2010/12/xx		Initial authoring. 
 *
 */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <math.h>

int isPrime(unsigned long long num) {
	int i = 3;

	if (!(num & 0x1)) 
		return( 0 );

	while( i < num ) {
		if( num % i == 0 ) {
			return( 0 );
		}
		i += 2;
	}
	return( 1 );
}


int problem(int argc, char** argv) {

	int count = 3;
	const int target = 10001;
	unsigned long long number = 5;

	/* FIXME: Double check off-by-one indexing */
	do {
		number += 2;

		if( isPrime( number ) ) {
			++count;
		}

	} while( count < target );

	printf("Number = %lld; count = %d;\n", number, count);

	return( 0 );
}

int main(int argc, char** argv) {

	return( problem(argc, argv) );
}
