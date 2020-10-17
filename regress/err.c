#include "../config.h"

#if HAVE_ERR
# include <err.h>
#endif
#include <errno.h>
#include <stdlib.h>

int
main(void)
{
	warnx("testing");
	warn("testing");
	warnc(ENOENT, "testing");
	errx(0, "non-failure");
	/* We shouldn't get here. */
	exit(1);
}
