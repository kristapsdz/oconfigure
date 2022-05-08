#include <util.h>

int
main(void)
{
	char *cinput = (char *)"1.5K", buf[FMT_SCALED_STRSIZE];
	long long ninput = 10483892, result;
	return scan_scaled(cinput, &result) == 0;
}
