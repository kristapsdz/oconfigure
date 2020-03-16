#include "../config.h"

#if HAVE_GETPROGNAME
# include <stdlib.h>
#endif

#include <string.h> /* strcmp */

int
main(void)
{
	if (strcmp(getprogname(), "./regress/getprogname") == 0)
		return 0;
	if (strcmp(getprogname(), "regress/getprogname") == 0)
		return 0;
	if (strcmp(getprogname(), "getprogname") == 0)
		return 0;
	return 1;
}
