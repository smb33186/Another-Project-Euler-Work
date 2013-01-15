/*
 * Solution to Project Euler Problem #19
 *
 * Scott Busch
 *
 * Modification Log:
 *	Date			Change
 *	2013/01/14		Initial authoring. 
 *
 */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

int days[] = {	31, // January
				28, // February
				31, // March
				30, // April
				31, // May
				30, // June
				31, // July
				31, // August
				30, // Septempter
				31, // October
				30,	// November
				31  // December
			 };

int problem(int argc, char** argv) {

	int year = 1900;
	int month = 0;
	int dayTotal = 1;
	int first_sundays = 0;

	while (year < 2001) {

		if (month == 1 && year % 4 == 0) {
			if (year % 100 != 0 || year % 400 == 0) {
				// Leap year
				dayTotal += days[month] + 1;
			}
		} else {
			dayTotal += days[month];
		}

		if (dayTotal % 7 == 0) {
			if (year > 1900 && year < 2001) {
				first_sundays++;
			}
		}

		if (month == 11)
			year++;

		month = (month + 1) % 12;
	}

	printf("There have been %d Sundays on the first of a month\n", first_sundays);

	return(0);
}

int main(int argc, char** argv) {

	return(problem(argc, argv));
}
