/*
 * Solution to Project Euler Problem #xx
 *
 * Scott Busch
 *
 * Modification Log:
 *	Date			Change
 *	2013/01/24		Initial authoring. 
 *
 */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <assert.h>

/*
 * This version is using the GMP library for comparison.
 * Tested with GMP v5.1.0.  Copy the static library and
 * "gmp.h" header into this directory and then compile
 * with:
 *	gcc -Wall -g solution_02.c libgmp.a
 *
 */
#include "gmp.h"


int problem(int argc, char** argv) {

	int i;
	char *numStr;

	mpz_t f;
	mpz_t r;

	mpz_init_set_ui(f, 1);
	mpz_init_set_ui(r, 1);

	for (i = 1; i < 100; ++i) {
		mpz_add_ui(f, f, 1);
		mpz_mul(r, r, f);
	}

	numStr = mpz_get_str(NULL, 10, r);
	printf("%s\n", numStr);

	return(0);
}

int main(int argc, char** argv) {

	return(problem(argc, argv));
}
