/*
 * Solution to Project Euler Problem #17
 *
 * Scott Busch
 *
 * Modification Log:
 *	Date			Change
 *	2012/12/23		Initial authoring. 
 *
 */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

int letterCount[100];
int tens[10];

void populateBase()
{
	letterCount[0] = 0;		// Zero
	letterCount[1] = 3;		// One
	letterCount[2] = 3;		// Two
	letterCount[3] = 5;		// Three
	letterCount[4] = 4;		// Four
	letterCount[5] = 4;		// Five
	letterCount[6] = 3;		// Six
	letterCount[7] = 5;		// Seven
	letterCount[8] = 5;		// Eight
	letterCount[9] = 4;		// Nine
	letterCount[10] = 3;	// Ten
	letterCount[11] = 6;	// Eleven
	letterCount[12] = 6;	// Twelve
	letterCount[13] = 8;	// Thirteen
	letterCount[14] = 8;	// Fourteen
	letterCount[15] = 7;	// Fifteen
	letterCount[16] = 7;	// Sixteen
	letterCount[17] = 9;	// Seventeen
	letterCount[18] = 8;	// Eighteen
	letterCount[19] = 8;	// Nineteen

	tens[0] = 0;		// Ones places
	tens[1] = -1;		// Teens - Special case
	tens[2] = 6;		// Twenty
	tens[3] = 6;		// Thirty
	tens[4] = 6;		// Fourty
	tens[5] = 5;		// Fifty
	tens[6] = 5;		// Sixty
	tens[7] = 7;		// Seventy
	tens[8] = 6;		// Eighty
	tens[9] = 5;		// Ninty
}

void populateTens()
{
	int i;

	for (i = 20; i < 100; ++i) {
		letterCount[i] = tens[(int)i / (int)10] + letterCount[i % 10];
	}
}

int countTens()
{
	int i;
	int total = 0;

	for (i = 1; i < 100; ++i) {
		total += letterCount[i];
	}

	return(total);
}

int countHundreds(int tensTotal)
{
	int total = 0;
	int i;

	for (i = 1; i < 10; ++i) {
		int hundreds = letterCount[i] + 7;		// xx Hundred
		total += hundreds + (hundreds + 3) * 99 + tensTotal;
	}

	return(total);
}

int problem(int argc, char** argv) {

	int tensSum;
	int hundredsSum;
	int total;

	populateBase();
	populateTens();
	tensSum = countTens();
	hundredsSum = countHundreds(tensSum);

	total = tensSum + hundredsSum + letterCount[1] + 8;		// Tens + hundreds + "one thousand"

	printf("Number of letters in numbers from 1 to 1000: %d\n", total);

	return(0);
}

int main(int argc, char** argv) {

	return(problem(argc, argv));
}
