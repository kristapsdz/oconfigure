#include "../config.h"

#include <string.h> /* strnlen */

int
main(void)
{
	char	v[10];

	strlcpy(v, "abc", sizeof(v));
	if (strnlen(v, sizeof(v)) != 3)
		return 1;
	if (strnlen(v, 2) != 2)
		return 1;

	return 0;
}
