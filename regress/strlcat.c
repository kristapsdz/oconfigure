#include "../config.h"

#include <string.h>

int
main(void)
{
	char	v[10];

	v[0] = '\0';
	if (strlcat(v, "abcdef", sizeof(v)) >= sizeof(v))
		return 1;
	if (strcmp(v, "abcdef"))
		return 1;
	if (strlcat(v, "abcdef", sizeof(v)) < sizeof(v))
		return 1;
	if (strcmp(v, "abcdefabc"))
		return 1;

	return 0;
}
