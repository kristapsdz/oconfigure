#include <endian.h>

int
main(void)
{
	return !htole32(23);
}
