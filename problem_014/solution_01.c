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
// #define MAX_START	100
#define MAX_SAVED	(MAX_START * 3 + 1)

unsigned int numbers[MAX_SAVED + 1];

void printSavedTable()
{
	unsigned int i;
	printf("Saved numbers table:\n");
	for (i = 0; i <= MAX_SAVED; ++i) {
		if (i != 0 && i % 8 == 0)
			printf("\n");

		printf("[%4d] = %5d  ", i, numbers[i]);

	}

	if (i != 0 && i % 8 != 0)
		printf("\n");
}

unsigned int printSequence(unsigned int num) {
	unsigned int cnt = 0;
	while (num > 1) {
		cnt++;
		printf("%5d -> ", num);
		if (num % 2 == 1)
			num = num * 3 + 1;
		else
			num = num / 2;

		if (cnt % 10 == 0)
			printf("\n");
	}

	if (cnt % 10 != 0)
		printf("  1\n");

	printf("Count = %d\n", ++cnt);

	return (cnt);
}

unsigned int calcSequence(unsigned int start)
{
	unsigned int cnt = 1;
	unsigned int num = start;

	while (num > 1) {
		if (num <= MAX_SAVED && numbers[num] != 0) {
			// At a known point
			return (cnt + numbers[num] - 1);
		}

		if (num % 2 == 0) {
			// Even number
			num >>= 1;		// Divid by 2
		} else {
			// Odd number
			num = num * 3 + 1;
		}

		cnt++;
	}

	return(cnt);
}

unsigned int populateMultiples(unsigned int base, unsigned int cnt)
{
	unsigned int i;
	for (i = base; i <= MAX_SAVED; i <<= 1) {
		numbers[i] = cnt++;
	}

	return(0);
}

unsigned int populateSaved()
{
	unsigned int i;
	unsigned int seqLen = 0;

	for (i = 1; i <= MAX_START; i += 2) {
		if (numbers[i] == 0) {
			seqLen = calcSequence(i);
			populateMultiples(i, seqLen);
		}
	}

	return(0);
}

unsigned int findBest(unsigned int* start)
{
	unsigned int i;
	// unsigned int seqLen = 0;
	unsigned int longest = 0;
	unsigned int best = 0;

	for (i = MAX_START; i > 0; --i) {
		if (numbers[i] == 0) {
			printf("Problem...? i = %d has no count\n", i);
		} else {
			if (numbers[i] > longest) {
				longest = numbers[i];
				best = i;
			}
		}
	}

	if (start)
		*start = best;
	
	return (longest);
}

int problem(int argc, char** argv) {

	unsigned int longest = 0;
	unsigned int bestStart = 0;

	memset(&numbers[0], 0, sizeof (numbers));

	populateSaved();
	// printSavedTable();
	longest = findBest(&bestStart);

	printf("Longest sequence (%d) under %d starts at %d\n", longest, MAX_START, bestStart);

	return( 0 );
}

int main(int argc, char** argv) {

	return( problem(argc, argv) );
}
