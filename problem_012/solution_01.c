/*
 * Solution to Project Euler Problem #12
 *
 * Scott Busch
 *
 * Modification Log:
 *	Date			Change
 *	2011/01/01		Initial authoring. 
 *
 */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <math.h>

int factorCount(int sum) {

	int count = 2;
	int max = sqrt(sum);
	int i = 0;

	if( max == 1 ) {
		return( count );
	}

	for( i = 2; i <= max; i++ ) {
		if( sum % i == 0 ) {
			count += 2;
		}
	}

	if( sqrt(sum) - (int)sqrt(sum) <= 0.0 ) {
		/* The number has an even square root but was counted
		 * as two factors.
		 */
		count--;
	}

	return( count );
}

int factorPrint(int sum) {

	int i = 0;

	printf("Factors for %d:", sum);
	for( i = 1; i <= sum; i++ ) {
		if( sum % i == 0 ) {
			printf(" %d", i );
		}
	}
	
	printf("\n");

	return( 0 );
}
int problem(int argc, char** argv) {

	int triangleNum = 1;
	int num = 1;
	int count = 0;

	while( 1 ) {
		num++;
		triangleNum += num;
		count = factorCount(triangleNum);
		// printf("num = %6d; Tn = %8d; count = %4d;\n", num, triangleNum, count);
		if( count >= 500 ) {
			break;
		}
	}

	printf("num = %d; triangleNum = %d; count = %d;\n", num, triangleNum, count);
	factorPrint(triangleNum);

	return( 0 );
}

int main(int argc, char** argv) {

	return( problem(argc, argv) );
}
