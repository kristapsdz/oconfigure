#include "../config.h"

#include <unistd.h> /* unveil */

int
main(void)
{
#if HAVE_UNVEIL
	if (unveil(NULL, NULL) == -1)
		return 1;
#endif
	return 0;
}
