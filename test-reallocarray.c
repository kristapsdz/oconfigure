#ifdef __NetBSD__
# define _OPENBSD_SOURCE
#endif
#include <stdlib.h>

int
main(void)
{
	return !reallocarray(NULL, 2, 2);
}
