/*
 * Solution to Project Euler Problem #xx
 *
 * Scott Busch
 *
 * Modification Log:
 *	Date			Change
 *	2013/02/08		Initial authoring. 
 *
 */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <assert.h>

#include <stdint.h>
#include <sys/mman.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

typedef struct node {
	struct node *next;
	struct node *prev;
	char *name;
	int score;
} node_t;

int name_score(const char* name) {
	if (!name)
		return(-1);
	
	int score = 0;
	const char* ptr = name;
	while (ptr && *ptr) {
		score += ((*ptr) - 0x40);
		ptr++;
	}

	return(score);
}

/*
 * n1 < n2 => -1
 * n1 = n2 =>  0
 * n1 > n2 =>  1
 *
 * All strings must be NULL termintated since no lengths
 * are used.  This is kind of dangerous/sloppy.
 */
int compare_names(const char* n1, const char* n2) {
	assert(n1);
	assert(n2);

	const char* ptr1 = n1;
	const char* ptr2 = n2;

	while (ptr1 && ptr2) {
		if (*ptr1 == 0 || *ptr2 == 0) {
			if (*ptr1 == *ptr2)
				return(0);
			else if (*ptr1 < *ptr2)
				return(-1);
			else
				return(1);
		} else if (*ptr1 < *ptr2) {
			return(-1);
		} else if (*ptr1 > *ptr2) {
			return (1);
		}
		ptr1++;
		ptr2++;
	}

	/* Should never happen */
	assert(0);
	return(-500);
}

int problem22(int argc, char** argv) {

	char* fName = "names.txt";
	int fd;
	struct stat sb;
	char *fData = NULL;

	fd = open(fName, O_RDONLY);

	if (fd == 0) {
		printf("Error: Failed opening file: \"%s\"\n", fName);
		return(1);
	}

	fstat(fd, &sb);
	printf("File size: %lu\n", sb.st_size);

	fData = malloc(sb.st_size+1);
	fData[sb.st_size-1] = 0;
	fData[sb.st_size] = 0;

	int size = read(fd, fData, sb.st_size);

	if (size != sb.st_size) {
		printf("Read and file sizes do not match:\nread = %d\nfile = %lu\n", size, sb.st_size);
		close(fd);
		return(1);
	}

	close(fd);

	printf("File put into memory\n");

	int score;
	int list_count = 0;
	node_t* head = NULL;
	node_t* tail = NULL;
	node_t* curr = NULL;
	node_t* new = NULL;

	char* token = NULL;
	const char* delim = " ,\"";
	char* last_token = NULL;

	/* This initializes and "chomps" the '"' on the first name.
	 * That way the first call in the loop is at the first name.
	 * strtok "merges" multiple repeated delimiter character
	 * into a single instance too. */
	token = strtok(fData, delim);
	while (1) {

		last_token = token;
		token = strtok(NULL, delim);
		if (!token)
			break;

		if (strlen(token) < 1) {
			printf("Error: Token length too short (file offset: %d, last token: \"%s\")\n", (token - fData), last_token);
			continue;
		}

		score = name_score(token);
		if (score < 0) {
			printf("Error: Problem getting name score for token: \"%s\" (0x%08x)\n", (token ? token : ""), (unsigned int)token);
			continue;
		}

		/* This is inefficient, should do block allocates instead */
		new = calloc(1, sizeof(node_t));

		new->name = token;
		new->score = score;

		curr = head;
		if (!curr) {
			/* First in list */
			head = new;
			tail = new;
		} else {
			/* Elsewhere in list */
			int rc = -5;
			while (curr && (rc = compare_names(curr->name, token)) < 0) {
				curr = curr->next;
			}

			assert(rc != 0);

			/* Update pointers to insert new node */
			if (curr == NULL) {
				/* Tail of list */
				tail->next = new;
				new->prev = tail;
				tail = new;
			} else if (curr == head) {
				/* Head of list */
				head = new;
				new->next = curr;
				curr->prev = new;
			} else {
				/* Middle of list */
				curr->prev->next = new;
				new->prev = curr->prev;
				new->next = curr;
				curr->prev = new;
			}
		}

		list_count++;
	}

	printf("List count: %d\n", list_count);

	/* Count scores */
	int i = 1;
	unsigned long long total = 0;
	curr = head;
	while (curr) {
		total += (curr->score * i);
		curr = curr->next;
		i++;
	}

	printf("Total of all name scores: %llu\n", total);

	/* Clean memory */
	node_t* tmp = NULL;
	curr = head;
	while (curr) {
		tmp = curr->next;
		free(curr);
		curr = tmp;
	}
	head = NULL;
	tail = NULL;

	free(fData);
	
	return(0);
}

int main(int argc, char** argv) {

	return(problem22(argc, argv));
}
