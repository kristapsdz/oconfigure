#ifdef __linux__
# define _DEFAULT_SOURCE
#endif
#include <endian.h>

int
main(void)
{
	return !htole32(23);
}
