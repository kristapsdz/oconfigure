#include "../config.h"

#if HAVE_TIMINGSAFE_BCMP
# include <string.h>
#endif

int main(void)
{
	const char *a = "foo", *b = "bar";

	if (timingsafe_bcmp(a, b, 2) == 0 ||
	    timingsafe_memcmp(a, b, 2) == 0)
		return 1;

	return 0;
}
