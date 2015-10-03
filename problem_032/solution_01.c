/*
 * Solution to Project Euler Problem #32
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

int
digit_count(int num)
{
	int cnt = 0;
	while (num > 0) {
		num /= 10;
		cnt++;
	}
	return(cnt);
}

int
check_digits(int a, int b, int c)
{
	int i, d;
	int nums[3] = { a, b, c };
	int digits[10] = { 0 };
	
	for (i = 0; i < 3; ++i) {
		while (nums[i] > 0) {
			d = nums[i] % 10;
			if (d == 0 || digits[d])
				return(0);

			digits[d] = 1;
			nums[i] /= 10;
		}
	}
	return(1);
}


int
problem32(int argc, char** argv)
{

	int i, j;
	int cnt = 0;
	int sum = 0;
	int i_cnt, j_cnt, r_cnt;

	for (i = 1; i < 9999; ++i) {
		i_cnt = digit_count(i);
		for (j = i; j < 9999; ++j) {
			if (i == j)
				continue;

			if (i * j > 9999)
				break;

			j_cnt = digit_count(j);
			r_cnt = digit_count(i*j);

			if (i_cnt + j_cnt + r_cnt != 9)
				continue;

			if (check_digits(i, j, i*j)) {
				printf("Pandigital found: %d * %d = %d\n", i, j, i*j);
				cnt++;
				sum += (i * j);
			}
		}
	}

	printf("Count: %d\n", cnt);
	printf("Sum: %d\n", sum);

	return(0);
}

int
main(int argc, char** argv)
{

	return(problem32(argc, argv));
}
