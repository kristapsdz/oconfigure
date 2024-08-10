#include "../config.h"

#include <string.h> /* strndup, strcmp */

int
main(void)
{
	char	*buf;

	/* For simplicity, don't free. */

	buf = strndup("abcdefgh", 2);
	if (buf == NULL)
		return 1;
	if (strcmp(buf, "ab"))
		return 1;

	return 0;
}
