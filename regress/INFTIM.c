#include "../config.h"

#include <poll.h>

int
main(void)
{
#ifdef INFTIM
	return 0;
#else
	return 1;
#endif
}
