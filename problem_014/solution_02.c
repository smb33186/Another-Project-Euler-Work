/*
 * Solution to Project Euler Problem #14
 *
 * Scott Busch
 *
 * Modification Log:
 *	Date			Change
 *	2012/05/01		Initial authoring. 
 *
 */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

#define MAX_START 1000000

int calcSequence(int start)
{
	int cnt = 1;
	int num = start;

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

	int i;
	int seqLen = 0;
	int longest = 0;
	int bestStart = 0;

	for (i = MAX_START; i > 0; --i) {
		seqLen = calcSequence(i);
		if (seqLen >= longest) {
			longest = seqLen;
			bestStart = i;
		}
	}
	
	printf("Longest sequence (%d) under %d starts at %d\n", longest, MAX_START, bestStart);

	return(0);
}

int main(int argc, char** argv) {

	return(problem(argc, argv));
}
