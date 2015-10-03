/*
 * Solution to Project Euler Problem #31
 *
 * Scott Busch
 *
 * Modification Log:
 *	Date			Change
 *	2015/10/02		Initial authoring. 
 *
 */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

#define NUM_PENCE	8
const int pence[NUM_PENCE] = {
	200,
	100,
	50,
	20,
	10,
	5,
	2,
	1
};

int
search(int start, int sum)
{
	int i;
	int cnt = 0;

	if (start >= NUM_PENCE)
		return(0);
	
	for (i = start; i < NUM_PENCE; ++i) {
		if (sum + pence[i] == 200) {
			cnt++;
		} else if (sum + pence[i] > 200) {
			continue;
		} else {
			cnt += search(i, sum + pence[i]);
		}
	}

	return(cnt);
}

int
problem(int argc, char** argv)
{
	int cnt;

	printf("Hello World\n");

	cnt = search(0, 0);
	printf("Possible combinations: %d\n", cnt);

	printf("Goodbye World\n");

	return(0);
}

int
main(int argc, char** argv)
{

	return(problem(argc, argv));
}
