#include "../config.h"

#include <sys/wait.h>

int
main(void)
{
#ifdef WAIT_ANY
	return 0;
#else
	return 1;
#endif
}
