#include "../config.h"

int
main(void)
{
#if HAVE_SYSTRACE
	return 1;
#else
	return 0;
#endif
}
