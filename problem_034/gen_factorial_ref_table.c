#include <stdio.h>

int
main(int argc, char **argv)
{
	int i;
	int prod = 1;
	printf("0\n");
	for (i = 1; i < 10; ++i) {
		printf("%d\n", (prod *= i));
	}

	return(0);
}

