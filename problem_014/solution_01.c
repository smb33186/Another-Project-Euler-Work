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

// #define MAX_START 1000000
// #define MAX_NUMBER  (3 * MAX_START + 1)
#define MAX_START 33
#define MAX_NUMBER  (MAX_START * MAX_START * MAX_START)

int numbers[MAX_NUMBER + 1];

int printSequence(int num) {
	int cnt = 0;
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


#if 0
int populateNumbers() {

	int i, j;
	int count = 0;

	for (i = 2; i <= 100; i++) {
		if (numbers[i] == 0) {
			if (i % 2 == 0) {

			count = numbers[i/2];
			for (j = i; j <= 100; j *= 2, count++) {
				numbers[j] = count;
			}
		} else {
			count = numbers[i-1];
			for (j = i * 2; j <= 100; j *= 2, count++) {
				numbers[j] = count;
			}
		}
	}

	return (0);
}
#endif

int populateSequence(int num) {

	int i;
	int count = 1;
	int count2;

	if (numbers[num] != 0) {
		return (numbers[num]);
	}

	if (num % 2 == 0) {
		count = populateSequence(num / 2) + 1;
	} else {
		count = populateSequence(num * 3 + 1) + 1;
	}

	numbers[num] = count;
	count2 = count + 1;
	for (i = 2 * num; i < MAX_NUMBER; i *= 2, count2++) {
		numbers[i] = count2;
	}

	return (count);
}

void printNumbers(int withSeq) {

	int i;

	for (i = 0; i <= MAX_NUMBER; ++i) {
		printf("%d => %d", i, numbers[i]);
		if (withSeq) {
			printf(":\n");
			printSequence(i);
			printf("==============\n");
		} else {
			printf("\n");
		}
	}
}


int populateNumbers() {

	int i;

	for (i = 2; i <= MAX_START; ++i) {
		populateSequence(i);
	}

	printNumbers(0);

	return (0);
}

int problem(int argc, char** argv) {

	// int i = 2;

	memset(&numbers[0], 0, sizeof (numbers));

	numbers[0] = 0;
	numbers[1] = 1; // Number 1 (Special/seed case)

	populateNumbers();

	return( 0 );
}

int main(int argc, char** argv) {

	return( problem(argc, argv) );
}
