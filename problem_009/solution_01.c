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

int conditionTest(int a, int b, int c) {
	return( (a < c) && (b < c) &&
			(1000 == a + b + c) &&
			((a*a + b*b) == (c*c)) );
}

int problem(int argc, char** argv) {

	int a, b, c;
	double b_calc;

	for( a = 1; a < 500; ++a ) {
		b_calc = ((double)(5e5 - 1000*a)) / ((double)(1000 - a));
		b = (int) b_calc;
		if( b == b_calc ) {
			c = 1000 - a - b;
			if( conditionTest(a, b, c) ) {
				printf("a = %d, b = %d, c = %d\n", a, b, c);
				printf("a+b+c = %d\n", (a + b + c));
				printf("a*b*c = %d\n", (a * b * c));
				break;
			}
		}
	}

	return( 0 );
}

int main(int argc, char** argv) {

	return( problem(argc, argv) );
}
