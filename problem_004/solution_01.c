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

int testPalindrome(int number) {

	int i = 0;
	int len = 0;
	char string[12] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
	len = sprintf(&string[0], "%d", number);

	for( i = 0; i < (int)(len/2); ++i ){
		if( string[i] != string[len-i-1] ) {
			return( 0 );
		}
	}

	return( 1 );
}

int main(int argc, char** argv) {

	int cursor1 = 999;
	int cursor2 = 999;
	int largest = 0;
	int terms[2] = {0, 0};

	while( cursor1 > terms[1] ) {

		cursor2 = cursor1;
		while( cursor2 > terms[1] ) {
			if( cursor1 * cursor2 > largest ) {
				if( testPalindrome( cursor1 * cursor2 ) ) {
					largest = cursor1 * cursor2;
					terms[0] = cursor1;
					terms[1] = cursor2;
				}
			}
			--cursor2;
		}
		--cursor1;
	}

	printf("Largest palindrome = %d => {%d, %d}\n", largest, terms[0], terms[1]);

	return( 0 );
}
