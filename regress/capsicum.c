#include "../config.h"

#if HAVE_CAPSICUM
# include <sys/resource.h>
# include <sys/capsicum.h>
#endif
#include <errno.h>

int
main(void)
{
#if HAVE_CAPSICUM
	if (cap_enter() == -1 && errno != ENOSYS)
		return 1;
#endif
	return 0;
}
