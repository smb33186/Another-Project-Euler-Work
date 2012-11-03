/*
 * Solution to Project Euler Problem #15
 *
 * Scott Busch
 *
 * Modification Log:
 *	Date			Change
 *	2012/xx/xx		Initial authoring. 
 *
 */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

unsigned long _recurse(int x, int y, int N)
{
	unsigned long cnt = 0;

	if (x == N-1 && y == N-1) {
		// At bottom edge corner
		cnt = 1;
	} else if (x == N-1) {
		// Along right edge
		cnt += _recurse(x, y+1, N);
	} else if (y == N-1) {
		// At bottom edge
		cnt += _recurse(x+1, y, N);
	} else {
		// In the middle or start
		cnt += _recurse(x+1, y, N);
		cnt += _recurse(x, y+1, N);
	}

	return(cnt);
}

unsigned long _tablePropagation(int N)
{
	int i;
	int k;
	unsigned long result = 0;
	unsigned long** table = NULL;
	
	table = calloc(N, sizeof(unsigned long *));
	for (i = 0; i < N; ++i) {
		table[i] = calloc(N, sizeof(unsigned long));
	}

	// Init boundary cases
	for (i = 0; i < N; ++i) {
		table[0][i] = 1;
		table[i][0] = 1;
	}

	for (i = 1; i < N; ++i) {
		// Traverse the diagonal
		for (k = i; k < N; ++k) {
			table[i][k] = table[i-1][k] + table[i][k-1];
			table[k][i] = table[i][k];
		}
	}

	result = table[N-1][N-1];

	for (i = 0; i < N; ++i) {
		free(table[i]);
		table[i] = NULL;
	}
	free(table);
	table = NULL;

	return(result);
}

int problem15(int argc, char** argv)
{
	int N = 0;
	unsigned long pathCnt = 0;

	if (argc != 2) {
		printf("Error: Incorrect parameter count (%d)\n", argc);
		printf("Usage:\n");
		printf("  %s <N = square size>\n", argv[0]);
		return(1);
	}

	N = atoi(argv[1]);
	if (N < 2) {
		printf("Error: Invalid size value %d (%s)\n", N, argv[1]);
		printf("Size must be 2 or larger (N >= 2)\n");
		return(1);
	}

	// pathCnt = _recurse(0, 0, N);
	pathCnt = _tablePropagation(N);
	printf("Path count for a %dx%d grid: %lu\n", N, N, pathCnt);

	return(0);
}

int main(int argc, char** argv)
{

	return(problem15(argc, argv));
}
