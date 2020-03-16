#include "../config.h"

#if HAVE_MEMRCHR
# include <string.h>
#endif

int
main(void)
{
	const char *v = "abcdefgh";

	if (memrchr(v, 'a', 8) == NULL)
		return 1;
	if (memrchr(v, 'z', 8) != NULL)
		return 1;

	return 0;
}
