#include "../config.h"

#if HAVE_SYS_SYSMACROS_H
# include <sys/sysmacros.h>
#else
# include <sys/types.h>
#endif

int
main(void)
{
	minor(0);
	return 0;
}
