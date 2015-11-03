/*
 * Solution to Project Euler Problem #39
 *
 * Scott Busch
 *
 * Modification Log:
 *	Date			Change
 *	2015/10/19		Initial authoring. 
 *
 */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <math.h>

int counts[1001] = { 0 };

int
problem39(int argc, char** argv)
{
	int i, i_s;
	int j, j_s;
	int k;

	for (i = 1; i < 500; ++i) {
		i_s = i * i;
		for (j = i; (j < 1000) && (i + j <= 1000); ++j) {
			j_s = j * j;
			k = (int)sqrt(i_s + j_s);

			if (k * k != i_s + j_s)
				continue;

			if (i + j + k > 1000)
				break;

			counts[i+j+k]++;
		}
	}

	int max = 0;
	int max_num = 0;
	for (i = 1; i <= 1000; ++i) {
		if (counts[i]) {
			if (counts[i] > max) {
				max = counts[i];
				max_num = i;
			}
		}
	}

	printf("%d: %d (%d)\n", max_num, max, counts[max_num]);

	return(0);
}

int
main(int argc, char** argv)
{
	return(problem39(argc, argv));
}
