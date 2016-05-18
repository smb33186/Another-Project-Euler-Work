/*
 * Solution to Project Euler Problem #40
 *
 * Scott Busch
 *
 * Modification Log:
 *	Date			Change
 *	2016/04/12		Initial authoring. 
 *
 */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>


int
problem40(int argc, char** argv)
{

	int i = 1;
	int j;
	int num;
	int product = 1;
	int order = 1;
	int order_end = 10;
	int digit_count = 0;
	int target_digit = 1;

	while (1) {

		if (digit_count + order >= target_digit) {
		printf("[%4d] order:%d order_end:%d digit_count:%d target:%d\n", i, order, order_end, digit_count, target_digit);
			num = i;
			j = digit_count + order - target_digit;
			printf("  j:%d\n", j);
			for (; j > 0; --j)
				num /= 10;

			int r = num % 10;

			product *= r;
			printf("  r:%d product:%d\n", r, product);

			target_digit *= 10;

		}

		digit_count += order;
		++i;

		if (i == order_end) {
			order += 1;
			order_end *= 10;
		}

		if (digit_count > 1e6)
			break;
	}

	printf("Product: %d\n", product);

	return(0);
}

int
main(int argc, char** argv)
{
	return(problem40(argc, argv));
}
