/*
 * Solution to Project Euler Problem #xx
 *
 * Scott Busch
 *
 * Modification Log:
 *	Date			Change
 *	2013/02/14		Initial authoring. 
 *
 */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

typedef struct num {
	int max;
	int len;
	unsigned char* num;
} num_t;

int num_alloc(int max, num_t* n) {

	n->max = max;
	n->len = 0;
	n->num = malloc(max * sizeof(unsigned char));
	memset(n->num, 0, max * sizeof(unsigned char));

	return(0);
}

int rexpy(num_t* r, num_t* n1, num_t* n2) {
	if (!r || !n1 || !n2) {
		return(-1);
	}

	int end = (n1->len > n2->len ? n1->len : n2->len);

	if (r->max < end + 2) {
		printf("Error: Destination doesn't have enough space for result: %d < %d\n", r->max, (end + 2));
		return(-1);
	}

	memset(r->num, 0, sizeof(unsigned char) * r->max);

	int i;
	for (i = 0; i < end; i++) {
		unsigned char t = n1->num[i] + n2->num[i] + r->num[i];
		r->num[i] = t % 10;
		r->num[i+1] = t / 10;

		int j = i;
		while (r->num[j] > 10 || r->num[j+1] > 10) {
			r->num[j+1] += r->num[j] / 10;
			r->num[j] = r->num[j] % 10;
			j++;
		}
	}
	
	i = end + 2;
	while (r->num[i] == 0) {
		i--;
	}
	r->len = i+1;

	return(r->len);

}

int problem025(int argc, char** argv) {

	num_t n1;
	num_t n2;
	num_t n3;

	num_t* p1 = NULL;
	num_t* p2 = NULL;
	num_t* p3 = NULL;
	num_t* tmp = NULL;

	num_alloc(1100, &n1);
	num_alloc(1100, &n2);
	num_alloc(1100, &n3);

	p1 = &n1;
	p2 = &n2;
	p3 = &n3;

	n1.len = 1;
	n1.num[0] = 1;

	n2.len = 1;
	n2.num[0] = 1;

	int i = 3;
	int j;
	while (1) {
		rexpy(p3, p1, p2);

		// printf("[%3d] len = %d\n[%3d] ", i, p3->len, i);
		// for (j = p3->len-1; j >= 0; --j) {
			// printf("%c", p3->num[j] + 0x30);
		// }
		// printf("\n");

		if (p3->len >= 1000)
			break;

		tmp = p1;
		p1 = p3;
		p3 = p2;
		p2 = tmp;
		i++;
	}

	printf("F_%d:\n", i);
	printf("len = %d\n", p3->len);
	for (j = p3->len-1; j >= 0; --j) {
		printf("%c", p3->num[j] + 0x30);
	}
	printf("\n");

	return(0);
}

int main(int argc, char** argv) {

	return(problem025(argc, argv));
}
