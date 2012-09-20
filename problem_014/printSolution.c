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

int main(int argc, char** argv) {

	if (argc != 2) {
		printf("Usage: %s <num>\n", argv[0]);
		return (1);
	}

	printSequence(atoi(argv[1]));
	return(0);
}
