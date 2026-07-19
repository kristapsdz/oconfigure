#include "../config.h"

#if HAVE_SYS_CDEFS_H
# include <sys/cdefs.h>
#endif
#include <stdlib.h>

__dead __used static void
exiter(int code, int __unused something)
{
	exit(code);
}

int
main(void)
{
	exiter(0, 1234);
}
