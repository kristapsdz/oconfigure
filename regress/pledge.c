#include "../config.h"

#if HAVE_PLEDGE
# include <unistd.h> /* pledge */
#endif

int
main(void)
{
#if HAVE_PLEDGE
	if (pledge("stdio", NULL) == -1)
		return 1;
#endif
	return 0;
}
