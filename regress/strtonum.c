#include "../config.h"

#include <stdlib.h>

int
main(void)
{
	int 		 iterations;
	const char 	*errstr;

	iterations = strtonum("64", 1, 64, &errstr);
	if (errstr != NULL)
		return 1;
	if (iterations != 64)
		return 1;
	iterations = strtonum("1", 1, 64, &errstr);
	if (errstr != NULL)
		return 1;
	if (iterations != 1)
		return 1;

	iterations = strtonum("65", 1, 64, &errstr);
	if (errstr == NULL)
		return 1;
	iterations = strtonum("0", 1, 64, &errstr);
	if (errstr == NULL)
		return 1;

	return 0;
}
