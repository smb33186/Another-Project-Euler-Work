/*
 * Solution to Project Euler Problem #6
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


int main(int argc, char** argv) {

	int end = 100;
	int triangleNumber = end * (end + 1) / 2;
	int i = 0;
	unsigned long long difference = 0;

	printf("Tn = %d;\n", triangleNumber);

	for( i = 0; i <= end; ++i ) {
		difference += i * triangleNumber;
		--triangleNumber;
	}

	printf( "Difference = %lld\n", difference );

	return( 0 );
}
