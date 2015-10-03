#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <math.h>

int
main(int argc, char **argv)
{
	double i;

	for (i = 1.0; i < 10.0; ++i) {
		printf("%d: %u\n", (int)i, (int)pow(i, 5.0));
	}
	return(0);
}

