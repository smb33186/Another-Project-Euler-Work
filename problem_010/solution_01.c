/*
 * Solution to Project Euler Problem #9
 *
 * Scott Busch
 *
 * Modification Log:
 *	Date			Change
 *	2010/12/23		Initial authoring. 
 *
 */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <math.h>

int isPrime(unsigned int num) {

	if( num == 1 )
		return( 0 );
	else if( num < 4 )
		return( 1 );
	else if( num % 2 == 0 )
		return( 0 );
	else if( num < 9 )
		return( 1 );
	else if( num % 3 == 0 )
		return( 0 );
	else {
		int r = (int) sqrt(num);
		int f = 5;
		while( f <= r ) {
			if( num % f == 0 )
				return( 0 );

			if( num % (f+2) == 0 )
				return( 0 );

			f += 6;
		}
	}

	return( 1 );
}

int problem(int argc, char** argv) {

	unsigned long long sum = 2;
	unsigned int num = 3;

	do {
		if( isPrime(num) ) {
			sum += num;
		}
		num += 2;
	} while( num < 2e6 );

	printf("num = %d\n", num);
	printf("sum = %lld\n", sum);

	return( 0 );
}

int main(int argc, char** argv) {

	return( problem(argc, argv) );
}
