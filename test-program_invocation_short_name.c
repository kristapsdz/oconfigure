#define _GNU_SOURCE         /* See feature_test_macros(7) */
#include <errno.h>

int
main(void)
{

	return !program_invocation_short_name;
}
