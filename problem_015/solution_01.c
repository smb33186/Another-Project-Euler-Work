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

int _recurse(int x, int y, int N)
{
	int cnt = 0;

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

int problem15(int argc, char** argv)
{
	int N = 0;
	int pathCnt = 0;

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

	pathCnt = _recurse(0, 0, N);
	printf("Path count for a %dx%d grid: %d\n", N, N, pathCnt);

	return(0);
}

int main(int argc, char** argv)
{

	return(problem15(argc, argv));
}
