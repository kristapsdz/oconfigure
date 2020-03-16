#include "../config.h"

#if HAVE_ERR
# include <err.h>
#endif

int
main(void)
{
	warnx("testing");
	warn("testing");
	errx(0, "non-failure");
}
