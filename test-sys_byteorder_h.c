#include <sys/byteorder.h>

int
main(void)
{
	return !LE_32(23);
}
