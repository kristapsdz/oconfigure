#include "../config.h"

#include <errno.h>
#include <stdlib.h>
#include <stdio.h>

#if HAVE_SCAN_SCALED
# include <util.h>
#endif

int
main(int argc, char *argv[])
{
	char *cinput = (char *)"1.5K", buf[FMT_SCALED_STRSIZE];
	long long ninput = 10483892, result;

	if (scan_scaled(cinput, &result) != 0)
		return 1;

	if (fmt_scaled(ninput, buf) != 0)
		return 1;

	return 0;
}
