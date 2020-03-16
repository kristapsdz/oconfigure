#include "../config.h"

#include <unistd.h> /* pledge */

int
main(void)
{
#if HAVE_PLEDGE
	if (pledge("stdio", NULL) == -1)
		return 1;
#endif
	return 0;
}
