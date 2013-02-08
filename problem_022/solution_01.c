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

#include <stdint.h>
#include <sys/mman.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

struct node {
	struct node *next;
	struct node *prev;
	char *name;
	int score;
} node_t;

// int tokenize(char* start, char** end) {

	// while(start

int proc_names(char* fData, int len) {

	int i;
	char* ptr = fData;


	return(0);
}

int problem(int argc, char** argv) {

	int page_size;
	int page_count;
	int mem_size;

	char* fName = "names.txt";
	int fd;
	struct stat sb;

	char *fData = NULL;

	page_size = getpagesize();

	fd = open(fName, O_RDONLY);

	if (fd == 0) {
		printf("Error: Failed opening file: \"%s\"\n", fName);
		return(1);
	}

	fstat(fd, &sb);
	printf("File size: %lu\n", sb.st_size);

	page_count = (sb.st_size + page_size - 1) / page_size;
	mem_size = page_count * page_size;

	printf("Page size: %d\n", page_size);
	printf("Pages needed: %d\n", page_count);

	fData = mmap(NULL, sb.st_size, PROT_READ, MAP_PRIVATE, fd, 0);

	if (fData == NULL) {
		printf("Error: mmap of file failed\n");
	} else {
		proc_names(fData, sb.st_size);
		munmap(fData, sb.st_size);
	}

	close(fd);

	return(0);
}

int main(int argc, char** argv) {

	return(problem(argc, argv));
}
