/*
 * Solution to Project Euler Problem #28
 *
 * Scott Busch
 *
 * Modification Log:
 *	Date			Change
 *	2013/09/23		Initial authoring. 
 *
 */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>


int problem28(int argc, char** argv) {

	unsigned long int sum = 1;
	int r = 3;
	int n;
	int pos = 1;
	int step = 2;
	int stop = 1001;

	if (argc == 2) {
		stop = atoi(argv[1]);
		if (stop < 3) {
			printf("Invalid valid parsed: \"%s\" (%d)\n", argv[1], stop);
			return(1);
		}

		if (stop % 2 == 0) {
			printf("Invalid row length (should be odd): %d\n", stop);
			return(1);
		}
	}

	for (; r <= stop; r += 2) {
		/* 4 corners */
		for (n = 0; n < 4; ++n) {
			pos += step;
			sum += pos;
		}

		step += 2;
	}

	printf("Final sum: %lu\n", sum);

	return(0);
}

int main(int argc, char** argv) {

	return(problem28(argc, argv));
}
