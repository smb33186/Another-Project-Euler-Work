/*
 * Solution to Project Euler Problem #42
 *
 * Scott Busch
 *
 * Modification Log:
 *	Date			Change
 *	2017/03/26		Initial authoring. 
 *
 */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

int *triNumbers = NULL;
int triNumLast = 0;

int
growTriangleNumbers(int max)
{
	int n = triNumLast - 1;

	if (triNumbers && triNumbers[n] > max)
		return (1);
	
	do {
		triNumLast += 16;
		triNumbers = realloc(triNumbers, ((triNumLast) * sizeof (int)));
	
		for (; n < triNumLast; ++n)
			triNumbers[n + 1] = triNumbers[n] + n + 1;
	} while (triNumbers[n - 1] < max);

	return (1);
}

int
isTriangleNumber(int num)
{
	int n = 1;

	if (!triNumbers || triNumbers[triNumLast] < num)
		growTriangleNumbers(num);
	
	for (;triNumbers[n] < num; ++n);

	if (triNumbers[n] == num)
		return (1);

	return (0);
}

int
processWord(char *word)
{
	int num = 0;
	char *ptr = word;

	for (ptr = word; *ptr != '\0'; ++ptr) {
		num += (*ptr - 0x40);
	}

	if (isTriangleNumber(num))
		return (1);

	return (0);
}

int
problem42(int argc, char** argv)
{
	char buffer[4096];
	char *ptr = NULL;
	char *end = NULL;
	char *start = NULL;
	size_t offset = 0;
	size_t len = 0;
	int triNumWords = 0;
	int wordCount = 0;
	FILE *fp = NULL;
	char *filename = "p042_words.txt";

	printf("Opening file: %s\n", filename);
	fp = fopen(filename, "r");

	if (!fp) {
		printf("Failed to open source word file: %s\n", filename);
		return (1);
	}

	memset(&buffer[0], 0, sizeof (buffer));

	while ((len = fread(&buffer[offset], sizeof (char), sizeof (buffer) - offset, fp))) {
		ptr = &buffer[0];
		end = &buffer[len + offset];
		start = NULL;

		while (ptr < end) {
			if (*ptr == '"') {
				if (start) {
					// Process word
					wordCount++;
					start++;
					*ptr = '\0';
					if (processWord(start))
						triNumWords++;

					start = NULL;
				} else {
					start = ptr;
				}
			}

			++ptr;
		}

		if (start) {
			for (ptr = &buffer[0], offset = 0; start < end; ++start, ++ptr, ++offset) {
				*ptr = *start;
			}
		} else {
			offset = 0;
		}
	}

	fclose(fp);

	printf("Triangle word count: %d\n", triNumWords);
	printf("Total word count: %d\n", wordCount);

	return (0);
}

int
main(int argc, char** argv)
{
	return (problem42(argc, argv));
}
