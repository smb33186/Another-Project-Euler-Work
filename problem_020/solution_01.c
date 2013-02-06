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

typedef struct big_num {
	int length;
	int max;
	unsigned char* num;
} big_num_t;

int big_num_init(big_num_t *n, unsigned int max) {
	if (n == NULL || max <= 0)
		return(-1);
	
	n->num = malloc(max * sizeof(char));
	assert(n->num != NULL);
	memset(n->num, 0, max * sizeof(char));

	n->max = max;
	n->length = 0;

	return(0);
}

int big_num_resize(big_num_t *n, unsigned int newMax) {

	if (n == NULL || newMax < n->length) {
		return(-1);
	}

	unsigned char* tmp = malloc(newMax * sizeof(char));
	assert(tmp != NULL);
	memset(tmp, 0, newMax * sizeof(char));

	memcpy(tmp, n->num, ((newMax > n->max) ? n->max : newMax));
	free(n->num);
	n->num = tmp;

	return(0);
}

int big_num_clear(big_num_t *n) {
	memset(n->num, 0, n->max);
	n->length = 0;
	return(0);
}

int big_num_multiply(big_num_t *d, big_num_t *s1, big_num_t *s2) {

	if (d->max < s1->length + s2->length) {
		big_num_resize(d, s1->length + s2->length + 20);
	}

	big_num_clear(d);

	int i;
	int j;
	int k;
	unsigned char r;
	unsigned char m;
	for (i = 0; i < s2->length; i++) {
		m = s2->num[i];
		for (j = 0; j < s1->length; j++) {
			/* Calculate single digit result */
			r = m * s1->num[j];

			/* Save into dest and carry */
			d->num[i+j] += r % 10;
			d->num[i+j+1] += r / 10;

			/* Carry through */
			k = i+j;
			while(d->num[k] > 9) {
				r = d->num[k];
				d->num[k] %= 10;
				d->num[k+1] += r / 10;
				++k;
			}
		}
	}

	d->length = s1->length + s2->length;

	/* Chomp leading zeros */
	while(d->num[d->length-1] == 0) {
		d->length--;
	}

	return(0);
}

int big_num_add_one(big_num_t *n) {

	/* Check for size */
	if (n->length == n->max) {
		big_num_resize(n, n->length + 20);
	}

	/* Add 1 */
	n->num[0] += 1;

	/* Carry if needed */
	int i = 0;
	while(n->num[i] > 9) {
		n->num[i+1] += n->num[i] / 10;
		n->num[i] %= 10;
		i++;
	}

	/* Incrase length if carried far enough */
	if (i == n->length) {
		n->length++;
	}

	return(0);
}

void big_num_print(big_num_t *n, const char *name) {
	int i;

	printf("%s = ", name);
	for(i = n->length-1; i >= 0; i--) {
		printf("%c", (n->num[i] + 0x30));
	}
	printf("\n");
}


int problem(int argc, char** argv) {

	int i;
	big_num_t f;
	big_num_t r1;
	big_num_t r2;
	big_num_t *w1;
	big_num_t *w2;
	big_num_t *tmp;

	big_num_init(&f, (unsigned)10);
	big_num_init(&r1, (unsigned)200);
	big_num_init(&r2, (unsigned)200);

	big_num_clear(&f);
	big_num_clear(&r1);
	big_num_clear(&r2);

	f.num[0] = 1;
	f.length = 1;
	r1.num[0] = 1;
	r1.length = 1;

	w1 = &r1;
	w2 = &r2;
	tmp = NULL;

	for (i = 1; i < 100; ++i) {
		big_num_add_one(&f);
		big_num_multiply(w2, w1, &f);

		tmp = w2;
		w2 = w1;
		w1 = tmp;
	}

	big_num_print(&f, "f");
	big_num_print(w1, "result");

	return(0);
}

int main(int argc, char** argv) {

	return(problem(argc, argv));
}
