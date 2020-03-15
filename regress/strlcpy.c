#include "../config.h"

#include <string.h>

int
main(void)
{
	char	v[10];

	if (strlcpy(v, "abcdef", sizeof(v)) >= sizeof(v))
		return 1;
	if (strcmp(v, "abcdef"))
		return 1;
	if (strlcpy(v, "abcdefabcdef", sizeof(v)) < sizeof(v))
		return 1;
	if (strcmp(v, "abcdefabc"))
		return 1;

	return 0;
}
