/*
 * Solution to Project Euler Problem #41
 *
 * Scott Busch
 *
 * Modification Log:
 *	Date			Change
 *	2016/05/26		Initial authoring. 
 *
 */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <stdint.h>


int
isPrime(unsigned int n)
{
	unsigned int i;

	/* Negative, special, or even number */
	if (n == 2)
		return (1);

	if (n < 2 || n % 2 == 0)
		return(0);

	/* Resume where the BM ended */
	for (i = 3; i < (n/2) + 1; i += 2) {
		if (n % i == 0) {
			return(0);
		}
	}

	return(1);
}

char *
printNum(int n, uint8_t digits[])
{
	static char digitStr[16];
	int i;

	memset(digitStr, 0, sizeof (digitStr));
	for (i = 0; i < n; ++i)
		digitStr[i] = digits[i] + 0x30;

	return (digitStr);
}

/*
 * checkDigits
 *
 * Check if the current digit combination is a prime number.
 * Returns the number if it is prime. Otherwise returns 0.
 */
int
checkDigits(int n, uint8_t digits[])
{
	unsigned int num;
	unsigned int scalar;
	int i;

	if (digits[n - 1] % 2 == 0)
		return (0);

	for (i = n - 1, scalar = 1, num = 0; i >= 0; --i, scalar *= 10)
		num += (digits[i] * scalar);
	
	if (isPrime(num))
		return (num);

	return (0);
}

/*
 * permute
 *
 * Recursive function to iterate through all the digit combinations
 * of a source array. Starts with the largest number and tests smaller
 * combinations until the first prime is found.
 *
 * Inputs:
 *   n - number of digits
 *   pos - current index position for iterating
 *   digits - digit array for permuting
 *
 * Results:
 *   0 = No prime number found
 *   <prime> = First prime found.
 */
int
permute(int n, int pos, uint8_t digits[])
{
	int i;
	unsigned int num;
	uint8_t temp;

	if (pos == n - 1) {
		if ((num = checkDigits(n, digits)))
			return (num);
		else
			return (0);
	}
	
	/* Progressively swap the digit at the current position to the end */
	for (i = pos; i < n; ++i) {
		if ((num = permute(n, pos + 1, digits))) {
			return (num);
		}

		if (i == n - 1)
			break;

		temp = digits[pos];
		digits[pos] = digits[i + 1];
		digits[i + 1] = temp;
	}

	/* Restore the digits to their original positions */
	for (i--; i >= pos; --i) {
		temp = digits[pos];
		digits[pos] = digits[i + 1];
		digits[i + 1] = temp;
	}

	return (0);
}

int
problem41(int argc, char** argv)
{
	uint8_t	digits[10];
	int n = 2;
	unsigned int	num = 0;
	int i;

	if (argc > 1)
		n = atoi(argv[1]);

	printf("n = %d\n", n);

	for (; n > 0; n--) {

		printf("n = %d\n", n);
		/* Initialize */
		for (i = 0; i < n; ++i)
			digits[i] = n - i;

		num = permute(n, 0, digits);

		if (num)
			break;
	}

	if (num) {
		printf("Result: %u\n", num);
	}

	return (0);
}

int
main(int argc, char** argv)
{
	return (problem41(argc, argv));
}
