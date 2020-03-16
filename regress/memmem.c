#include "../config.h"

#if HAVE_MEMMEM
# include <string.h>
#endif

int
main(void)
{
	const char *v = "abcdefgh";

	if (memmem(v, 8, "fgh", 3) == NULL)
		return 1;
	if (memmem(v, 8, "xyz", 3) != NULL)
		return 1;

	return 0;
}
