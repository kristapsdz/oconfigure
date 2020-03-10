#include <libkern/OSByteOrder.h>

int
main(void)
{
	return !OSSwapHostToLittleInt32(23);
}
