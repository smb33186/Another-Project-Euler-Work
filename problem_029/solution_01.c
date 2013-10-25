/*
 * Solution to Project Euler Problem #29
 *
 * Scott Busch
 *
 * Modification Log:
 *	Date			Change
 *	2013/10/14		Initial authoring. 
 *
 */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <math.h>

// Using the Omega(x) = log(x)/log(2) equation to bound the upper
// limit on the number of prime factor (including multiplicity of
// terms).  For a < 100, the maximum is 6.
#define MAX_PRIME_FACTORS	6

#define MAX_POWER			100
#define MAX_BASE			100

#define MAX(a, b)			(((a) > (b)) ? (a) : (b))
#define MIN(a, b)			(((a) < (b)) ? (a) : (b))

typedef struct _term {
	unsigned short base;
	unsigned short power;
} term_t;

typedef struct _num {
	int number;
	int cnt;
	term_t components[MAX_PRIME_FACTORS];
} num_t;

typedef struct _ll_node {
	struct _ll_node* next;
	struct _ll_node* prev;
	num_t num;
} ll_node_t;

void print_num(num_t *n);


num_t factor(unsigned int p_orig) {
	num_t factors;
	int i = 2;
	int j = 0;
	unsigned int p = p_orig;

	memset(&factors, 0, sizeof(num_t));

	factors.number = p;

	while (i <= p) {
		if (factors.cnt == (MAX_PRIME_FACTORS - 1)) {
			printf("Error: Base has too many factors: %d\n", p);
			exit(1);
		}

		if (p % i == 0) {
			p /= i;
			for (j = 0; j < factors.cnt; ++j) {
				if (factors.components[j].base == i) {
					factors.components[j].power++;
					break;
				}
			}

			if (j == factors.cnt) {
				factors.components[j].base = i;
				factors.components[j].power = 1;
				factors.cnt++;
			}

			i = 2;
		} else {
			i++;
		}
	}

	unsigned int verify = 1;
	for (i = 0; i < factors.cnt; ++i) {
		verify *= pow(factors.components[i].base, factors.components[i].power);
	}

	if (verify != p_orig) {
		printf("Error: Factoring problem: %u, %u\n", p_orig, verify);
		print_num(&factors);
		exit(1);
	}


	return(factors);
}

void print_num(num_t *n) {
	int i = 0;

	if (n == NULL || n->number <= 0) {
		printf("Invalid number (0x%lx, %d)\n", (unsigned long)n, (n ? n->number : -1));
		return;
	}

	printf("Factors for number %d (Cnt: %d):\n", n->number, n->cnt);
	for (i = 0; i < n->cnt; ++i) {
		printf("   %2d: %2d\n", n->components[i].base, n->components[i].power);
	}
}

void print_num_inline(num_t *n) {
	int i = 0;
	printf("(Cnt: %d)", n->cnt);
	for (; i < n->cnt; ++i) {
		printf(" %d(%d)", n->components[i].base, n->components[i].power);
	}
}

int ll_insert_before(ll_node_t **head, ll_node_t **tail, ll_node_t *ptr, num_t *n) {

	if (!head || !tail || !n) {
		printf("Error: Invalid parameter (head = %p, tail = %p, n = %p)\n", head, tail, n);
		return(0);
	}

	ll_node_t *new = calloc(1, sizeof(ll_node_t));
	new->num = *n;

	if (ptr == NULL) {
		// Goes at end of list (or empty list)
		if (*tail == NULL) {
			// Empty list
			*tail = new;
			*head = new;
		} else {
			// End
			(*tail)->next = new;
			new->prev = (*tail);
			*tail = new;
		}
	} else {
		// Middle or first
		if (*head == ptr) {
			// First
			(*head)->prev = new;
			new->next = *head;
			*head = new;
		} else {
			// Middle
			ptr->prev->next = new;
			new->prev = ptr->prev;
			new->next = ptr;
			ptr->prev = new;
		}
	}

	return(1);
}

int problem29(int argc, char** argv) {

	int i;
	int j;
	int k;
	num_t f[MAX_BASE+1];

	int ll_cnt = 0;
	ll_node_t* ll_head = NULL;
	ll_node_t* ll_tail = NULL;
	ll_node_t* ll_ptr = NULL;

	for (i = 2; i <= MAX_BASE; ++i) {
		f[i] = factor(i);
	}

	// int iterCnt = 0;
	int combo_cnt = 0;
	int duplicate_cnt = 0;

	for (i = 2; i <= MAX_BASE; ++i) {
		for (j = 2; j <= MAX_POWER; ++j) {

			combo_cnt++;

			num_t temp = f[i];
			// printf("[%4d] Power: %d; Base number: ", __LINE__, j);
			// print_num_inline(&temp);
			// printf("\n");

			for (k = 0; k < temp.cnt; ++k) {
				temp.components[k].power *= j;
			}

			// printf("[%4d] Starting insert search: ", __LINE__);
			// print_num_inline(&temp);
			// printf("\n");

			if (ll_cnt == 0) {
				ll_cnt += ll_insert_before(&ll_head, &ll_tail, NULL, &temp);
			} else {
				// Existing
				ll_ptr = ll_head;
				int component = 0;
				int done = 0;
				while (ll_ptr) {
					int stop_component = MIN(temp.cnt, ll_ptr->num.cnt);
					// printf("[%4d]     Comparing to: ", __LINE__);
					// print_num_inline(&ll_ptr->num);
					// printf("\n");

					for (component = 0; component < stop_component; ++component) {
						if (temp.components[component].base > ll_ptr->num.components[component].base) {
							// printf("[%4d]     New has larger base -> Skipping to next\n", __LINE__);
							ll_ptr = ll_ptr->next;
							break;
						} else if (temp.components[component].base < ll_ptr->num.components[component].base) {
							// printf("[%4d]     New has smaller base -> Adding number\n", __LINE__);
							ll_cnt += ll_insert_before(&ll_head, &ll_tail, ll_ptr, &temp);
							done = 1;
							break;
						} else if (temp.components[component].power < ll_ptr->num.components[component].power) {
							// printf("[%4d]     New has equal base with smaller power -> Adding number\n", __LINE__);
							ll_cnt += ll_insert_before(&ll_head, &ll_tail, ll_ptr, &temp);
							done = 1;
							break;
						} else if (temp.components[component].power > ll_ptr->num.components[component].power) {
							// printf("[%4d]     New has equal base but larger power -> Skipping to next\n", __LINE__);
							ll_ptr = ll_ptr->next;
							break;
						}
					}

					// if (++iterCnt > 1000) {
						// printf("[%4d] Aborting...\n", __LINE__);
						// return (0);
					// }

					if (done) {
						break;
					}

					if (component == stop_component) {
						if (temp.cnt == ll_ptr->num.cnt) {
							// Duplicate
							// printf("[%4d]     New is a duplicate -> Do nothing: ", __LINE__);
							// print_num_inline(&ll_ptr->num);
							// printf("\n");
							duplicate_cnt++;
							break;
						}

						if (temp.cnt == stop_component) {
							// printf("[%4d]     New has fewer components -> Adding number\n", __LINE__);
							ll_cnt += ll_insert_before(&ll_head, &ll_tail, ll_ptr, &temp);
							break;
						}

						ll_ptr = ll_ptr->next;
					}
				}

				if (ll_ptr == NULL) {
					ll_cnt += ll_insert_before(&ll_head, &ll_tail, NULL, &temp);
				}
			}

			// printf("[%4d] LL length: %d\n", __LINE__, ll_cnt);
		}
	}

	printf("Duplicates: %d\n", duplicate_cnt);
	printf("Combinations: %d\n", combo_cnt);
	printf("Linked List Count: %d\n", ll_cnt);

	ll_ptr = ll_head;
	while (ll_ptr) {
		ll_head = ll_head->next;
		if (ll_head)
			ll_head->prev = NULL;
		free(ll_ptr);
		ll_ptr = ll_head;
	}
	ll_tail = NULL;

	return(0);
}

int main(int argc, char** argv) {

	return(problem29(argc, argv));
}
