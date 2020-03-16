#include "../config.h"

#include <string.h> /* explicit_bzero, strlcpy */

int
main(void)
{
	char	v[10];
	size_t	i;

	strlcpy(v, "abcdef", sizeof(v));

	/* 
	 * This doesn't check whether the zeroing is explicit, just
	 * whether the function is defined and does something.
	 */

	explicit_bzero(v, sizeof(v));

	for (i = 0; i < sizeof(v); i++)
		if (v[i] != '\0')
			return 1;

	return 0;
}
