#include "../config.h"

#include <limits.h>

int
main(void)
{
#ifdef PATH_MAX
	return 0;
#else
	return 1;
#endif
}
