/*
 * Solution to Project Euler Problem #14
 *
 * Scott Busch
 *
 * Modification Log:
 *	Date			Change
 *	2012/09/20		Initial authoring. 
 *
 */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

#define MAX_START 1000000

unsigned long calcSequence(unsigned long start)
{
	unsigned long cnt = 1;
	unsigned long num = start;

	while (num > 1) {
		if (num % 2 == 0) {
			// Even number
			num /= 2;		// Divid by 2
		} else {
			// Odd number
			num = num * 3 + 1;
		}

		cnt++;
	}

	return(cnt);
}

int problem(int argc, char** argv) {

	unsigned long i;
	unsigned long seqLen = 0;
	unsigned long longest = 0;
	unsigned long bestStart = 0;

	for (i = MAX_START; i > 0; --i) {
		seqLen = calcSequence(i);
		if (seqLen >= longest) {
			longest = seqLen;
			bestStart = i;
		}
	}
	
	printf("Longest sequence (%lu) under %d starts at %lu\n", longest, MAX_START, bestStart);

	return(0);
}

int main(int argc, char** argv) {

	return(problem(argc, argv));
}
