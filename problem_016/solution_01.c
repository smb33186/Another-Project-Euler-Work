/*
 * Solution to Project Euler Problem #16
 *
 * Scott Busch
 *
 * Modification Log:
 *	Date			Change
 *	2011/11/07		Initial authoring. 
 *
 */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

#define MAX_NUM_LENGTH		(400)
#define MAX_EXPONENT_BITS	(32)
// #define MAX_EXPONENT		(0x1 << (MAX_EXPONENT_BITS-1))
#define MAX_EXPONENT		0xffffffff

typedef struct BigExponent {
	// int base;
	// int exp;
	int length;
	char decimal[MAX_NUM_LENGTH];
} BigExponent_t;

int max(int a, int b) {
	if (a > b) return(a);
	else return(b);
}

void initNumber(BigExponent_t* number) {
	if (number) {
		memset(number, 0, sizeof (BigExponent_t));
		number->length = 1;
	}
}

char* convertAscii(BigExponent_t* number)
{
	int srcIdx;
	int dstIdx;
	
	if (number == NULL) {
		printf("Cannot conver number: invalid number object specified (NULL)\n");
		return (NULL);
	}

	if (number->length > MAX_NUM_LENGTH || number->length < 0) {
		printf("Cannot convert number: length invalid (%d)\n", number->length);
		return (NULL);
	}

	char *str;

	if (number->length == 0) {
		str = calloc(2, sizeof (char));
		str[0] = '0';
	} else {
		/* Transpose number and convert to ASCII */
		str = calloc(number->length + 1, sizeof (char));
		srcIdx = number->length - 1;
		dstIdx = 0;
		for (dstIdx = 0; dstIdx < MAX_NUM_LENGTH && srcIdx >= 0; ++dstIdx, --srcIdx) {
			str[dstIdx] = number->decimal[srcIdx] + 0x30;
		}
	}

	return (str);
}

BigExponent_t* multiplyNumbers(BigExponent_t *x, BigExponent_t *y, BigExponent_t *result) {

	if (x == NULL || y == NULL || result == NULL) {
		return (NULL);
	}

	initNumber(result);

	if (x->length < 0) {
		printf("X has no digits (%d)\n", x->length);
		return(result);
	}

	if (x->length > MAX_NUM_LENGTH) {
		printf("X reported as larger than buffer (%d)\n", x->length);
		return(NULL);
	}

	if (y->length < 0) {
		printf("Y has no digits (%d)\n", y->length);
		return(result);
	}

	if (y->length > MAX_NUM_LENGTH) {
		printf("Y reported as longer than buffer (%d)\n", y->length);
		return(NULL);
	}

	int idx;
	int xIdx;
	int yIdx;

	for (yIdx = 0; yIdx < y->length; ++yIdx) {

		for (xIdx = 0; xIdx < x->length; ++xIdx) {
			idx = yIdx + xIdx;
			
			if (idx >= MAX_NUM_LENGTH) {
				printf("Maximum number length exceeded (%d = %d + %d)\n", idx, yIdx, xIdx);
				return (NULL);
			}

			result->decimal[idx] += (x->decimal[xIdx] * y->decimal[yIdx]);

			/* Check for and perform carry operation */
			for (; idx < MAX_NUM_LENGTH; ++idx) {
				if (result->decimal[idx] > 9) {
					/* Need to carry */

					/* Check for room to cary */
					if (idx == MAX_NUM_LENGTH - 1) {
						printf("Error: Number limits overflowed (%d)\n", idx);
						return (NULL);
					}

					int ones = result->decimal[idx] % 10;
					int tens = result->decimal[idx] / 10;

					result->decimal[idx] = ones;
					result->decimal[idx+1] += tens;

				} else {
					break;
				}
			}

			result->length = max(result->length, idx + 1);
		}
	}

	return (result);
}

BigExponent_t* squareNumber(BigExponent_t *x, BigExponent_t *result) {
	return (multiplyNumbers(x, x, result));
}

int problem16(int argc, char** argv) {

	int exp = 0;

	if (argc != 2) {
		printf("Error: Invalid parameter count (%d)\n", argc);
		printf("%s <2^x power>\n", argv[0]);
		return(1);
	}

	exp = atoi(argv[1]);
	if (exp < 0) {
		printf("Error: Invalid exponent specified: %d (%s)\n", exp, argv[1]);
		return(1);
	}

	printf("Captured exponent: %d\n", exp);

	/* Special case */
	if (exp == 0) {
		printf("1\n");
		return (0);
	}

	BigExponent_t *working = calloc(1, sizeof(BigExponent_t));
	BigExponent_t *result = calloc(1, sizeof(BigExponent_t));
	BigExponent_t *final = calloc(1, sizeof(BigExponent_t));
	BigExponent_t *swap = NULL;

	initNumber(working);
	initNumber(result);
	initNumber(final);

	working->decimal[0] = 2;
	working->length = 1;
	if (exp & 0x1) {
		final->decimal[0] = 2;
		final->length = 1;
	} else {
		final->decimal[0] = 1;
		final->length = 1;
	}

	int i;
	int bit = 0x2;
	int mask = MAX_EXPONENT & (~1);
	for (i = 2; i < MAX_EXPONENT_BITS; ++i) {
		/* Still more bits to be checked? */
		printf("mask = %08x, bit = %08x, i = %d\n", mask, bit, i);
		if (exp & mask) {
			if ((squareNumber(working, result)) != result) {
				printf("Failure squaring the working number\n");
				return (1);
			}

			swap = working;
			working = result;
			result = swap;

			/* Does this bit need to be included in the final */
			if (exp & bit) {
				printf("Include bit (%d) in final\n", i);
				if ((multiplyNumbers(final, working, result)) != result) {
					printf("Failed multiplying the final and working numbers\n");
					return (1);
				}

				swap = final;
				final = result;
				result = swap;
			}

			bit <<= 1;
			mask <<= 1;
		} else {
			printf("No more bits in exponent (mask = %08x, bit = %08x, i = %d)\n", mask, bit, i);
			break;
		}
	}

	char *str = convertAscii(final);
	printf("2 ^ %d = %s\n", exp, str);
	
	return(0);
}

int main(int argc, char** argv) {

	return(problem16(argc, argv));
}
