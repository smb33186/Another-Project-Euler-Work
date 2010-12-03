/*
 * Solution to Project Euler Problem #2
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

#define index(i, off)	(((i) + (3 - off)) % (3))
int main(int argc, char** argv) {

	int i = 2;
	int total = 0;
	int dataValues[] = {0, 2, 0};

	/* Problem Solving */

	while( dataValues[index(i, 1)] < 4000000 ) {
		dataValues[index(i,0)] = 4 * dataValues[index(i,1)] + dataValues[index(i,2)];
		total += dataValues[index(i,0)];
		++i;
	}

	total -= dataValues[index(i,1)];

	printf( "Total = %d;\n", total);
	printf( "Last value set = { %d, %d, %d }, i = %d, index = %d;\n",
		dataValues[0], dataValues[1], dataValues[2], i, index(1,0));

	return( 0 );
}
